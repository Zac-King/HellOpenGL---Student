#include "GameObject.h"



void GameObject::draw(Matrix4 a_view, Matrix4 a_projection)
{
	glUseProgram(m_shader);
	GLuint ul_proj = glGetUniformLocation(m_shader, "Projection");
	GLuint ul_view = glGetUniformLocation(m_shader, "View");
	GLuint ul_model = glGetUniformLocation(m_shader, "Model");

	glUniformMatrix4fv(ul_proj, 1, GL_FALSE, a_projection.m);
	glUniformMatrix4fv(ul_view, 1, GL_FALSE, a_view.m);
	glUniformMatrix4fv(ul_model, 1, GL_FALSE, m_transform.getGlobal().m);

	glBindVertexArray(m_ro.VAO);
	glDrawElements(GL_TRIANGLES, m_ro.size, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glUseProgram(0);
}