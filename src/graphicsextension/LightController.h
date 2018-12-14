#include <vector>
#include <memory>
#include <string>
#include "glm.hpp"

namespace frontier
{
	class Core;
	class Entity;
	class Shader;
	class DepthMap;
	class DirectionalLight;

	class LightController
	{
	private:
		std::weak_ptr<Core> m_corePtr;
		std::vector<std::weak_ptr<Entity>> m_pointLights;
		std::weak_ptr<Entity> m_directionalLight;
		std::vector<std::weak_ptr<Entity>> m_spotLights;

	public:
		LightController(std::weak_ptr<Core> _corePtr);
		void AddPointLight(std::weak_ptr<Entity> _newPointLight);
		void SetDirectionalLight(std::weak_ptr<Entity> _directionalLight);
		void AddSpotLight(std::weak_ptr<Entity> _newSpotLight);
		void SetLightUniformValues(std::shared_ptr<Shader> _shader);
		glm::mat4 GetLightSpacematrix();
		glm::vec3 GetDirectionalLightPosition();
		std::shared_ptr<DepthMap> GetDirectionalLightDepthMap();
		void SetLightUniformValuesPBR(std::shared_ptr<Shader> _shader);
		bool HasDirectionalLight();
		std::shared_ptr<DirectionalLight> LightController::GetDirectionalLight();
	};

}