#include "PointLight.h"
#include "frontier/Shader.h"
#include "frontier/Entity.h"
#include "frontier/Transform.h"
#include "frontier/Core.h"
#include "LightController.h"
namespace frontier
{
	void PointLight::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic)
	{
		Light::OnInit(_parent, _ambient, _diffuse, _specular);
		m_constant = _constant;
		m_linear = _linear;
		m_quadratic = _quadratic;
		_parent.lock()->GetCore()->GetLightController()->AddPointLight(_parent);
	}

	void PointLight::SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index)
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

		std::string constantUniformID = _uniformName + arrayIndexStr + ".constant";

		_shader.lock()->SetUniform(constantUniformID.c_str(), m_constant);

		std::string linearUniformID = _uniformName + arrayIndexStr + ".linear";

		_shader.lock()->SetUniform(linearUniformID.c_str(), m_linear);

		std::string quadraticUniformID = _uniformName + arrayIndexStr + ".quadratic";

		_shader.lock()->SetUniform(quadraticUniformID.c_str(), m_quadratic);

	}

	void PointLight::SetLightUniformPBR(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index)
	{
		std::string arrayIndexStr = "";

		if (_index > -1)
		{
			arrayIndexStr = "[" + std::to_string(_index) + "]";
		}

		std::string positionUniformID = _uniformName + arrayIndexStr + ".position";

		_shader.lock()->SetUniform(positionUniformID.c_str(), GetEntity()->getComponent<Transform>()->GetPosition());

		std::string coloruniformID = _uniformName + arrayIndexStr + ".color";

		glm::vec3 modifiedColor = m_diffuse * 300.0f;

		_shader.lock()->SetUniform(coloruniformID.c_str(), modifiedColor);
	}

}