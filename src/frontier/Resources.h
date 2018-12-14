#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <list>
#include <memory>
#include "Resource.h"

namespace frontier
{
	//!The resources manager. Holds pointers of all created resources.
	class Resources
	{
	private:
		std::list<std::shared_ptr<Resource>> m_resources;

	public:
		//!Destructor for the Resources, clears the resources list.
		~Resources();

		//!Adds the created resource to the resources list
		/*!
			\param _resource Pointer to the resource to be added.
		*/
		void AddCreatedResource(std::shared_ptr<Resource> _resource);
	};
}

#endif // !RESOURCES_H_