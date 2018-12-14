#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <GL/glew.h>
#include <vector>
#include "glm.hpp"
#include "Component.h"

namespace frontier
{
	class Shader;
	//! A box collider, uses basic AABB collisions against other entities with a collider attached.
	/*!
		 If other colliders are intersecting, then the collider component will trigger a boolean to confirm the collsion and will store a vector of weak pointers to each entity colliding with this one. Currently the collider only works based on positions and scale, rotations are not applied.
	*/
	class Collider : public Component
	{
	private:
		glm::vec3 m_boxScale;
		int m_numOfVertices;
		bool m_colliding, m_drawWireframe;
		std::vector<std::weak_ptr<Entity>> m_collidingEntities;
		GLuint m_VAO, m_VBO;
		std::shared_ptr<Shader> m_shaderProgram;

	public:
		//!Initialises the collider component, this will be called by AddComponent in the Entity class, intialises the collider class with the box scale
		/*!
			\param _parent The entity that this component is attached to.
			\param _boxScale The scale of the collision box, this is relative to the scale in the transform component on the entity (Set to glm::vec3(1.0f, 1.0f, 1.0f) by default).
		*/
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _boxScale = glm::vec3(1.0f,1.0f,1.0f));

		//!Initialises the collider component, this will be called by AddComponent in the Entity class, this is a copy contructor used for making an entity from a prefab.
		/*!
			\param _parent The entity that this component is attached to.
			\param _original The original version of the component, typically taken from a prefab
		*/
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Collider> _original);

		//!Runs every frame, checks all other collider components to see if any are colliding.
		void OnTick() override;

		//!Checks against another entity's position and scale to determine whether this collider is collding with another.
		/*!
			\param _position The position of the other entity.
			\param _scale The scale of the other entity.
		*/
		bool CheckIfColliding(glm::vec3 _position, glm::vec3 _scale);

		//!Returns the vector of entities currently colliding with this collider.
		std::vector<std::weak_ptr<Entity>> GetCollidingEntities();

		//!Returns whether the collider is currently colliding with anything.
		bool IsColliding();

		//!Returns the box scale.
		glm::vec3 GetBoxScale();

	};

}

#endif