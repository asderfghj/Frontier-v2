#include <stb_image.h>
#include <iostream>
#include <exception>
#include "CubemapTexture.h"
#include "Resources.h"

namespace frontier
{
	std::shared_ptr<CubemapTexture> CubemapTexture::Create(std::vector<std::string> _paths, std::shared_ptr<Resources> _resources, int _textureLocation)
	{
		std::shared_ptr<CubemapTexture> rtn = std::make_shared<CubemapTexture>();
		GLuint rtnID;
		glActiveTexture(GL_TEXTURE0 + _textureLocation);
		glGenTextures(1, &rtnID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, rtnID);

		int width, height, nrChannels;
		unsigned char *data;
		stbi_set_flip_vertically_on_load(false);

		for (GLuint i = 0; i < _paths.size(); i++)
		{
			data = stbi_load(_paths[i].c_str(), &width, &height, &nrChannels, 3);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Failed to find texture" << std::endl;
				stbi_image_free(data);
				throw std::exception();
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glActiveTexture(GL_TEXTURE0);

		rtn->SetTexture(rtnID, _textureLocation);
		_resources->AddCreatedResource(rtn);
		return rtn;
	}

	void CubemapTexture::SetTexture(GLuint _newID, int _textureLocation)
	{
		m_id = _newID;
		m_textureLocation = _textureLocation;
	}

	GLuint CubemapTexture::GetTexture()
	{
		return m_id;
	}

	int CubemapTexture::GetTextureLocation()
	{
		return m_textureLocation;
	}

	void CubemapTexture::Bindtexture()
	{
		glActiveTexture(GL_TEXTURE0 + m_textureLocation);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	}



}
