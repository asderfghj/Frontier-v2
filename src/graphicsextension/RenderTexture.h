#ifndef RENDERTEXTURE_H_
#define RENDERTEXTURE_H_

#include <GL/glew.h>
#include "frontier/Texture.h"

namespace frontier
{
	class RenderTexture
	{
	protected:
		GLuint m_FBO, m_texID;
		int m_width, m_height, m_textureLocation;
	public:
		RenderTexture();
		RenderTexture(int width, int height, int textureLocation);
		GLuint GetRenderTextureID();
		void Clear();
		void BindRenderTexture();
		void UnbindRenderTexture();
		void BindTexture();
		GLuint getTextureID();
		int getTexLocation();
		int getWidth();
		int getHeight();
	};
}

#endif