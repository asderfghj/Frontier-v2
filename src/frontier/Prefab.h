#ifndef PREFAB_H_
#define PREFAB_H_

#include <vector>
#include <memory>
#include "Transform.h"
#include "Component.h"
#include "Entity.h"

namespace frontier
{
	class Core;

	//!Acts as a template for an entity, can be passed into a new entity and the information stored will pass on to the new entity.
	/*!
		Currently, only these components will be copied into an entity:
		-collider
		-mesh renderer (with mesh, textures and shaders)
		-asteroid behaviour
		-projectile behaviour
	*/
	class Prefab : public Entity
	{
	private:
		std::vector<std::shared_ptr<Component>> m_components;


	public:
		//!Initialises the Prefab.
		/*!
			\param _corePtr Pointer to the core.
		*/
		void Init(std::weak_ptr<Core> _corePtr) override;

		//!Returns a vector of components attached to the prefab.
		std::vector<std::shared_ptr<Component>> getComponents();

		//!Adds a component with no parameters in the initialiser.
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();

			m_components.push_back(t);

			t->OnInit(m_self);
			return t;
		}

		//!Adds a component with one parameters in the initialiser.
		template <typename T, typename A>
		std::shared_ptr<T> AddComponent(A _a)
		{

			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component with two parameters in the initialiser.
		template <typename T, typename A, typename B>
		std::shared_ptr<T> AddComponent(A _a, B _b)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component with three parameters in the initialiser.
		template <typename T, typename A, typename B, typename C>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component with four parameters in the initialiser.
		template <typename T, typename A, typename B, typename C, typename D>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c, D _d)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c, _d);
			m_components.push_back(t);
			return t;
		}

		//!Returns a component of the specified type if one is attached.
		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				std::shared_ptr<T> returnPtr = std::dynamic_pointer_cast<T>(m_components.at(i));

				if (returnPtr)
				{
					return returnPtr;
				}
			}
			throw std::exception();


		}

	};
}

#endif // !PREFAB_H_