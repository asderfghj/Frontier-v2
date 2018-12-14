#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <assert.h>
#include "Component.h"
#include "glm.hpp"
#include "Shader.h"

namespace frontier
{

	class Core;
	class Prefab;

	//!The base entity which components can be attached to.
	class Entity : std::enable_shared_from_this<Entity>
	{
	private:
		std::vector<std::shared_ptr<Component>> m_components;
		bool m_active = true;
		bool m_activating = false;

	protected:
		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;

	public:
		//!Destructor for Entity
		/*!
			Clears the component list.
		*/
		~Entity();

		//!Initialises the entity, sets the core pointer and adds a transform component.
		/*!
			\param _corePtr Pointer to the core, used for components.
		*/
		virtual void Init(std::weak_ptr<Core> _corePtr);

		//!Initialises the entity, sets the core pointer and adds a transform component and sets the initial parameters in the transform.
		/*!
			\param _corePtr Pointer to the core, used for components.
			\param _position Initial position for the transform component (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _rotation Initial rotation for the transform component (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _scale Initial scale for the transform component (set to glm::vec3(1.0f, 1.0f, 1.0f) by default).
		*/
		void Init(std::weak_ptr<Core> _corePtr, glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));

		//!Initialises the entity using a prefab, sets the core pointer and adds a transform component and sets the initial parameters in the transform.
		/*!
			\param _corePtr Pointer to the core, used for components.
			\param _prefab Prefab that the entity will be based off of.
			\param _position Initial position for the transform component (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _rotation Initial rotation for the transform component (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _scale Initial scale for the transform component (set to glm::vec3(1.0f, 1.0f, 1.0f) by default).
		*/
		void Init(std::weak_ptr<Core> _corePtr, std::shared_ptr<Prefab> _prefab, glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));

		//!Returns the core.
		std::shared_ptr<Core> GetCore();

		//!Updates all of the components in the entity, call handled by main.
		void Tick();

		void Draw();

		void DrawDepthMap(std::shared_ptr<Shader> _depthShader);

		//!Sets the pointer to the entity, call handled by main.
		/*!
			\param _selfPtr A pointer of the entity.
		*/
		void SetSelf(std::weak_ptr<Entity> _selfPtr);

		//!Set the entity to active or inactive, inactive entities to not run tick until they have been activated again.
		/*!
			\param _active Intended state of the entity.
		*/
		void SetActive(bool _active);

		//!Sets the activating state (handled internally)
		void SetActivating(bool _activating);

		//!Returns the active state.
		bool IsActive();

		//!Returns the activating state.
		bool IsActivating();

		//!Adds a component of the specified type with no additional parameters.
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();

			m_components.push_back(t);

			t->OnInit(m_self);
			return t;
		}

		//!Adds a copy of a component, usually taken from a prefab.
		template <typename T>
		std::shared_ptr<T> addCopyOfComponent(std::weak_ptr<T> _original)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();

			m_components.push_back(t);

			t->OnInit(m_self, _original);
			return t;
		}

		//!Adds a component of the specified type with one additional parameters.
		template <typename T, typename A>
		std::shared_ptr<T> AddComponent(A _a)
		{

			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component of the specified type with two additional parameters.
		template <typename T, typename A, typename B>
		std::shared_ptr<T> AddComponent(A _a, B _b)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component of the specified type with three additional parameters.
		template <typename T, typename A, typename B, typename C>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component of the specified type with four additional parameters.
		template <typename T, typename A, typename B, typename C, typename D>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c, D _d)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c, _d);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component of the specified type with five additional parameters.
		template <typename T, typename A, typename B, typename C, typename D, typename E>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c, D _d, E _e)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c, _d, _e);
			m_components.push_back(t);
			return t;
		}

		//!Adds a component of the specified type with six additional parameters.
		template <typename T, typename A, typename B, typename C, typename D, typename E, typename F>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c, D _d, E _e, F _f)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c, _d, _e, _f);
			m_components.push_back(t);
			return t;
		}

		template <typename T, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c, D _d, E _e, F _f, G _g)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c, _d, _e, _f, _g);
			m_components.push_back(t);
			return t;
		}

		template <typename T, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c, D _d, E _e, F _f, G _g, H _h)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c, _d, _e, _f, _g, _h);
			m_components.push_back(t);
			return t;
		}

		template <typename T, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
		std::shared_ptr<T> AddComponent(A _a, B _b, C _c, D _d, E _e, F _f, G _g, H _h, I _i)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(m_self, _a, _b, _c, _d, _e, _f, _g, _h, _i);
			m_components.push_back(t);
			return t;
		}

		//!Returns a component of the specified type if one exists.
		template <typename T>
		std::shared_ptr<T> getComponent()
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

		//!Queries whether a component of the specified type exists on the entity.
		template <typename T>
		bool hasComponent()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				std::shared_ptr<T> returnPtr = std::dynamic_pointer_cast<T>(m_components.at(i));

				if (returnPtr)
				{
					return true;
				}
			}

			return false;
		}

	};

}

#endif // !ENTITY_H_