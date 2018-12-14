#ifndef CORE_H_
#define CORE_H_

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "glm.hpp"
#include <string>
#include <AL/al.h>
#include <AL/alc.h>

namespace frontier
{

	class Environment;
	class Entity;
	class Input;
	class Resources;
	class Camera;
	class Shader;
	class Prefab;
	class Pooler;
	class RenderTexture;
	class RenderQuad;
	class LightController;
	class DepthMap;

	//!The main core of the engine. This is where all entities, prefabs and resources get created. 
	class Core : public std::enable_shared_from_this<Core>
	{
	public:
		enum ShaderMode
		{
			BLINN_PHONG,
			PBR
		};
	private:
		//Entity related
		std::vector<std::shared_ptr<Entity>> m_entities;
		std::vector<std::shared_ptr<Entity>> m_uiElements;
		std::vector<std::shared_ptr<Prefab>> m_prefabs;
		std::vector<std::shared_ptr<Pooler>> m_poolers;
		std::vector<std::shared_ptr<Entity>> m_entitiesToActivate;
		std::vector<std::shared_ptr<DepthMap>> m_depthMapsToRender;

		//Other important classes
		std::shared_ptr<Environment> m_environment;
		std::shared_ptr<Input> m_input;
		std::shared_ptr<Resources> m_resources;
		std::weak_ptr<Core> m_self;
		std::shared_ptr<Camera> m_mainCamera;
		std::shared_ptr<RenderTexture> m_screenRT;
		std::shared_ptr<RenderQuad> m_screenRQ;
		std::shared_ptr<DepthMap> m_shadowDepthMap;
		std::shared_ptr <LightController> m_lightController;

		//Default shaders
		std::shared_ptr<Shader> m_hitboxShader;
		std::shared_ptr<Shader> m_skyboxShader;
		std::shared_ptr<Shader> m_untexturedUIImageShader;
		std::shared_ptr<Shader> m_texturedUIImageShader;
		std::shared_ptr<Shader> m_defaultRenderQuadShader;
		std::shared_ptr<Shader> m_depthMapShader;
		std::shared_ptr<Shader> m_blinnPhongShader;
		std::shared_ptr<Shader> m_PBRShader;

		//Important external classes
		SDL_Window *m_window;
		SDL_Event m_event;
		ALCdevice* m_device;
		ALCcontext* m_context;
		


		//Other information
		int m_windowWidth, m_windowHeight;
		ShaderMode m_shaderMode;
		bool m_running;
		bool m_updateInfo;

		void GameLoop();

	public:
		//!Destructor for the core, removes all entities from stored vector list.
		~Core();

		//!Initialisation for the core, sets up OpenGL, SDL, OpenAL and all other classes needed by the core.
		/*!
			\param _self A pointer to the core, used to assign to entities.
			\param _width The window width (set to 800 by default).
			\param _height The window height (set to 600 by default).
		*/
		void Init(std::weak_ptr<Core> _self, int _width = 800, int _height = 600);

		//!Starts the game, this starts the game loop and makes everything run. Do not call this until everything has been set up.
		void Start();

		//!Stops the game, closes down any classes that need to be de-initialised.
		void Stop();

		//!Adds an entity and returns a pointer to it
		/*!
			\param _position The initial position of the entity (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _rotation The initial rotation of the entity (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _scale The initial scale of the entity (set to glm::vec3(1.0f, 1.0f, 1.0f) by default).
		*/
		std::shared_ptr<Entity> AddEntity(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));

		//!Adds an entity using a prefab and returns a pointer to it
		/*!
			\param _prefab The prefab which the entity will be copied from.
			\param _position The initial position of the entity (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _rotation The initial rotation of the entity (set to glm::vec3(0.0f, 0.0f, 0.0f) by default).
			\param _scale The initial scale of the entity (set to glm::vec3(1.0f, 1.0f, 1.0f) by default).
		*/
		std::shared_ptr<Entity> AddEntity(std::shared_ptr<Prefab> _prefab, glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));

		//!Adds a UI element entity, a UI element entity has it's on tick function prioritised over non-ui entities.
		/*!
			\param _position The initial position of the entity in screen space (set to glm::vec2(0.0f, 0.0f) by default).
			\param _rotation The initial rotation of the entity (set to 0.0f by default).
			\param _scale The initial scale of the entity (set to glm::vec3(1.0f, 1.0f, 1.0f) by default).
		*/
		std::shared_ptr<Entity> AddUIElement(glm::vec2 _position = glm::vec2(0.0f, 0.0f), float _rotation = 0.0f, glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));

		//!Adds a prefab and returns a pointer to it.
		std::shared_ptr<Prefab> AddPrefab();

		//!Adds a pooler for use with a lot of instances of entities.
		/*!
			\param _id string identifier for the pooler.
			\param _prefab The prefab that entities will be created from.
			\param _initalPoolSize The intial number of entities to be created.
		*/
		std::shared_ptr<Pooler> AddPooler(std::string _id, std::shared_ptr<Prefab> _prefab, int _initialPoolSize);

		//!Returns a pooler with the given ID.
		/*!
			\param _poolID the string identifier of the pool, must match the string created during initialisation of the pool (see addPooler).
		*/
		std::shared_ptr<Pooler> GetPooler(std::string _poolID);

		//!Returns the instance of the environment class.
		std::shared_ptr<Environment> GetEnvironment();

		//!Returns the instance of the input class.
		std::shared_ptr<Input> GetInput();

		//!Returns the instance of the resources class.
		std::shared_ptr<Resources> GetResources();

		std::shared_ptr<LightController> GetLightController();

		void RequestDepthMapRender(std::shared_ptr<DepthMap> _dm);

		//!Sets the self pointer to be used in entity intialisation.
		/*!
			\param _self A pointer to the core, used to assign to entities.
		*/
		void SetSelf(std::weak_ptr<Core> _selfPtr);

		//!Returns the width of the screen.
		int GetWidth();

		//!Returns the height of the screen.
		int GetHeight();

		//!Returns a pointer to the current main camera
		std::shared_ptr<Camera> GetMainCamera();

		//!Sets a new main camera and unsets the previous one.
		/*!
			\param _mainCameraToSet A pointer to the new main camera.
		*/
		void SetMainCamera(std::shared_ptr<Camera> _mainCameraToSet);

		//!Sets all entities in pools to inactive.
		void DeactivateAllInstancesInPools();

		//default shader getters
		//!Returns a pointer to the default hitbox shader.
		std::shared_ptr<Shader> getHitboxShader();

		//!Returns a pointer to the default skybox shader.
		std::shared_ptr<Shader> getSkyboxShader();

		//!Returns a pointer to the default untextured UI shader.
		std::shared_ptr<Shader> getUntexturedUiImageShader();

		//!Returns a pointer to the default textured UI shader.
		std::shared_ptr<Shader> getTexturedUiImageShader();

		std::shared_ptr<Shader> getBlinnPhongShader();

		std::shared_ptr<Shader> getPBRShader();

		std::shared_ptr<Shader> getDefaultRenderQuadShader();

		std::shared_ptr<DepthMap> getShadowMap();

		ShaderMode getShaderMode();

		void setShaderMode(ShaderMode _newMode);

		void requestInfoUpdate();

		//!Adds an entity to activation list so that it can be activated next frame.
		void AddToEntitiesToActivate(std::shared_ptr<Entity> _entityToActivate);

		//!returns a vector with all entities with a specified component.
		template <typename T>
		std::vector<std::weak_ptr<Entity>> getEntitiesWithComponent()
		{
			std::vector<std::weak_ptr<Entity>> returnEntities;
			for (size_t i = 0; i < m_entities.size(); i++)
			{
				if (m_entities[i]->hasComponent<T>())
				{
					returnEntities.push_back(m_entities[i]);
				}
			}

			return returnEntities;
		}


	};

}

#endif // !CORE_H_