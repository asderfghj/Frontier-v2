#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <vector>
#include <memory>
#include "glm.hpp"
#include "Component.h"

namespace frontier
{
	class Entity;

	//!Class that tracks location information on an entity, added by default to an entity on intialisation.
	class Transform: public Component
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		std::vector<std::weak_ptr<Transform>> m_children;
		std::weak_ptr<Transform> m_transformParent;
		bool m_isChildOfOtherTransform;
		std::weak_ptr<Transform> m_self;
	public:
		//!Initialises the transform
		/*!
			\param _parent The parent of the component.
		*/
		void OnInit(std::weak_ptr<Entity> _parent) override;

		//!Initialises the transform
		/*!
			\param _parent The parent of the component.
			\param _position The initial position of the transform.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _position);

		//!Initialises the transform
		/*!
			\param _parent The parent of the component.
			\param _position The initial position of the transform.
			\param _rotation The initial rotation of the transform.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _position, glm::vec3 _rotation);

		//!Initialises the transform
		/*!
			\param _parent The parent of the component.
			\param _position The initial position of the transform.
			\param _rotation The initial rotation of the transform.
			\param _scale The initial scale of the transform.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);

		//!Returns the position.
		glm::vec3 GetPosition();

		//!Sets the position.
		/*!
			\param _pos New position.
		*/
		void SetPosition(glm::vec3 _pos);

		//!Returns the rotation.
		glm::vec3 GetRotation();

		//!Sets the rotation.
		/*!
			\param _rot New rotation.
		*/
		void SetRotation(glm::vec3 _rot);

		//!Returns the scale.
		glm::vec3 GetScale();

		//!Sets the scale.
		/*!
			\param _sca New scale.
		*/
		void SetScale(glm::vec3 _sca);

		//!Returns the model matrix.
		glm::mat4 GetModelMatrix();

		//!Returns the model matrix with a modified scale.
		/*!
			\param _scaleModifier The scale to multiple the current scale by.
		*/
		glm::mat4 GetModelMatrixModScale(glm::vec3 _scaleModifier);

		//!Returns a model matrix with just the position.
		/*!
			\param _excludeAxis Excludes a specifed axis 0 = none, 1 = x, 2 = y, 3 = z. 
		*/
		glm::mat4 GetPositionMatrix(int _excludeAxis = 0);

		//!Sets the transform parent, this is used for scene graphs.
		/*!
			\param _parent The parent of this transform.
		*/
		void SetTransformParent(std::weak_ptr<Transform> _parent);

		//!adds a child to the transform.
		/*!
			\param _child The new child for this transform.
		*/
		void AddChild(std::weak_ptr<Transform> _child);

		//!Sets the self pointer
		/*!
			\param _self A weak pointer to this transform.
		*/
		void SetSelf(std::weak_ptr<Transform> _self);
	};
}

#endif // !TRANSFORM_H_