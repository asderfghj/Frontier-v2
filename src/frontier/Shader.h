#ifndef SHADER_H_
#define SHADER_H_

#include "glm.hpp"
#include <GL/glew.h>
#include <memory>
#include <vector>
#include "Resource.h"

namespace frontier
{
	class Texture;
	class Resources;
	class CubemapTexture;
	class RenderTexture;

	//!A container for a shader. Compiles a shader from filepaths.
	class Shader : public Resource
	{
	private:
		GLuint m_id;

	public:
		//!Creates and compiles a new shader and returns a pointer
		/*!
			\param _fragSrc The filepath of the fragment shader.
			\param _vertSrc The filepath of the vertex shader.
			\param _attributes A list of the attributes used in the shader.
			\param _resources A pointer to the resources class so that the shader can be refered back to later.
		*/
		static std::shared_ptr<Shader> Create(std::string _fragScr, std::string _vertScr, std::vector<GLchar*> _attributes, std::shared_ptr<Resources> _resources);
		
		//!Sets a float uniform
		/*!
			\param _name The name of the uniform
			\param _value The value of the uniform
			\param _unsetProgram Whether to set openGL back to a null shader after the uniform has been set.
		*/
		void SetUniform(const GLchar *_name, float _value, bool _unsetProgram = false);

		//!Sets an int uniform
		/*!
			\param _name The name of the uniform
			\param _value The value of the uniform
			\param _unsetProgram Whether to set openGL back to a null shader after the uniform has been set.
		*/
		void SetUniform(const GLchar *_name, int _value, bool _unsetProgram = false);

		void SetUniform(const GLchar *_name, bool _value, bool _unsetProgram = false);

		//!Sets a texture uniform
		/*!
			\param _name The name of the uniform
			\param _texture The value of the uniform
			\param _unsetProgram Whether to set openGL back to a null shader after the uniform has been set.
		*/
		void SetUniform(const GLchar *_name, std::weak_ptr<Texture> _texture, bool _unsetProgram = false);

		//!Sets a cubemap uniform
		/*!
			\param _name The name of the uniform
			\param _texture The value of the uniform
			\param _unsetProgram Whether to set openGL back to a null shader after the uniform has been set.
		*/
		void SetUniform(const GLchar *_name, std::weak_ptr<CubemapTexture> _texture, bool _unsetprogram = false);

		void SetUniform(const GLchar *_name, std::weak_ptr<RenderTexture> _texture, bool _unsetprogram = false);

		//!Sets a mat4 uniform
		/*!
			\param _name The name of the uniform
			\param _value The value of the uniform
			\param _unsetProgram Whether to set openGL back to a null shader after the uniform has been set.
			\param _transpose Whether the matrix should be transposed or not
		*/
		void SetUniform(const GLchar *_name, glm::mat4 _value, bool _unsetProgram = false, bool _transpose = false);

		void SetUniform(const GLchar *_name, glm::vec2 _value, bool _unsetProgram = false);

		//!Sets a vec3 uniform
		/*!
			\param _name The name of the uniform
			\param _value The value of the uniform
			\param _unsetProgram Whether to set openGL back to a null shader after the uniform has been set.
		*/
		void SetUniform(const GLchar *_name, glm::vec3 _value, bool _unsetProgram = false);

		//!Sets a vec4 uniform
		/*!
			\param _name The name of the uniform
			\param _value The value of the uniform
			\param _unsetProgram Whether to set openGL back to a null shader after the uniform has been set.
		*/
		void SetUniform(const GLchar *_name, glm::vec4 _value, bool _unsetProgram = false);

		//!Sets a new ID for the Shader
		/*!
			\param _newID The new ID for the shader.
		*/
		void SetID(GLuint _newID);

		//!Returns the current ID for the Shader.
		GLuint GetID();

	};

}

#endif // !SHADER_H_