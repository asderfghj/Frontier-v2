#include "UIButton.h"
#include "UIImage.h"
#include "Input.h"
#include "Entity.h"
#include "Transform.h"
#include <iostream>

namespace frontier
{

	void UIButton::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		if (_parent.lock()->hasComponent<UIImage>())
		{
			m_targetImage = _parent.lock()->getComponent<UIImage>();
			
		}
	}

	void UIButton::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<UIImage> _targetImg)
	{
		Component::OnInit(_parent);
		m_targetImage = _targetImg;
	}

	void UIButton::OnTick()
	{
		if (IsMouseOverlapping() && GetInput()->GetMouseButton(Input::LEFT_MOUSE_BUTTON))
		{
			std::cout << "Button Clicked" << std::endl;
			if (!m_targetImage.expired())
			{
				m_targetImage.lock()->SetColor(glm::vec4(m_pressedColor, 1.0f));
			}
		}
		else if (IsMouseOverlapping())
		{
			if (!m_targetImage.expired())
			{
				m_targetImage.lock()->SetColor(glm::vec4(m_overlapColor, 1.0f));
			}
		}
		else
		{
			if (!m_targetImage.expired())
			{
				m_targetImage.lock()->SetColor(glm::vec4(m_idleColor, 1.0f));
			}
		}
	}

	void UIButton::SetTargetImage(std::weak_ptr<UIImage> _newImage)
	{
		m_targetImage = _newImage;
	}

	void UIButton::SetIdleColor(glm::vec3 _newIdleColor)
	{
		m_idleColor = _newIdleColor;
	}

	void UIButton::SetPressedColor(glm::vec3 _newPressedColor)
	{
		m_pressedColor = _newPressedColor;
	}

	void UIButton::SetOverlapColor(glm::vec3 _newOverlapColor)
	{
		m_overlapColor = _newOverlapColor;
	}

	bool UIButton::IsMouseOverlapping()
	{
		return (glm::abs(GetEntity()->getComponent<Transform>()->GetPosition().x - GetInput()->GetMousePos().x) < GetEntity()->getComponent<Transform>()->GetScale().x) &&
			(glm::abs(GetEntity()->getComponent<Transform>()->GetPosition().y - GetInput()->GetMousePos().y) < GetEntity()->getComponent<Transform>()->GetScale().y);
	}

}