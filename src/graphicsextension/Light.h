#ifndef LIGHT_H_
#define LIGHT_H_

#include "frontier/Component.h"
#include "glm.hpp"
#include <string>

namespace frontier
{
	class Shader;

	class Light : public Component
	{
	protected:
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
	public:
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular);
		virtual void SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index = -1);

	};

}

#endif // !LIGHT_H_