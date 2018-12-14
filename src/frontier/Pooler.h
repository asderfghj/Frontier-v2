#include <string>
#include <memory>
#include <vector>
#include "glm.hpp"

namespace frontier
{
	class Prefab;
	class Entity;
	class Core;

	//!Creates a pool of entities
	/*!
		Rather than creating a new instance of an entity every time one is needed, this class creates several at once, switches them to inactive and actives them when the spawn function is called.
	*/
	class Pooler
	{
	private:
		std::string m_poolID;
		std::shared_ptr<Prefab> m_poolPrefab;
		std::vector<std::weak_ptr<Entity>> m_entities;
		int m_poolSize;
		std::weak_ptr<Core> m_corePtr;
		std::weak_ptr<Entity> AddNewEntity();
		

	public:
		//!Initialises the pooler.
		/*!
			\param _core Pointer to the core.
			\param _id Identifier for the pooler so that it can be refered back to later.
			\param _prefab The prefab that all entities in the pool will be created from.
			\param _initialPoolSize The initial number of entities that will be created.
		*/
		void OnInit(std::weak_ptr<Core> _core, std::string _id, std::shared_ptr<Prefab> _prefab, int _initialPoolSize);

		//!Spawns an entity from the pool and returns a pointer to it.
		/*!
			\param _position The initial position of the new entity.
			\param _modifyScale Whether the scale needs to be modified.
			\param _scale The initial scale of the new entity.
		*/
		std::weak_ptr<Entity> Spawn(glm::vec3 _position, bool _modifyScale = false, glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));

		//!Returns the pool identifier. 
		std::string GetID();

		//!Returns the number of active entities in the pool.
		int GetActiveInPool();

		//!Deactivates all active entities in the pool.
		void DeactivateAllInstances();

	};

}