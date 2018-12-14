#include "MeshRenderer.h"
#include "Shader.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"
#include "Texture.h"
#include "Model.h"
#include "game/FPSCamera.h"
#include "graphicsextension/LightController.h"


namespace frontier
{
	void MeshRenderer::OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Model> meshData)
	{
		Component::OnInit(_parent);
		m_copyable = true;
		m_meshData = meshData;
		m_hasAO = false;
		m_hasMetallic = false;
		m_blinnPhongShader = _parent.lock()->GetCore()->getBlinnPhongShader();
		m_PBRShader = _parent.lock()->GetCore()->getPBRShader();
	}

	void MeshRenderer::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<MeshRenderer> _original)
	{
		Component::OnInit(_parent);
		m_copyable = true;
		m_meshData = _original.lock()->GetMeshData();
		m_blinnPhongShader = _original.lock()->GetShader();
		m_diffuse = _original.lock()->GetTexture();

	}

	void MeshRenderer::OnTick()
	{
		Component::OnTick();

	}

	void MeshRenderer::Draw()
	{
		m_blinnPhongShader->SetUniform("model", GetEntity()->getComponent<Transform>()->GetModelMatrix());
		m_blinnPhongShader->SetUniform("view", GetCore()->GetMainCamera()->GetViewMatrix());
		m_blinnPhongShader->SetUniform("projection", GetCore()->GetMainCamera()->GetProjectionMatrix());
		if (GetCore()->GetLightController()->HasDirectionalLight())
		{
			m_blinnPhongShader->SetUniform("lightSpaceMatrix", GetCore()->GetLightController()->GetLightSpacematrix());
		}
		m_blinnPhongShader->SetUniform("viewPos", GetCore()->GetMainCamera()->GetEntity()->getComponent<Transform>()->GetPosition());
		
		if (m_hasNormal)
		{
			m_blinnPhongShader->SetUniform("material.normalMap", m_normal);
			m_normal->BindTexture();
		}
		m_blinnPhongShader->SetUniform("material.hasNormalmap", m_hasNormal);

		m_blinnPhongShader->SetUniform("material.diffuseMat", m_albedo);
		m_albedo->BindTexture();

		m_blinnPhongShader->SetUniform("material.shininess", 64.0f);

		GetCore()->GetLightController()->SetLightUniformValues(m_blinnPhongShader);

		m_meshData->Draw(m_blinnPhongShader);
	}

	void MeshRenderer::DrawDepthMap(std::shared_ptr<Shader> _depthBufShader)
	{
		m_meshData->DrawDepthMap(GetEntity()->getComponent<Transform>()->GetModelMatrix(), GetCore()->GetLightController()->GetLightSpacematrix(), _depthBufShader);
	}

	void MeshRenderer::DrawPBR()
	{
		m_PBRShader->SetUniform("model", GetEntity()->getComponent<Transform>()->GetModelMatrix());
		m_PBRShader->SetUniform("view", GetCore()->GetMainCamera()->GetViewMatrix());
		m_PBRShader->SetUniform("projection", GetCore()->GetMainCamera()->GetProjectionMatrix());
		m_PBRShader->SetUniform("camPos", GetCore()->GetMainCamera()->GetEntity()->getComponent<Transform>()->GetPosition());

		m_PBRShader->SetUniform("albedoMap", m_albedo);
		m_albedo->BindTexture();
		m_PBRShader->SetUniform("normalMap", m_normal);
		m_normal->BindTexture();
		if (m_hasMetallic)
		{
			m_PBRShader->SetUniform("metallicMap", m_metallic);
			m_metallic->BindTexture();
		}
		m_PBRShader->SetUniform("hasMetallic", m_hasMetallic);
		m_PBRShader->SetUniform("roughnessMap", m_roughness);
		m_roughness->BindTexture();
		if (m_hasAO)
		{
			m_PBRShader->SetUniform("aoMap", m_ao);
			m_ao->BindTexture();
		}
		m_PBRShader->SetUniform("hasAO", m_hasAO);

		GetCore()->GetLightController()->SetLightUniformValuesPBR(m_PBRShader);

		m_meshData->DrawPBR(m_PBRShader);
	}

	void MeshRenderer::AttachShaderProgram(std::shared_ptr<Shader> _newShaderProgram)
	{
		m_blinnPhongShader = _newShaderProgram;
	}

	void MeshRenderer::AttachTexture(std::shared_ptr<Texture> _newTexture, Texturetype _typ)
	{
		if (_typ == DIFFUSE)
		{
			m_diffuse = _newTexture;
		}
		else if (_typ == SPECULAR)
		{
			m_specular = _newTexture;
		}
		else if (_typ == ALBEDO)
		{
			m_albedo = _newTexture;
		}
		else if (_typ == NORMAL)
		{
			m_normal = _newTexture;
			if (m_normal)
			{
				m_hasNormal = true;
			}
			else
			{
				m_hasNormal = false;
			}
		}
		else if (_typ == METALLIC)
		{
			m_metallic = _newTexture;
			if (m_metallic)
			{
				m_hasMetallic = true;
			}
			else
			{
				m_metallic = false;
			}
		}
		else if (_typ == ROUGHNESS)
		{
			m_roughness = _newTexture;
		}
		else if (_typ == AO)
		{
			m_ao = _newTexture;
			if (m_ao)
			{
				m_hasAO = true;
			}
			else
			{
				m_hasAO = false;
			}
		}

	}

	std::shared_ptr<Model> MeshRenderer::GetMeshData()
	{
		return m_meshData;
	}

	std::shared_ptr<Texture> MeshRenderer::GetTexture()
	{
		return m_diffuse;
	}

	std::shared_ptr<Shader> MeshRenderer::GetShader()
	{
		return m_blinnPhongShader;
	}

}