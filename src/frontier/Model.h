#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <string>

#include "Shader.h"
#include "Component.h"
#include "Resource.h"
#include "Resources.h"

namespace frontier
{

	class Mesh;
	class Texture;
	class LightController;
	class DepthMap;

	struct Material
	{
		Material(std::string _name, glm::vec3 _amb, glm::vec3 _spec, glm::vec3 _diff, float _shininess)
		{
			m_name = _name;
			m_ambient = _amb;
			m_specular = _spec;
			m_diffuse = _diff;
			m_shininess = _shininess;
		}
		std::string m_name;
		glm::vec3 m_ambient;
		glm::vec3 m_specular;
		glm::vec3 m_diffuse;
		float m_shininess;
	};

	struct TexturePack
	{
		TexturePack(std::shared_ptr<Texture> _diffuse, std::shared_ptr<Texture> _specular)
		{
			if (_diffuse)
			{
				m_Diffuse = _diffuse;
				m_hasDiff = true;
			}

			if (_specular)
			{
				m_Specular = _specular;
				m_hasSpec = true;
			}
		}

		std::shared_ptr<Texture> m_Diffuse, m_Specular;
		bool m_hasDiff = false, m_hasSpec = false;

	};

	//!A group of meshes that make up a model.
	class Model : public Resource
	{
	friend class Mesh;
	private:
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		void LoadModel(std::string _path);
		std::vector<Material> m_modelMats;
	public:
		//!Creates a model from a filepath to be used in a MeshRenderer.
		/*!
			\param _path The filepath for the model.
			\param _resources The resources class located in core.
		*/
		static std::shared_ptr<Model> Create(const char *_path, std::weak_ptr<Resources> _resources);

		//!Draws the model.
		/*!
			\param _model The model matrix.
			\param _view The view matrix, taken from the camera.
			\param _proj The projection matrix, taken from the camera.
			\param _textures The textures for the model, currently supports specular and diffuse materials.
			\param _shader The shader for the model.
		*/
		void Draw(std::shared_ptr<Shader> _shader);
		
		void DrawDepthMap(glm::mat4 _model, glm::mat4 _lightspace, std::shared_ptr<Shader> _depthBufShader);

		void DrawPBR(std::shared_ptr<Shader> _shader);
	
	};
}

#endif // !MODEL_H_