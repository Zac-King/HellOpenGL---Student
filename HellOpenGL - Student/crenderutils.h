#pragma once
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include "cmathutils.h"

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

// don't use these.
// Make your own. These are for demonstration only.

//mat4 mul(mat4 a, vec4 b);
/////////////////////////////////////////////////////////



struct Vertex { vec4 position; vec4 color; }; //

struct Triangle { unsigned v[3]; }; // 12 bytes

struct RenderObject
{
	unsigned VBO, IBO, VAO, size;
};

struct TextureData
{
	int width, height, format;
	GLuint handle;
};


RenderObject loadMesh(Vertex *verts, unsigned nverts,
					  Triangle *tris, unsigned ntris);

void drawRenderObject(RenderObject ro, unsigned shader);

GLuint CreateProgram(const char *a_vertex, const char *a_frag);

TextureData LoadTexture(const char *a_path);



