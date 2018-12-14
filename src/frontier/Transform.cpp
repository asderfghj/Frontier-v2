#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Transform.h"


namespace frontier
{
	void Transform::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_isChildOfOtherTransform = false;
	}

	void Transform::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _position)
	{
		Component::OnInit(_parent);
		m_position = _position;
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_isChildOfOtherTransform = false;
	}

	void Transform::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _position, glm::vec3 _rotation)
	{
		Component::OnInit(_parent);
		m_position = _position;
		m_rotation = _rotation;
		m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_isChildOfOtherTransform = false;
	}


	void Transform::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		Component::OnInit(_parent);
		m_position = _position;
		m_rotation = _rotation;
		m_scale = _scale;
		m_isChildOfOtherTransform = false;
	}


	glm::vec3 Transform::GetPosition()
	{
		return m_position;
	}

	void Transform::SetPosition(glm::vec3 _pos)
	{
		m_position = _pos;
	}

	glm::vec3 Transform::GetRotation()
	{
		return m_rotation;
	}

	void Transform::SetRotation(glm::vec3 _rot)
	{
		m_rotation = _rot;
	}

	glm::vec3 Transform::GetScale()
	{
		return m_scale;
	}

	void Transform::SetScale(glm::vec3 _sca)
	{
		m_scale = _sca;
	}

	glm::mat4 Transform::GetModelMatrix()
	{
		glm::mat4 rtn = glm::mat4(1.0f), trans = glm::mat4(1.0f), rotx = glm::mat4(1.0f), roty = glm::mat4(1.0f), rotz = glm::mat4(1.0f), sca = glm::mat4(1.0f);
		trans = glm::translate(trans, m_position);
		sca = glm::scale(sca, m_scale);
		rotx = glm::rotate(rotx, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		roty = glm::rotate(roty, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotz = glm::rotate(rotz, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	
		rtn =   trans * rotz * rotx * roty  * sca;


		if(m_isChildOfOtherTransform)
		{
			rtn = rtn * m_transformParent.lock()->GetModelMatrix();
		}

		return rtn;
	}

	glm::mat4 Transform::GetModelMatrixModScale(glm::vec3 _scaleModifier)
	{
		glm::vec3 modifiedScale = _scaleModifier * m_scale;

		glm::mat4 rtn = glm::mat4(1.0f), trans = glm::mat4(1.0f), rotx = glm::mat4(1.0f), roty = glm::mat4(1.0f), rotz = glm::mat4(1.0f), sca = glm::mat4(1.0f);
		trans = glm::translate(trans, m_position);
		sca = glm::scale(sca, modifiedScale);
		rotx = glm::rotate(rotx, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		roty = glm::rotate(roty, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotz = glm::rotate(rotz, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		rtn = trans * rotz * rotx * roty * sca;

		if (m_isChildOfOtherTransform)
		{
			rtn = rtn * m_transformParent.lock()->GetModelMatrix();
		}

		return rtn;
	}

	glm::mat4 Transform::GetPositionMatrix(int _excludeAxis)
	{
		glm::mat4 rtn;
		if (_excludeAxis == 1)
		{
			rtn = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, m_position.y, m_position.z));
		}
		else if (_excludeAxis == 2)
		{
			rtn = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, 0.0f, m_position.z));
		}
		else if (_excludeAxis == 3)
		{
			rtn = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
		}
		else
		{
			rtn = glm::translate(glm::mat4(1.0f), m_position);
		}
		return rtn;
	}

	void Transform::SetTransformParent(std::weak_ptr<Transform> _parent)
	{
		m_transformParent = _parent;
		m_isChildOfOtherTransform = true;
	}

	void Transform::AddChild(std::weak_ptr<Transform> _child)
	{
		m_children.push_back(_child);
		_child.lock()->SetTransformParent(m_self);
	}

	void Transform::SetSelf(std::weak_ptr<Transform> _self)
	{
		m_self = _self;
	}
}