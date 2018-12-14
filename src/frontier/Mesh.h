#include "glm.hpp"
#include "Shader.h"
#include <string>
#include <vector>
#include <memory>
#include <glm.hpp>
#include <GL/glew.h>

namespace frontier
{
	class Model;
	class Texture;
	class LightController;
	class DepthMap;
	struct Material;
	struct TexturePack;


	//!Contains vertices, normals and texcoords loaded from an obj.
	class Mesh 
	{
	private:
		std::vector<GLfloat> m_vertices;
		std::vector<GLfloat> m_normals;
		std::vector<GLfloat> m_texCoords;
		unsigned int m_VAO, m_vertVBO, m_normVBO, m_texCoordVBO;
		void SetupMesh();
		void SetupMeshNoTexCoords();

	public:
		//!Constructor for a mesh, initialised with vertices, normals and texcoords.
		/*!
			\param _vertices Vertices from the obj model.
			\param _normals Normals from the obj model.
			\param _texCoords Texcoords from the obj model.
		*/
		Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals, std::vector<GLfloat> _texCoords);

		//!Constructor for a mesh, initialised with vertices and normals.
		/*!
			\param _vertices Vertices from the obj model.
			\param _normals Normals from the obj model.
		*/
		Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals);

		//!Draws the mesh.
		/*!
			\param _model The model matrix to draw the mesh to.
			\param _view The view matrix from a camera.
			\param _proj The projection matrix from a camera.
			\param _tex The texture for the model.
			\param _shader The shader for the model.
		*/
		void Draw(std::shared_ptr<Shader> _shader);

		void DrawDepthMap(glm::mat4 _model, glm::mat4 _lightspace, std::shared_ptr<Shader> _depthBufShader);

		void DrawPBR(std::shared_ptr<Shader> _shader);

	};





}