#include "RenderTexture.h"
#include <exception>
#include <iostream>

namespace frontier
{
	RenderTexture::RenderTexture()
	{

	}

	RenderTexture::RenderTexture(int width, int height, int textureLocation)
	{
		m_FBO = 0;
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		glGenTextures(1, &m_texID);

		glBindTexture(GL_TEXTURE_2D, m_texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_FLOAT, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		GLuint depthRBO = 0;
		glGenRenderbuffers(1, &depthRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRBO);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texID, 0);

		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers);

		m_width = width;
		m_height = height;
		m_textureLocation = textureLocation;

	}

	GLuint RenderTexture::GetRenderTextureID()
	{
		return m_FBO;
	}

	void RenderTexture::Clear()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderTexture::BindRenderTexture()
	{
		glEnable(GL_CULL_FACE);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glViewport(0, 0, m_width, m_height);
	}

	void RenderTexture::UnbindRenderTexture()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_CULL_FACE);
		glViewport(0, 0, 1000, 800);
	}

	void RenderTexture::BindTexture()
	{
		glActiveTexture(GL_TEXTURE0 + m_textureLocation);
		glBindTexture(GL_TEXTURE_2D, m_texID);
	}

	GLuint RenderTexture::getTextureID()
	{
		return m_texID;
	}

	int RenderTexture::getTexLocation()
	{
		return m_textureLocation;
	}

	int RenderTexture::getWidth()
	{
		return m_width;
	}

	int RenderTexture::getHeight()
	{
		return m_height;
	}

}