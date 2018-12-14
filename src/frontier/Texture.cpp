#include <iostream>
#include "Texture.h"
#include "Resources.h"
#define STB_IMAGE_IMPLEMENTATION  
#include "stb_image.h"


namespace frontier
{
	std::shared_ptr<Texture> Texture::Create(const char* _path, std::shared_ptr<Resources> _resources, int _textureLocation)
	{
		std::shared_ptr<Texture> rtn = std::make_shared<Texture>();
		GLuint rtnID;
		glActiveTexture(GL_TEXTURE0 + _textureLocation);
		glGenTextures(1, &rtnID);
		glBindTexture(GL_TEXTURE_2D, rtnID);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(_path, &width, &height, &nrChannels, 4);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			throw std::exception();
		}
		rtn->SetWidth(width);
		rtn->SetHeight(height);
		stbi_image_free(data);


		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);

		rtn->SetTexture(rtnID, _textureLocation);
		_resources->AddCreatedResource(rtn);
		std::cout << "Texture Loaded" << std::endl;
		return rtn;
	}

	void Texture::SetTexture(GLuint _newID, int _textureLocation)
	{
		m_id = _newID;
		m_textureLocation = _textureLocation;
	}

	GLuint Texture::GetTexture()
	{
		return m_id;
	}

	int Texture::GetTextureLocation()
	{
		return m_textureLocation;
	}

	void Texture::BindTexture()
	{
		glActiveTexture(GL_TEXTURE0 + m_textureLocation);
		glBindTexture(GL_TEXTURE_2D, m_id);

	}

	void Texture::SetWidth(int _newWidth)
	{
		m_width = _newWidth;
	}

	void Texture::SetHeight(int _newHeight)
	{
		m_height = _newHeight;
	}

	int Texture::GetWidth()
	{
		return m_width;
	}

	int Texture::GetHeight()
	{
		return m_height;
	}
}
