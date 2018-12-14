#include "Light.h"
#include "glm.hpp"
#include <string>

namespace frontier
{

	class PointLight : public Light
	{
	private:
		float m_constant;
		float m_linear;
		float m_quadratic;
	public:
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic);
		void SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index = -1) override;
		void SetLightUniformPBR(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index = -1);

	};

}