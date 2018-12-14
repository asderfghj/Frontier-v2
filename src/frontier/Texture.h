#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Resource.h"
#include <memory>
#include <string>
#include <GL/glew.h>

namespace frontier
{
	class Resources;

	//!A container for an image, loaded externally.
	class Texture : public Resource
	{
	private:
		
		int m_width;
		int m_height;
	protected:
		GLuint m_id;
		int m_textureLocation;

	public:
		//!Creates the image.
		/*!
			\param _path The filepath for the image.
			\param _resources Pointer to the resources class.
			\param _textureLocation The location where the texture will be located on the GPU.
		*/
		static std::shared_ptr<Texture> Create(const char* _path, std::shared_ptr<Resources> _resources, int _textureLocation);

		//!Sets a new texture.
		/*!
			\param _newID The new ID for the texture.
			\param _textureLocation The location where the texture will be located on the GPU.
		*/
		void SetTexture(GLuint _newID, int _textureLocation);

		//!Gets the current Texture ID;
		GLuint GetTexture();

		//!Gets the current texture location.
		int GetTextureLocation();

		//!Binds the current texture.
		void BindTexture();

		//!Sets the width of the texture
		/*!
			\param _newWidth The new width of the texture.
		*/
		void SetWidth(int _newWidth);

		//!Sets the height of the texture
		/*!
			\param _newWidth The new height of the texture.
		*/
		void SetHeight(int _newHeight);

		//!Gets the current width of the texture.
		int GetWidth();

		//!Gets the current height of the texture.
		int GetHeight();
	};

}

#endif