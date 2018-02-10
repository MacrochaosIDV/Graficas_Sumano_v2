#ifndef IDV_PARSER
#define IDV_PARSER

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct CVertexMesh {

	float x, y, z;
	float w = 1;
	float nx, ny, nz, nw;
	float s, t;
};

void PrintFromLibrary();
void ReadFile(std::string filename);
void ParserInner_w_events(std::string filename, SDL_Event evento);

#endif