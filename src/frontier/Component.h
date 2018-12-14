#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <memory>

namespace frontier
{

	class Entity;
	class Core;
	class Input;
	class Environment;

	//!Base component class, use for inheritance to other classes only. Useless on its own.
	class Component
	{
	private:
		std::weak_ptr<Entity> m_entity;

	protected:
		//!Returns a pointer to the core.
		std::shared_ptr<Core> GetCore();

		//!Returns a pointer to the input class.
		std::shared_ptr<Input> GetInput();

		//!Returns a pointer to the environment class.
		std::shared_ptr<Environment> GetEnvironment();

		//!Determines if a component has a copy constructor.
		bool m_copyable = false;

	public:
		//!Initialises the component. Sets the pointer to the entity that this component is attached to.
		/*!
			\param _parent The entity that the component will be attached to.
		*/
		virtual void OnInit(std::weak_ptr<Entity> _parent);

		//!Called when an entity's active state is changed from false to true.
		virtual void OnActivate();

		//!Called every frame, use for data that needs to be calculated each frame.
		virtual void OnTick();

		//!Returns the entity that this component is attached to.
		std::shared_ptr<Entity> GetEntity();

		//!Returns if the class is copyable for a prefab.
		bool IsCopyable();
	};
}
#endif