/**
    @author Stefano Nuvoli
*/
#include "convexhull2d_iterative.h"

namespace cg3 {


/* ----- USEFUL FUNCTION DECLARATION ----- */

template <class T>
void processConvexHull(
        const Point2D<T>& point,
        std::set<Point2D<T>>& upper,
        std::set<Point2D<T>>& lower);



/* ----- ITERATIVE CONVEX HULL 2D IMPLEMENTATION ----- */


/* CONSTRUCTORS/DESTRUCTORS */

/**
 * @brief Constructor for empty datastructure
 */
template <class T>
IterativeConvexHull2D<T>::IterativeConvexHull2D() {

}

/**
 * @brief Constructors to initialize the convex hull with given points
 * given the on iterators of containers
 * @param[in] first First iterator of the input container
 * @param[in] end End iterator of the input container
 */
template <class T> template <class InputIterator>
IterativeConvexHull2D<T>::IterativeConvexHull2D(
        const InputIterator first,
        const InputIterator end)
{
    this->addPoints(first, end);
}

/**
 * @brief Constructors to initialize the convex hull with given points
 * in a container
 * @param[in] points Container of the points of the shape
 */
template <class T> template <class InputContainer>
IterativeConvexHull2D<T>::IterativeConvexHull2D(const InputContainer& container)
{
    this->addPoints(container.begin(), container.end());
}



/**
 * @brief Constructors to initialize the convex hull with given points
 * given the on iterators of containers
 * @param[in] first First iterator of the input container
 * @param[in] end End iterator of the input container
 */
template <class T> template <class InputIterator>
void IterativeConvexHull2D<T>::addPoints(const InputIterator first, const InputIterator end) {
    for (InputIterator it = first; it != end; it++) {
        this->addPoint(*it);
    }
}

/**
 * @brief Constructors to initialize the convex hull with given points
 * in a container
 * @param[in] points Container of the points of the shape
 */
template <class T> template <class InputContainer>
void IterativeConvexHull2D<T>::addPoints(const InputContainer& container)
{
    this->addPoints(container.begin(), container.end());
}




/**
 * @brief Add a new point to the convex hull
 * @param[in] point Input point
 */
template <class T>
void IterativeConvexHull2D<T>::addPoint(const Point2D<T>& point) {
    cg3::processConvexHull<T>(point, this->upper, this->lower);
}

/**
 * @brief Get convex hull of the current data structure
 * @param[out] out Output iterator
 */
template <class T> template <class OutputIterator>
void IterativeConvexHull2D<T>::getConvexHull(OutputIterator out) {

    if (this->upper.size() > 1) {

        //Upper convex hull
        auto firstUpper = this->upper.begin();
        auto lastUpper = std::prev(this->upper.end());

        typename std::set<Point2D<T>>::iterator itUpper = firstUpper;

        do {
            *out = *itUpper;
            out++;

            itUpper++;
        } while (itUpper != lastUpper);


        //Lower convex hull
        if (!this->lower.empty()) {
            auto firstLower = this->lower.rbegin();
            auto lastLower = std::prev(this->lower.rend());

            typename std::set<Point2D<T>>::reverse_iterator itLower = firstLower;

            do {
                *out = *itLower;
                out++;

                itLower++;
            } while (itLower != lastLower);
        }

    }
    else {
        for (const Point2D<T>& p : this->upper) {
            *out = p;
            out++;
        }
    }

}


/**
 * @brief Clear convex hull
 */
template <class T>
void IterativeConvexHull2D<T>::clear() {
    upper.clear();
    lower.clear();
}


/* ----- ALGORITHM INTERFACE IMPLEMENTATION ----- */

/**
 * @brief Add point to the convex hull
 */
template <class T>
void addPointToConvexHull(
        const Point2D<T>& point,
        IterativeConvexHull2D<T>& iterativeConvexHull2D)
{
    iterativeConvexHull2D.addPoint(point);
}



/* ----- USEFUL FUNCTION IMPLEMENTATION ----- */

/**
 * @brief Algorithm step for processing iterative convex hull
 *
 * @param[in] point Added point
 * @param[out] upper Current upper convex hull
 * @param[out] lower Current upper convex hull
 */
template <class T>
void processConvexHull(
        const Point2D<T>& point,
        std::set<Point2D<T>>& upper,
        std::set<Point2D<T>>& lower)
{
    typedef typename std::set<Point2D<T>>::iterator SetIt;


    // Upper convex hull

    if (upper.size() < 2) {
        upper.insert(point);
    }
    else {
        //Get first and last
        SetIt firstUpper = upper.begin();
        SetIt lastUpper = std::prev(upper.end());


        //If the point is an endpoints
        //Or the it is at the left of the first-last segment
        if (
                point < *firstUpper ||
                point > *lastUpper ||
                cg3::isPointAtLeft(*firstUpper, *lastUpper, point))
        {
            std::pair<SetIt, bool> pairUpperIt = upper.insert(point);
            SetIt upperIt = pairUpperIt.first;

            //Set endpoints if they exist

            SetIt upperPrev = upper.end();
            if (*upperIt != *firstUpper) {
                upperPrev = upperIt;
                upperPrev--;
            }
            SetIt upperNext = upper.end();
            if (*upperIt != *lastUpper) {
                upperNext = upperIt;
                upperNext++;
            }

            //If the new iterator has prev and next
            //Erase point if the point is at left of the neighbor segment
            if (
                    upperPrev != upper.end() &&
                    upperNext != upper.end() &&
                    !cg3::isPointAtLeft(*upperPrev, *upperNext, *upperIt))
            {
                upper.erase(upperIt);
            }
            else {
                //If the point has a prev
                if (upperPrev != upper.end()) {
                    SetIt upperPrevPrev = upperPrev;
                    upperPrevPrev--;

                    while (*upperPrev != *firstUpper &&
                           !cg3::isPointAtLeft(*upperPrevPrev, *upperIt, *upperPrev)) {
                        upperPrevPrev--;
                        upper.erase(upperPrev--);
                    }
                }

                //If the point has a next
                if (upperNext != upper.end()) {
                    SetIt upperNextNext = upperNext;
                    upperNextNext++;

                    while (*upperNext != *lastUpper &&
                           !cg3::isPointAtLeft(*upperIt, *upperNextNext, *upperNext)) {
                        upperNextNext++;
                        upper.erase(upperNext++);
                    }
                }
            }
        }
    }



    // Lower convex hull


    if (lower.size() < 2) {
        lower.insert(point);
    }
    else {
        //Get first and last
        SetIt firstLower = std::prev(lower.end());
        SetIt lastLower = lower.begin();

        //If the point is an endpoints
        //Or the it is at the left of the first-last segment
        if (
                point > *firstLower ||
                point < *lastLower ||
                cg3::isPointAtLeft(*firstLower, *lastLower, point))
        {
            std::pair<SetIt, bool> pairLowerIt = lower.insert(point);
            SetIt lowerIt = pairLowerIt.first;

            //Set endpoints if they exist

            SetIt lowerPrev = lower.end();
            if (*lowerIt != *firstLower) {
                lowerPrev = lowerIt;
                lowerPrev++;
            }
            SetIt lowerNext = lower.end();
            if (*lowerIt != *lastLower) {
                lowerNext = lowerIt;
                lowerNext--;
            }

            //If the new iterator has prev and next
            //Erase point if the point is at left of the neighbor segment
            if (
                    lowerPrev != lower.end() &&
                    lowerNext != lower.end() &&
                    !cg3::isPointAtLeft(*lowerPrev, *lowerNext, *lowerIt))
            {
                lower.erase(lowerIt);
            }
            else {
                //If the point has a prev
                if (lowerPrev != lower.end()) {
                    SetIt lowerPrevPrev = lowerPrev;
                    lowerPrevPrev++;

                    while (*lowerPrev != *firstLower &&
                           !cg3::isPointAtLeft(*lowerPrevPrev, *lowerIt, *lowerPrev)) {
                        lowerPrevPrev++;
                        lower.erase(lowerPrev++);
                    }
                }

                //If the point has a next
                if (lowerNext != lower.end()) {
                    SetIt lowerNextNext = lowerNext;
                    lowerNextNext--;

                    while (*lowerNext != *lastLower &&
                           !cg3::isPointAtLeft(*lowerIt, *lowerNextNext, *lowerNext)) {
                        lowerNextNext--;
                        lower.erase(lowerNext--);
                    }
                }
            }
        }
    }

}


}