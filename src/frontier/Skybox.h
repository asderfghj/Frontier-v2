#ifndef SKYBOX_H_
#define SKYBOX_H_


#include <memory>
#include <vector>
#include <GL/glew.h>

#include "Component.h"

namespace frontier
{
	class Entity;
	class CubemapTexture;
	class Shader;

	//!Creates a skybox that acts as a backdrop for the scene. This will not move as the camera move.
	class Skybox : public Component 
	{
	private:
		std::shared_ptr<CubemapTexture> m_texture;
		std::shared_ptr<Shader> m_shaderProgram;
		GLuint m_VBO, m_VAO;
		std::vector<GLfloat> m_skyboxVertices;

	public:
		//!Initialises the skybox with a cubemap texture.
		/*!
			\param _parent The entity that this component will be attached to.
			\param _skyboxTexture The texture that will be rendered on the skybox.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<CubemapTexture> _skyboxTexture);

		//!Draws the skybox.
		void OnTick() override;

		void Draw();

	};


}


#endif // !SKYBOX_H_