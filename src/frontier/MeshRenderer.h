#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include <GL/glew.h>
#include <memory>
#include <vector>
#include "Component.h"
#include "glm.hpp"

namespace frontier
{

	class Texture;
	class Shader;
	class Model;

	//!Container for a model.
	class MeshRenderer : public Component
	{
	private:
		std::shared_ptr<Model> m_meshData;
		std::shared_ptr<Texture> m_diffuse;
		std::shared_ptr<Texture> m_specular;
		std::shared_ptr<Texture> m_albedo;
		std::shared_ptr<Texture> m_normal;
		bool m_hasNormal;
		std::shared_ptr<Texture> m_metallic;
		bool m_hasMetallic;
		std::shared_ptr<Texture> m_roughness;
		std::shared_ptr<Texture> m_ao;
		bool m_hasAO;
		std::shared_ptr<Shader> m_blinnPhongShader;
		std::shared_ptr<Shader> m_PBRShader;


	public:
		enum Texturetype
		{
			DIFFUSE,
			SPECULAR,
			ALBEDO,
			NORMAL,
			METALLIC,
			ROUGHNESS,
			AO
		};

		//!Initialises the MeshRenderer with a model
		/*!
			\param _parent The entity this component will be attached to.
			\param _meshData The model that will be rendered.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Model> _meshData);

		//!Initialises the MeshRenderer with a MeshRenderer, usually from a prefab.
		/*!
			\param _parent The entity this component will be attached to.
			\param _original The orginal mesh renderer that will be copied.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<MeshRenderer> _original);

		//!Draws the mesh.
		void OnTick() override;

		void Draw();

		void DrawDepthMap(std::shared_ptr<Shader> _depthBufShader);

		void DrawPBR();

		//!Attaches a shader program to the mesh renderer
		/*!
			\param _newShaderProgram Shader program to attach.
		*/
		void AttachShaderProgram(std::shared_ptr<Shader> _newShaderProgram);

		//!Attaches a texture to the mesh renderer
		/*!
			\param _newTexture Texture to attach.
		*/
		void AttachTexture(std::shared_ptr<Texture> _newTexture, Texturetype _typ);

		//!Returns the current model.
		std::shared_ptr<Model> GetMeshData();

		//!Returns the current texture.
		std::shared_ptr<Texture> GetTexture();

		//!Returns the current shader.
		std::shared_ptr<Shader> GetShader();
	};
}

#endif // !MESHRENDERER_H_