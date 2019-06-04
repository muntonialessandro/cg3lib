/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "ply_vertex.h"
#include <cg3/utilities/tokenizer.h>

namespace cg3 {
namespace ply {

namespace internal {

template <typename A, typename B, typename C>
bool loadVerticesTxt(
		std::ifstream& file,
		const PlyHeader& header,
		A vertices[],
		B verticesNormals[],
		io::FileColorMode colorMod ,
		C verticesColors[])
{
	bool error = false;
	uint colorStep = 3;
	if (colorMod == io::RGBA)
		colorStep = 4;
	cg3::Tokenizer spaceTokenizer;
	error = internal::nextLine(file, spaceTokenizer);
	cg3::Tokenizer::iterator token = spaceTokenizer.begin();
	for(uint v = 0; v < header.numberVertices(); ++v) {
		for (ply::Property p : header.vertexProperties()) {
			if (token == spaceTokenizer.end()){
				error = nextLine(file, spaceTokenizer);
				token = spaceTokenizer.begin();
			}
			if (error) return false;
			switch (p.name) {
				case ply::x :
					vertices[v*3] = internal::readProperty<A>(token, p.type); break;
				case ply::y :
					vertices[v*3+1] = internal::readProperty<A>(token, p.type); break;
				case ply::z :
					vertices[v*3+2] = internal::readProperty<A>(token, p.type); break;
				case ply::nx :
					verticesNormals[v*3] = internal::readProperty<B>(token, p.type); break;
				case ply::ny :
					verticesNormals[v*3+1] = internal::readProperty<B>(token, p.type); break;
				case ply::nz :
					verticesNormals[v*3+2] = internal::readProperty<B>(token, p.type); break;
				case ply::red :
					verticesColors[v*colorStep] = internal::readProperty<C>(token, p.type, true); break;
				case ply::green :
					verticesColors[v*colorStep+1] = internal::readProperty<C>(token, p.type, true); break;
				case ply::blue :
					verticesColors[v*colorStep+2] = internal::readProperty<C>(token, p.type, true); break;
				case ply::alpha :
					if(colorStep == 4){ // alpha in file that will be saved
						verticesColors[v*colorStep+3] = internal::readProperty<C>(token, p.type, true);;
					}
					else { // alpha in file that will not be saved
						token++;
					}
					break;
				case ply::vertex_indices :
				case ply::unknown :
					if (p.list){
						uint s = internal::readProperty<int>(token, p.listSizeType);
						for (uint i = 0; i < s; ++i)
							internal::readProperty<int>(token, p.type);
					}
					else {
						internal::readProperty<int>(token, p.type);
					}
			}
		}
	}
	return !error;
}

template <typename A, typename B, typename C>
bool loadVerticesBin(
		std::ifstream& file,
		const PlyHeader& header,
		A vertices[],
		B verticesNormals[],
		io::FileColorMode colorMod ,
		C verticesColors[])
{
	uint colorStep = 3;
	if (colorMod == io::RGBA)
		colorStep = 4;
	for(uint v = 0; v < header.numberVertices(); ++v) {
		for (ply::Property p : header.vertexProperties()) {
			switch (p.name) {
				case ply::x :
					vertices[v*3] = internal::readProperty<A>(file, p.type); break;
				case ply::y :
					vertices[v*3+1] = internal::readProperty<A>(file, p.type); break;
				case ply::z :
					vertices[v*3+2] = internal::readProperty<A>(file, p.type); break;
				case ply::nx :
					verticesNormals[v*3] = internal::readProperty<B>(file, p.type); break;
				case ply::ny :
					verticesNormals[v*3+1] = internal::readProperty<B>(file, p.type); break;
				case ply::nz :
					verticesNormals[v*3+2] = internal::readProperty<B>(file, p.type); break;
				case ply::red :
					verticesColors[v*colorStep] = internal::readProperty<C>(file, p.type, true); break;
				case ply::green :
					verticesColors[v*colorStep+1] = internal::readProperty<C>(file, p.type, true); break;
				case ply::blue :
					verticesColors[v*colorStep+2] = internal::readProperty<C>(file, p.type, true); break;
				case ply::alpha :
					if (colorStep == 4)
						verticesColors[v*colorStep+3] = internal::readProperty<C>(file, p.type, true);
					else
						internal::readProperty<C>(file, p.type, true); //read without save anywhere
					break;
				case ply::vertex_indices :
				case ply::unknown :
					if (p.list){
						uint s = internal::readProperty<int>(file, p.listSizeType);
						for (uint i = 0; i < s; ++i)
							internal::readProperty<int>(file, p.type);
					}
					else {
						internal::readProperty<int>(file, p.type);
					}
			}
		}
	}
	return true;
}

} //namespace cg3::ply::internal

template <typename A, typename B, typename C>
void saveVertices(
		std::ofstream& file,
		const PlyHeader& header,
		const A vertices[],
		const B verticesNormals[],
		io::FileColorMode colorMod ,
		const C verticesColors[])
{
	bool bin = header.format() == ply::BINARY;
	uint colorStep = 3;
	if (colorMod == io::RGBA)
		colorStep = 4;
	for(uint v = 0; v < header.numberVertices(); ++v) {
		for (ply::Property p : header.vertexProperties()) {
			switch (p.name) {
				case ply::x :
					internal::writeProperty(file, vertices[v*3], p.type, bin); break;
				case ply::y :
					internal::writeProperty(file, vertices[v*3+1], p.type, bin); break;
				case ply::z :
					internal::writeProperty(file, vertices[v*3+2], p.type, bin); break;
				case ply::nx :
					internal::writeProperty(file, verticesNormals[v*3], p.type, bin); break;
				case ply::ny :
					internal::writeProperty(file, verticesNormals[v*3+1], p.type, bin); break;
				case ply::nz :
					internal::writeProperty(file, verticesNormals[v*3+2], p.type, bin); break;
				case ply::red :
					internal::writeProperty(file, verticesColors[v*colorStep], p.type, bin, true); break;
				case ply::green :
					internal::writeProperty(file, verticesColors[v*colorStep+1], p.type, bin, true); break;
				case ply::blue :
					internal::writeProperty(file, verticesColors[v*colorStep+2], p.type, bin, true); break;
				case ply::alpha :
					if (colorStep == 4)
						internal::writeProperty(file, verticesColors[v*colorStep+3], p.type, bin, true);
					else
						internal::writeProperty(file, (p.type < 6 ? 255 : 1), p.type, bin, true);
						;
					break;
				case ply::vertex_indices :
				case ply::unknown :
					internal::writeProperty(file, 0, p.type, bin); break;
			}
		}
		if (!bin)
			file << std::endl;
	}
}

template <typename A, typename B, typename C>
bool loadVertices(
		std::ifstream& file,
		const PlyHeader& header,
		A vertices[],
		B verticesNormals[],
		io::FileColorMode colorMod ,
		C verticesColors[])
{
	if(header.format() == ply::ASCII) {
		return internal::loadVerticesTxt(file, header, vertices, verticesNormals, colorMod, verticesColors);
	}
	else if(header.format() == ply::BINARY) {
		return internal::loadVerticesBin(file, header, vertices, verticesNormals, colorMod, verticesColors);
	}
	else return false;
}

} //namespace cg3::ply
} //namespace cg3
