/**
  * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
  * This Source Code Form is subject to the terms of the GNU GPL 3.0
  *
  * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
  */

#ifndef CG3_CG3LIB_H
#define CG3_CG3LIB_H

#if __cplusplus >= 201300
#define CG3_CPP14
#endif

/**
  * @link: https://stackoverflow.com/questions/11124895/suppress-compiler-warning-function-declared-never-referenced
  */
#define CG3_SUPPRESS_WARNING(a) (void)a

/**
  * @link: https://stackoverflow.com/questions/20631922/expand-macro-inside-string-literal
  */
#define CG3_STRINGIFY2(X) #X
#define CG3_STRINGIFY(X) CG3_STRINGIFY2(X)

#endif // CG3_CG3LIB_H
