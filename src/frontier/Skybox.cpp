#include "Skybox.h"
#include "Shader.h"
#include "Entity.h"
#include "Core.h"
#include "CubemapTexture.h"
#include "Camera.h"
#include <gtc/matrix_transform.hpp>

namespace frontier
{
	void Skybox::OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<CubemapTexture> _skyboxTexture)
	{
		Component::OnInit(_parent);
		m_texture = _skyboxTexture;

		m_skyboxVertices = {
			// cube positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_skyboxVertices.size(), &m_skyboxVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_shaderProgram = GetCore()->getSkyboxShader();

	}

	void Skybox::OnTick()
	{
		Component::OnTick();
	}

	void Skybox::Draw()
	{
		glDepthMask(false);
		m_shaderProgram->SetUniform("skybox", m_texture);
		m_texture->Bindtexture();

		glUseProgram(m_shaderProgram->GetID());

		m_shaderProgram->SetUniform("projection", GetEntity()->GetCore()->GetMainCamera()->GetProjectionMatrix());
		m_shaderProgram->SetUniform("view", glm::mat4(glm::mat3(GetEntity()->GetCore()->GetMainCamera()->GetViewMatrix())));
		glm::mat4 scaler = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, 50.0f));



		m_shaderProgram->SetUniform("scaler", scaler);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_skyboxVertices.size() / 3);
		glBindVertexArray(0);
		glUseProgram(0);
		glDepthMask(true);
	}
}