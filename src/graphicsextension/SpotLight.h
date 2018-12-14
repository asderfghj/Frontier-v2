#include "Light.h"

namespace frontier
{
	class SpotLight : public Light
	{
	private:
		glm::vec3 m_direction;
		float m_constant;
		float m_linear;
		float m_quadratic;
		float m_cutoff;
		float m_outerCutoff;
	public:
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction, float _constant, float _linear, float _quadratic, float _cutoff, float _outerCutoff);
		void SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index = -1) override;
		void setCutoffs(float _inner, float _outer);
		float getOuterCutoff();
		float getInnerCutoff();
		void outputAngleData();
	};

}