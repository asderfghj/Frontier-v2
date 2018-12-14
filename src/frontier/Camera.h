#ifndef CAMERA_H_
#define CAMERA_H_


#include "glm.hpp"

#include "Component.h"

namespace frontier
{
	class Transform;
	//!Provides the view, projection and orthographic matricies for drawing objects to the screen.
	class Camera: public Component
	{

	private:
		bool m_isMainCamera;
		float m_FOV;
		float m_near;
		float m_far;
		bool m_isCustomViewMatrix;
		glm::mat4 m_CustomViewMatrix;

	public:
		//!Initialises the camera component, this will be called by AddComponent in the Entity class, initialises the field of view, near and far variables.
		/*!
			\param _parent The entity that this component is attached to.
			\param _fov The field of view for the camera (used in the projection matrix).
			\param _near The near plane for the camera.
			\param _far The far plane for the camera.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, float _fov, float _near, float _far);

		//!Returns a view matrix based on the inverse of the camera entity's model matrix.
		glm::mat4 GetViewMatrix();


		void SetCustomViewMatrix(glm::mat4 _newViewMatrix);


		void UnsetCustomViewMatrix();

		//!Returns a projection matrix based on the field of view, near and far variables provided on initalisation.
		glm::mat4 GetProjectionMatrix();

		//!Returns an orthographic matrix based on the screen size and the near and far variables provided at initialisation.
		glm::mat4 GetOrthographicMatrix();

		//!Queries whether this camera is the main one that is being used for drawing.
		bool IsMainCamera();

		//!Sets the isMainCamera value, Unless you have a good reason, do not change this. this is handled by the Core.
		/*!
			\param _main The new value for m_isMainCamera.
		*/
		void SetIsMainCamera(bool _main);

	};
}

#endif // !CAMERA_H_