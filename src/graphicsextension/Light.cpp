#include "Light.h"
#include "frontier/Shader.h"
#include "frontier/Entity.h"
#include "frontier/Transform.h"

namespace frontier
{
	void Light::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular)
	{
		Component::OnInit(_parent);
		m_ambient = _ambient;
		m_diffuse = _diffuse;
		m_specular = _specular;
	}

	void Light::SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index)
	{
		std::string arrayIndexStr = "";

		if (_index > -1)
		{
			arrayIndexStr = "[" + std::to_string(_index) + "]";
		}

		std::string positionUniformID = _uniformName + arrayIndexStr + ".position";

		_shader.lock()->SetUniform(positionUniformID.c_str(), GetEntity()->getComponent<Transform>()->GetPosition());

		std::string ambientUniformID = _uniformName + arrayIndexStr + ".ambient";

		_shader.lock()->SetUniform(ambientUniformID.c_str(), m_ambient);

		std::string diffuseUniformID = _uniformName + arrayIndexStr + ".diffuse";

		_shader.lock()->SetUniform(diffuseUniformID.c_str(), m_diffuse);

		std::string specularUniformID = _uniformName + arrayIndexStr + ".specular";

		_shader.lock()->SetUniform(specularUniformID.c_str(), m_specular);
	}
}