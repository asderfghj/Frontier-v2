#include "Component.h"
#include "glm.hpp"
#include <GL/glew.h>

namespace frontier
{
	class Texture;
	class Shader;

	//!A UI image that will appear in screen space rather than world space.
	class UIImage : public Component
	{
	private:
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Texture> m_texture;
		glm::vec4 m_color;
		GLuint m_VAO, m_posVBO, m_texVBO, m_verticesCount;
		bool m_preserveAspect, m_customShader;
		void InitialiseQuad();

	public:
		//!Initialises the UI Image.
		/*!
			\param _parent The entity that this compoenent will attach to.
		*/
		void OnInit(std::weak_ptr<Entity> _parent);

		//!Initialises the UI Image with a texture.
		/*!
			\param _parent The entity that this compoenent will attach to.
			\param _newTexture The texture that will be attached to the entity.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Texture> _newTexture, bool _preserveAspect = false);

		//!Draws the image.
		void OnTick() override;

		//!Attaches a new shader to the UIImage.
		void AttachShader(std::shared_ptr<Shader> _newShader);

		//!Attaches a new texture to the UIImage.
		void AttachTexture(std::shared_ptr<Texture> _newTexture, bool _preserveAspect = false);

		//!Sets a new color for the UIImage.
		void SetColor(glm::vec4 _newColor);

	};
}