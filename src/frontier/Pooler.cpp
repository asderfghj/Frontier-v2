#include "Pooler.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"

namespace frontier
{
	std::weak_ptr<Entity> Pooler::AddNewEntity()
	{
		std::weak_ptr<Entity> rtn = m_corePtr.lock()->AddEntity(m_poolPrefab);
		rtn.lock()->SetActive(false);
		m_entities.push_back(rtn);
		return rtn;
	}

	void Pooler::OnInit(std::weak_ptr<Core> _core, std::string _id, std::shared_ptr<Prefab> _prefab, int initialPoolSize)
	{
		m_corePtr = _core;
		m_poolID = _id;
		m_poolPrefab = _prefab;
		for (int i = 0; i < initialPoolSize; i++)
		{
			AddNewEntity();
		}
	}

	std::weak_ptr<Entity> Pooler::Spawn(glm::vec3 _position, bool _modifyScale, glm::vec3 _scale)
	{
		std::weak_ptr<Entity> newObject;
		bool objectFound = false;

		for (size_t i = 0; i < m_entities.size(); i++)
		{
			if (!m_entities[i].lock()->IsActive() && !m_entities[i].lock()->IsActivating())
			{
				newObject = m_entities[i];
				objectFound = true;
				newObject.lock()->SetActivating(true);
				break;
			}
		}

		if (!objectFound)
		{
			newObject = AddNewEntity();
		}

		newObject.lock()->getComponent<Transform>()->SetPosition(_position);
		if (_modifyScale)
		{
			newObject.lock()->getComponent<Transform>()->SetScale(_scale);
		}
		m_corePtr.lock()->AddToEntitiesToActivate(newObject.lock());
		return newObject;
	}

	std::string Pooler::GetID()
	{
		return m_poolID;
	}

	int Pooler::GetActiveInPool()
	{
		int activeObjects = 0;
		for (size_t i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i].lock()->IsActive())
			{
				activeObjects++;
			}
		}

		return activeObjects;
	}

	void Pooler::DeactivateAllInstances()
	{
		for (size_t i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i].lock()->IsActive())
			{
				m_entities[i].lock()->SetActive(false);
			}
		}
	}

}