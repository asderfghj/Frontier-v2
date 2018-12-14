#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Prefab.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "Skybox.h"
#include "game/AsteroidBehavior.h"
#include "game/ProjectileBehavior.h"
#include <iostream>

namespace frontier
{
	Entity::~Entity()
	{
		m_components.clear();
	}

	void Entity::Tick()
	{
		if (m_active)
		{
			for each (std::shared_ptr<Component> _c in m_components)
			{
				_c->OnTick();
			}
		}

	}

	void Entity::Draw()
	{
		if (m_active)
		{
			if (hasComponent<MeshRenderer>())
			{
				if (GetCore()->getShaderMode() == Core::BLINN_PHONG)
				{
					getComponent<MeshRenderer>()->Draw();
				}
				else
				{
					getComponent<MeshRenderer>()->DrawPBR();
				}
			}
			else if (hasComponent<Skybox>())
			{
				getComponent<Skybox>()->Draw();
			}
		}
	}

	void Entity::DrawDepthMap(std::shared_ptr<Shader> _depthShader)
	{
		if (m_active)
		{
			if (hasComponent<MeshRenderer>())
			{
				getComponent<MeshRenderer>()->DrawDepthMap(_depthShader);
			}
		}
	}

	void Entity::Init(std::weak_ptr<Core> _corePtr)
	{
		m_core = _corePtr;
		std::shared_ptr<Transform> trans = AddComponent<Transform>();
		trans->SetSelf(trans);
	}

	void Entity::Init(std::weak_ptr<Core> _corePtr, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		m_core = _corePtr;
		AddComponent<Transform, glm::vec3, glm::vec3, glm::vec3>(_position, _rotation, _scale);
	}

	void Entity::Init(std::weak_ptr<Core> _corePtr, std::shared_ptr<Prefab> _prefab, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		m_core = _corePtr;
		AddComponent<Transform, glm::vec3, glm::vec3, glm::vec3>(_position, _rotation, _scale);
		for (size_t i = 0; i < _prefab->getComponents().size(); i++)
		{

			if (typeid(*_prefab->getComponents()[i]).name() == typeid(MeshRenderer).name())
			{
				addCopyOfComponent<MeshRenderer>(_prefab->GetComponent<MeshRenderer>());
			}

			else if (typeid(*_prefab->getComponents()[i]).name() == typeid(Collider).name())
			{
				addCopyOfComponent<Collider>(_prefab->GetComponent<Collider>());
			}

			else if (typeid(*_prefab->getComponents()[i]).name() == typeid(AsteroidBehavior).name())
			{
				AddComponent<AsteroidBehavior>();
			}

			else if (typeid(*_prefab->getComponents()[i]).name() == typeid(ProjectileBehavior).name())
			{
				addCopyOfComponent<ProjectileBehavior>(_prefab->GetComponent<ProjectileBehavior>());
			}

			else
			{
				std::cout << "WARNING: Component type: " << typeid(*_prefab->getComponents()[i]).name() << " is not copyable, it will not be added to this enitity" << std::endl;
			}
		}
	}

	void Entity::SetSelf(std::weak_ptr<Entity> _selfPtr)
	{
		m_self = _selfPtr;
	}

	void Entity::SetActive(bool _active)
	{
		if (_active && !m_active)
		{
			m_active = _active;
			for (size_t i = 0; i < m_components.size(); i++)
			{
				m_components[i]->OnActivate();
			}
		}
		else
		{
			m_active = _active;
		}
	}

	void Entity::SetActivating(bool _activating)
	{
		m_activating = _activating;
	}

	bool Entity::IsActive()
	{
		return m_active;
	}

	bool Entity::IsActivating()
	{
		return m_activating;
	}

	std::shared_ptr<Core> Entity::GetCore()
	{
		return m_core.lock();
	}

}