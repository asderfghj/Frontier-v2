#include "Resources.h"
#include <iostream>

namespace frontier
{

	Resources::~Resources()
	{
		m_resources.clear();
		std::cout << "Resources Destroyed" << std::endl;
	}

	void Resources::AddCreatedResource(std::shared_ptr<Resource> _resource)
	{
		m_resources.push_back(_resource);
	}
}