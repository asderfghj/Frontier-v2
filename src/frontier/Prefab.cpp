#include "Prefab.h"

namespace frontier
{
	void Prefab::Init(std::weak_ptr<Core> _coreptr)
	{
		m_core = _coreptr;
	}

	std::vector<std::shared_ptr<Component>> Prefab::getComponents()
	{
		return m_components;
	}

}