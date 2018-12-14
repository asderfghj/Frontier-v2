#include "Light.h"
#include "glm.hpp"
#include <string>

namespace frontier
{
	class DepthMap;

	class DirectionalLight : public Light
	{

	private:
		glm::vec3 m_direction;
		glm::mat4 m_lightProjectionMatrix;
		std::shared_ptr<DepthMap> m_depthMap;
	public:
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction);
		void OnTick() override;
		void SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index = -1) override;
		void SetLightUniformPBR(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index = -1);
		glm::mat4 getLightSpaceMatrix();
		glm::vec3 getDirection();
		glm::vec3 getLightColor();
		void setLightColor(glm::vec3 _newColor);
		std::shared_ptr<DepthMap> getDepthMap();
	};

}