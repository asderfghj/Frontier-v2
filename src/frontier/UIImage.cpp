#include "UIImage.h"
#include "Entity.h"
#include "Core.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Transform.h"

namespace frontier
{
	void UIImage::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		m_shader = _parent.lock()->GetCore()->getUntexturedUiImageShader();
		m_preserveAspect = false;
		m_customShader = false;
		m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		InitialiseQuad();
	}

	void UIImage::OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Texture> _newtexture, bool _preserveAspect)
	{
		Component::OnInit(_parent);
		m_shader = _parent.lock()->GetCore()->getTexturedUiImageShader();
		m_preserveAspect = _preserveAspect;
		m_customShader = false;
		m_texture = _newtexture;
		m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		InitialiseQuad();
	}

	void UIImage::OnTick()
	{
		glEnable(GL_BLEND);
		if (m_texture)
		{
			m_shader->SetUniform("texture", m_texture);
			m_texture->BindTexture();
		}

		glUseProgram(m_shader->GetID());

		m_shader->SetUniform("ortho", GetCore()->GetMainCamera()->GetOrthographicMatrix());
		if (m_preserveAspect)
		{
			m_shader->SetUniform("model", GetEntity()->getComponent<Transform>()->GetModelMatrixModScale(glm::vec3(m_texture->GetWidth(), m_texture->GetHeight(), 1.0f)));
		}
		else
		{
			m_shader->SetUniform("model", GetEntity()->getComponent<Transform>()->GetModelMatrix());
		}
		m_shader->SetUniform("color", m_color);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_verticesCount / 3);
		glBindVertexArray(0);
		glUseProgram(0);
		glDisable(GL_BLEND);

	}

	void UIImage::AttachShader(std::shared_ptr<Shader> _newShader)
	{
		m_shader = _newShader;
		m_customShader = true;
	}

	void UIImage::AttachTexture(std::shared_ptr<Texture> _newTexture, bool _preserveAspect)
	{
		m_texture = _newTexture;
		m_preserveAspect = _preserveAspect;
		if (!m_customShader)
		{
			if (m_texture)
			{
				m_shader = GetEntity()->GetCore()->getTexturedUiImageShader();
			}
			else
			{
				m_shader = GetEntity()->GetCore()->getUntexturedUiImageShader();
			}
		}
	}

	void UIImage::SetColor(glm::vec4 _newColor)
	{
		m_color = _newColor;
	}

	void UIImage::InitialiseQuad()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_posVBO);
		glGenBuffers(1, &m_texVBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);

		std::vector<GLfloat> verts = {
			-1.0f,  1.0f,  0.0f,
			 1.0f,  1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f,

			 1.0f, -1.0f,  0.0f,
			-1.0f, -1.0f,  0.0f,
			-1.0f,  1.0f,  0.0f
		};

		m_verticesCount = verts.size();

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts.size(), &verts.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		if (m_texture)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_texVBO);

			std::vector<GLfloat> texcoords = {
				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f,

				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texcoords.size(), &texcoords.at(0), GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		}


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
}