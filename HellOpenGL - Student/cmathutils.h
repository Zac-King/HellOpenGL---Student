#pragma once
#include <cmath>

union vec3 { float v[3]; struct { float x, y, z; }; };
union vec4 { float v[4]; struct  { float x, y, z, w; }; };
union mat4 { float m[16]; float mm[4][4]; vec4 v[4]; };

typedef mat4 Matrix4;

mat4 mat4MakeIdentity();
mat4 mul(mat4 a, mat4 b);

mat4 operator*(mat4 a, mat4 b);

mat4 getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);


mat4 makeRotation(float angle);
mat4 makeTranslation(vec3 pos);


vec4 operator*(vec4 a, float b);
vec4 operator-(vec4 a, vec4 b);
vec4 operator+(vec4 a, vec4 b);


vec3 operator*(vec3 a, float b);
vec3 operator-(vec3 a, vec3 b);
vec3 operator+(vec3 a, vec3 b);


vec4 operator+(vec4 a, vec3 b);