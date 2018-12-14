#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <memory>
#include <map>
#include <SDL2/SDL.h>
#include "glm.hpp"

namespace frontier 
{
	class Core;
	
	//!Class for handling input, current input handled: keyboard, mouse, controller
	class Input
	{
	public:
		//!Enum for keyboard buttons, currently configured for current game.
		enum ListedButtons
		{
			W_KEY, //!<Bound to W button.
			S_KEY,	//!<Bound to S button.
			A_KEY,	//!<Bound to A button.
			D_KEY,	//!<Bound to D button.
			Q_KEY,		//!<Bound to Q button.
			E_KEY,	//!<Bound to E button.
			O_KEY,
			P_KEY,
			K_KEY,
			L_KEY,
			M_KEY,
			Z_KEY,
			X_KEY,
			ONE_KEY,
			TWO_KEY,
			THREE_KEY,
			FOUR_KEY,
			UP_KEY,
			DOWN_KEY,
			LEFT_KEY,
			RIGHT_KEY,
			ESC_KEY,	//!<Bound to esc.
			NUM_OF_BUTTONS	//!<Used for array size.
		};

		//!Enum for controller stick axes.
		enum ControllerAxes
		{
			LEFTSTICK,
			RIGHTSTICK
		};

		//!Enum for controller buttons.
		enum ControllerButtons
		{
			A_BUTTON,
			B_BUTTON,
			X_BUTTON,
			Y_BUTTON,
			LB_BUTTON,
			RB_BUTTON,
			BACK_BUTTON,
			START_BUTTON,
			NUM_OF_CONTROLLER_BUTTONS
		};

		//!Enum for controller d-pad states.
		enum DpadStates
		{
			DPAD_LEFTUP,
			DPAD_UP,
			DPAD_RIGHTUP,
			DPAD_LEFT,
			DPAD_CENTER,
			DPAD_RIGHT,
			DPAD_LEFTDOWN,
			DPAD_DOWN,
			DPAD_RIGHTDOWN,
			NUM_OF_STATES
		};

		//!Enum for mouse buttons.
		enum MouseButtonStates
		{
			LEFT_MOUSE_BUTTON,
			RIGHT_MOUSE_BUTTON,
			NUM_OF_MOUSE_BUTTON_STATES
		};


	private:
		std::weak_ptr<Core> _corePtr;

		//keyboard info
		const Uint8* m_sdlKeyboardState;
		uint8_t m_keys[NUM_OF_BUTTONS - 1] = { false };
		uint8_t m_controllerBtns[NUM_OF_CONTROLLER_BUTTONS - 1] = { false };
		uint8_t m_dpadStates[NUM_OF_STATES - 1] = { false };
		uint8_t m_mouseBtnStates[NUM_OF_MOUSE_BUTTON_STATES - 1] = { false };
		glm::vec2 m_mousePos;

		bool m_joystickConnected;
		SDL_Joystick* m_joystick;
		glm::vec2 m_leftStickAxes;
		glm::vec2 m_rightStickAxes;
		Sint16 m_leftTrigger;
		Sint16 m_rightTrigger;
		bool m_queueKeyboardUpdate, m_queueJoystickUpdate, m_queueJoystickButtonUpdate, m_queueDpadUpdate, m_queueMouseMovementUpdate, m_queueMouseButtonUpdate;

	public:
		//!Constructor for input, used for controller detection. 
		Input();
		
		//!Queries a key from the ListedButtons enum, false is key up, true is key down.
		/*!
			/param _keycode The keycode that needs to be queried.
		*/
		bool GetKey(ListedButtons _keycode);

		//!Queries a mouse button from the MouseButtonStates enum, false is key up, true is key down.
		/*!
			/param _btn The mouse button that needs to be queried.
		*/
		bool GetMouseButton(MouseButtonStates _btn);

		//!Returns the mouse position. 
		glm::vec2 GetMousePos();

		//!Queries a controller button from the ControllerButtons enum, false is key up, true is key down.
		/*!
			/param _btn The controller button that needs to be queried.
		*/
		bool GetJoystickButton(ControllerButtons _btn);

		//!Queries a dpad button from the DpadStates enum, false is key up, true is key down.
		/*!
			/param _state The dpad state that needs to be queried.
		*/
		bool GetJoystickDpadState(DpadStates _state);

		//!Queries a controller axis from the ControllerAxes enum, returns a vec2 of the controller joystick x and y.
		/*!
			/param _axis The axis that needs to be queried.
		*/
		glm::vec2 GetJoystickAxis(ControllerAxes _axis);

		//!Sets the core pointer
		/*!
			/param _core Pointer to the core.
		*/
		void SetCorePtr(std::weak_ptr<Core> _core);

		//!Queries if a controller is connected.
		bool IsJoystickConnected();

		//!Closes and joysicks attached.
		void FreeJoystick();

		//!Updates the left joystick position
		/*!
			\param _axes Left joystick position.
		*/
		void UpdateLeftJoystick(glm::vec2 _axes);

		//!Updates the right joystick position
		/*!
			\param _axes Right joystick position.
		*/
		void UpdateRightJoystick(glm::vec2 _axes);

		//!Updates inputs if any inputs have changed.
		void Tick();

		//!Queues update for mouse movement.
		void QueueMouseMovementUpdate();

		//!Queues update for mouse buttons.
		void QueueMouseButtonUpdate();

		//!Queues update for keyboard buttons.
		void QueueKeyboardUpdate();

		//!Queues update for controller joysticks.
		void QueueControllerJoystickUpdate();

		//!Queues update for controller buttons.
		void QueueControllerButtonUpdate();

		//!Queues update for the controller dpad.
		void QueueControllerDpadUpdate();
	};


}