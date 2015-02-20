#pragma once
#include "Core.h"
#include "crenderutils.h"
#include <map>
#include <vector>
#include <string>

class Assets : public Core
{
private:
	Assets()	{}

	std::vector<TextureData> m_textures;
	std::vector<RenderObject>m_geometries;
	std::vector<GLuint>		 m_shaders;

	std::map<std::string, TextureData*>		m_texture_map;
	std::map<std::string, GLuint*>			m_shader_map;
	std::map<std::string, RenderObject*>	m_geometry_map;
protected:
	bool term()
	{
		for each(auto t in m_textures)
			glDeleteTextures(1, &t.handle);

		for each(auto g in m_geometries)
		{
			glDeleteBuffers		(1, &g.VBO);
			glDeleteBuffers		(1, &g.VBO);
			glDeleteVertexArrays(1, &g.VBO);
		}

		for each (auto s in m_shaders)
			glDeleteProgram(s);

		return true;
	}
public:
	static Assets &getInstance()	{ static Assets a; return a; }
	enum e_AssetType	{Texture, Shader, Geometry};
	////////////////////////////////////////
	void loadTextureData(char *a_name, char *a_path)
	{
		assert(m_texture_map.count(a_name) == 0); 
		m_textures.push_back(LoadTexture(a_path));	
		m_texture_map[a_name] = &m_textures.back();
	}
	//////////
	TextureData getTexture(char *a_name)
	{	assert(m_texture_map.count(a_name) == 1); return *m_texture_map[a_name];}
	////////////////////////////////////////
	void loadShaderData(char *a_name, char *a_vpath, const char *a_fpath)
	{
		m_shaders.push_back(CreateProgram(a_vpath, a_fpath));
		m_shader_map[a_name] = &m_shaders.back();
	}
	//////////
	GLuint getShader(char *a_name)
	{	return *m_shader_map[a_name];	}
	////////////////////////////////////////
	void loadGeometryData(char *a_name, Vertex *a_verts, unsigned nverts, Triangle *tris, unsigned ntris)
	{
		m_geometries.push_back(loadMesh(a_verts, nverts, tris, ntris));
		m_geometry_map[a_name] = &m_geometries.back();
	}
	//////////
	RenderObject getGeometry(char *a_name)
	{	return *m_geometry_map[a_name];	}

	TextureData  getTexture (char *a_name);
	GLuint		 getShader  (char *a_name);
	RenderObject getGeometry(char *a_name);
};