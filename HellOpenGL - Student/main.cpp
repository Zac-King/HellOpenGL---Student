#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>
#include "crenderutils.h"
#include "GameObject.h"
#include "TankStuff.h"

#define S_W 1280
#define S_H 720


int main()
{
	// OpenGL set up the window
	if (!glfwInit()) return -1;
	GLFWwindow* window;

	window = glfwCreateWindow(S_W, S_H, "Hello World", NULL, NULL);
	if (!window) { glfwTerminate(); return -1; }
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { glfwTerminate(); return -1; }
	////////////////////////////////////////////////////////////////////////
	auto major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
	auto minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
	auto revision = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
	printf("GL %i.%i.%i\n", major, minor, revision);
	////////////////////////////////////////////////////////////////////////
	
	/// Camera Information
	mat4 view = mat4MakeIdentity();
	mat4 ortho = getOrtho(0, S_W, 0, S_H, 0, 100);


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
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - currentTime;
		currentTime = glfwGetTime();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		monkey.draw(view, ortho);
		banana.draw(view, ortho);

		monkey.update(deltaTime, window);
		banana.update(deltaTime, window);
		//update functions also called here

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}