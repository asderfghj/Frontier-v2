#include "Component.h"
#include "glm.hpp"

namespace frontier
{
	class UIImage;

	//!A UI button that will be in screen space.
	class UIButton : public Component
	{
	private:
		std::weak_ptr<UIImage> m_targetImage;
		glm::vec3 m_idleColor;
		glm::vec3 m_pressedColor;
		glm::vec3 m_overlapColor;
		bool m_buttonPressed;
		bool IsMouseOverlapping();

	public:
		//!Initialises the UI button
		/*!
			\param _parent The parent to this component.
		*/
		void OnInit(std::weak_ptr<Entity> _parent);

		//!Initialises the UI button with a UIImage as a target.
		/*!
			\param _parent The parent to this component.
			\param _targetImg The target image for the button.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<UIImage> _targetImg);

		//!Updates the Button.
		void OnTick() override;

		//!Sets a new target image
		/*!
			\param _targetImg The new target image for the button.
		*/
		void SetTargetImage(std::weak_ptr<UIImage> _newImage);

		//!Sets a new idle color for the button.
		void SetIdleColor(glm::vec3 _newIdleColor);

		//!Sets a new pressed color for the button.
		void SetPressedColor(glm::vec3 _newPressedColor);

		//!Sets a new overlap color for the button.
		void SetOverlapColor(glm::vec3 _newOverlapColor);
	};

}