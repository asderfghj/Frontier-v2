#include "Mesh.h"
#include "Model.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
#include "Camera.h"
#include "Texture.h"
#include "graphicsextension/LightController.h"
#include "graphicsextension/DepthMap.h"
#include <GL/glew.h>

namespace frontier
{
	void Mesh::SetupMesh()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_vertVBO);
		glGenBuffers(1, &m_normVBO);
		glGenBuffers(1, &m_texCoordVBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertices.size(), &m_vertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, m_normVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_normals.size(), &m_normals.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_texCoords.size(), &m_texCoords.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::SetupMeshNoTexCoords()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_vertVBO);
		glGenBuffers(1, &m_normVBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertices.size(), &m_vertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, m_normVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_normals.size(), &m_normals.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals, std::vector<GLfloat> _texcoords)
	{
		m_vertices = _vertices;
		m_normals = _normals;
		m_texCoords = _texcoords;
		SetupMesh();
	}

	Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals)
	{
		m_vertices = _vertices;
		m_normals = _normals;
		SetupMeshNoTexCoords();
	}

	void Mesh::Draw(std::shared_ptr<Shader> _shader)
	{
		glUseProgram(_shader->GetID());

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
		glBindVertexArray(0);
		glUseProgram(0);

	}

	void Mesh::DrawDepthMap(glm::mat4 _model, glm::mat4 _lightspace, std::shared_ptr<Shader> _depthBufShader)
	{
		glUseProgram(_depthBufShader->GetID());

		_depthBufShader->SetUniform("lightSpaceMatrix", _lightspace);
		_depthBufShader->SetUniform("model", _model);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void Mesh::DrawPBR(std::shared_ptr<Shader> _shader)
	{
		glUseProgram(_shader->GetID());
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
		glBindVertexArray(0);
		glUseProgram(0);
	}


}