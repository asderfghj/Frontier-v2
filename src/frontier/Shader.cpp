#include "Shader.h"
#include "Resources.h"
#include "Texture.h"
#include "CubemapTexture.h"
#include "graphicsextension/RenderTexture.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "gtc/type_ptr.hpp"


namespace frontier
{

	std::shared_ptr<Shader> Shader::Create(std::string _fragScr, std::string _vertScr, std::vector<GLchar*> _attributes, std::shared_ptr<Resources> _resources)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		std::shared_ptr<Shader> rtn = std::make_shared<Shader>();

		vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

		try
		{
			vShaderFile.open(_vertScr);
			fShaderFile.open(_fragScr);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();

			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch(std::ifstream::failure e)
		{
			std::cout << "Shader file not read" << std::endl;
		}

		GLint ShaderSuccess = 0;

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();


		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShaderID, 1, &vShaderCode, NULL);
		glCompileShader(vertexShaderID);
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &ShaderSuccess);

		if (!ShaderSuccess)
		{
			std::cout << "Vertex Shader compiler error" << std::endl;
			std::vector<char> errorlog(255);
			glGetShaderInfoLog(vertexShaderID, 255, NULL, errorlog.data());
			std::string errorString(errorlog.begin(), errorlog.end());
			std::cout << errorString << std::endl;
			throw std::exception();
		}

		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShaderID);
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &ShaderSuccess);

		if (!ShaderSuccess)
		{
			std::cout << "Fragment Shader compiler error" << std::endl;
			std::vector<char> errorlog(255);
			glGetShaderInfoLog(fragmentShaderID, 255, NULL, errorlog.data());
			std::string errorString(errorlog.begin(), errorlog.end());
			std::cout << errorString << std::endl;
			throw std::exception();
		}

		GLuint ProgramId = glCreateProgram();

		glAttachShader(ProgramId, vertexShaderID);
		glAttachShader(ProgramId, fragmentShaderID);

		for (size_t i = 0; i < _attributes.size(); i++)
		{
			glBindAttribLocation(ProgramId, i, _attributes[i]);
		}

		glLinkProgram(ProgramId);
		glGetProgramiv(ProgramId, GL_LINK_STATUS, &ShaderSuccess);


		if (!ShaderSuccess)
		{
			std::cout << "Shader Link Error" << std::endl;
			std::vector<char> errorlog(255);
			glGetShaderInfoLog(ProgramId, 255, NULL, errorlog.data());
			std::string errorString(errorlog.begin(), errorlog.end());
			std::cout << errorString << std::endl;
			throw std::exception();
		}

		glDetachShader(ProgramId, vertexShaderID);
		glDeleteShader(vertexShaderID);
		glDetachShader(ProgramId, fragmentShaderID);
		glDeleteShader(fragmentShaderID);

		rtn->SetID(ProgramId);

		_resources->AddCreatedResource(rtn);

		std::cout << "Shader Compiled and loaded" << std::endl;

		return rtn;

	}

	void Shader::SetUniform(const GLchar* _name, float _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform1f(UniformLocation, _value);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, int _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform1i(UniformLocation, _value);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, bool _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform1i(UniformLocation, _value);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, std::weak_ptr<Texture> _texture, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform1i(UniformLocation, _texture.lock()->GetTextureLocation());
	}

	void Shader::SetUniform(const GLchar* _name, std::weak_ptr<CubemapTexture> _texture, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform1i(UniformLocation, _texture.lock()->GetTextureLocation());
	}

	void Shader::SetUniform(const GLchar* _name, std::weak_ptr<RenderTexture> _texture, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform1i(UniformLocation, _texture.lock()->getTexLocation());
	}

	void Shader::SetUniform(const GLchar* _name, glm::mat4 _value, bool _transpose, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniformMatrix4fv(UniformLocation, 1, _transpose, glm::value_ptr(_value));
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, glm::vec2 _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform2fv(UniformLocation, 1, &_value[0]);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, glm::vec3 _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform3fv(UniformLocation, 1, &_value[0]);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, glm::vec4 _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(m_id, _name);
		glUseProgram(m_id);
		glUniform4fv(UniformLocation, 1, &_value[0]);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetID(GLuint _newID)
	{
		m_id = _newID;
	}

	GLuint Shader::GetID()
	{
		return m_id;
	}

}