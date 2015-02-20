#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include "crenderutils.h"
#include "GameObject.h"
#include "TankStuff.h"
#include "Engine.h"

const unsigned int e_SCREEN_WIDTH  = 1280;
const unsigned int e_SCREEN_HEIGHT = 720;
const char		   e_SCREEN_NAME[] = "roar";

#define S_W e_SCREEN_WIDTH
#define S_H e_SCREEN_HEIGHT

int main()
{
	Engine &eref = Engine::getInstance();

	eref.loadCore();
	eref.init();

	GLFWwindow* window = Window::getInstance().getHandle();
	
	/// Camera Information
	mat4 view = mat4MakeIdentity();
	mat4 ortho = getOrtho(0, e_SCREEN_WIDTH, 0, e_SCREEN_HEIGHT, 0, 100);

	// Vertex/Triangle Mesh information
	Vertex verts[3] = { { { 0, 30, 0, 1},
						  { 0, 1, 1, 1 } },

					    { { -30, -30, 0, 1 }, 
						  { 1, 1, 0, 1 } },	

						{ { 30, -30, 0, 1 },
						  { 1, 0, 1, 1 } } };

	Triangle tris[1] = { 0, 1, 2 };
	
	// Model Laoded in
	RenderObject ro = loadMesh(verts, 3, tris, 1);
	// Shaders Loaded in
	GLuint shader = CreateProgram("./shaders/simpleShader.vert",
								  "./shaders/simpleShader.frag");

	// GameObjects created...
	Tank monkey(ro, shader, mat4MakeIdentity());

	monkey.m_transform.m_local.v[3].x = S_W / 2;
	monkey.m_transform.m_local.v[3].y = S_H / 2;
	monkey.m_transform.m_local.v[3].z = 0;
	monkey.m_transform.m_local.v[3].w = 1;


	Turret banana(ro, shader, monkey);

	banana.m_transform.m_local = mat4MakeIdentity();

	banana.m_transform.m_local.v[3].y = 60;
	banana.m_torque = 1.5;

	float currentTime = 0;
	float deltaTime = 0;
	glfwSetTime(0);

	while (eref.step())
	{	
		deltaTime = Time::getInstance().getDeltaTime();
		
		monkey.draw(view, ortho);
		banana.draw(view, ortho);

		monkey.update(deltaTime, window, &banana);
		banana.update(deltaTime, window);

	}

	eref.term();
	return 0;
}