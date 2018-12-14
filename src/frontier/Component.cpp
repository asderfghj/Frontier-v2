#include "Component.h"
#include "Entity.h"
#include "Core.h"
#include <iostream>

namespace frontier
{
	std::shared_ptr<Entity> Component::GetEntity()
	{
		return m_entity.lock();
	}

	std::shared_ptr<Core> Component::GetCore()
	{
		if (!m_entity.expired())
		{
			return m_entity.lock()->GetCore();
		}
		else
		{
			throw std::exception();
		}
	}

	std::shared_ptr<Input> Component::GetInput()
	{
		return GetCore()->GetInput();
	}

	std::shared_ptr<Environment> Component::GetEnvironment()
	{
		return GetCore()->GetEnvironment();
	}

	void Component::OnInit(std::weak_ptr<Entity> _parent)
	{
		m_entity = _parent;
	}

	void Component::OnActivate()
	{
		//Put activation code here in derived class.
	}

	void Component::OnTick()
	{
		//Put per frame code here in derived class.
	}

	bool Component::IsCopyable()
	{
		return m_copyable;
	}

}