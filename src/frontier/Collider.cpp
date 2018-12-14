#include "Collider.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>
#include <gtc/matrix_transform.hpp>



namespace frontier
{
	void Collider::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 boxscale)
	{
		Component::OnInit(_parent);
		//used for prefabs
		m_copyable = true;
		m_boxScale = boxscale;

		//initialisation of wireframe box for debugging.
		std::vector<GLfloat> colliderVertices = {
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

		m_numOfVertices = colliderVertices.size();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colliderVertices.size(), &colliderVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_shaderProgram = GetCore()->getHitboxShader();

		m_drawWireframe = false;
		m_colliding = false;
	}

	void Collider::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Collider> _original)
	{
		Component::OnInit(_parent);
		m_copyable = true;
		m_boxScale = _original.lock()->GetBoxScale();

		//initialisation of wireframe box for debugging.
		std::vector<GLfloat> colliderVertices = {
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

		m_numOfVertices = colliderVertices.size();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colliderVertices.size(), &colliderVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_shaderProgram = GetCore()->getHitboxShader();

		m_drawWireframe = false;
		m_colliding = false;
	}

	void Collider::OnTick()
	{
		Component::OnTick();
		m_collidingEntities.clear();
		std::vector<std::weak_ptr<Entity>> entitiesWithColliders = GetCore()->getEntitiesWithComponent<Collider>();
		for (size_t i = 0; i < entitiesWithColliders.size(); i++)
		{
			//checks every entity with a colldier for collsion
			if (entitiesWithColliders[i].lock()->getComponent<Collider>()->CheckIfColliding(GetEntity()->getComponent<Transform>()->GetPosition(), m_boxScale * GetEntity()->getComponent<Transform>()->GetScale()) && entitiesWithColliders[i].lock()->IsActive())
			{
				m_collidingEntities.push_back(entitiesWithColliders[i]);
			}
		}
		
		if (m_collidingEntities.size() > 1)
		{
			m_colliding = true;
		}
		else
		{
			m_colliding = false;
		}

		if (m_drawWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glUseProgram(m_shaderProgram->GetID());
			m_shaderProgram->SetUniform("projection", GetEntity()->GetCore()->GetMainCamera()->GetProjectionMatrix());
			m_shaderProgram->SetUniform("view", GetEntity()->GetCore()->GetMainCamera()->GetViewMatrix());

			glm::mat4 model = glm::mat4(1.0f), trans = glm::mat4(1.0f), sca = glm::mat4(1.0f);

			trans = glm::translate(trans, GetEntity()->getComponent<Transform>()->GetPosition());

			sca = glm::scale(sca, m_boxScale * GetEntity()->getComponent<Transform>()->GetScale());

			model = trans *  sca;

			m_shaderProgram->SetUniform("model", model);

			if (!m_colliding)
			{
				m_shaderProgram->SetUniform("color", glm::vec3(1.0f, 0.0f, 0.0f));
			}
			else
			{
				m_shaderProgram->SetUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
			}

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, m_numOfVertices);
			glBindVertexArray(0);
			glUseProgram(0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	}

	bool Collider::CheckIfColliding(glm::vec3 _position, glm::vec3 _scale)
	{

		return (glm::abs(GetEntity()->getComponent<Transform>()->GetPosition().x - _position.x) < (m_boxScale.x * GetEntity()->getComponent<Transform>()->GetScale().x + _scale.x)) &&
			   (glm::abs(GetEntity()->getComponent<Transform>()->GetPosition().y - _position.y) < (m_boxScale.y * GetEntity()->getComponent<Transform>()->GetScale().y + _scale.y)) &&
			   (glm::abs(GetEntity()->getComponent<Transform>()->GetPosition().z - _position.z) < (m_boxScale.z * GetEntity()->getComponent<Transform>()->GetScale().z + _scale.z));
	}

	std::vector<std::weak_ptr<Entity>> Collider::GetCollidingEntities()
	{
		return m_collidingEntities;
	}

	bool Collider::IsColliding()
	{
		return m_colliding;
	}

	glm::vec3 Collider::GetBoxScale()
	{
		return m_boxScale;
	}
}