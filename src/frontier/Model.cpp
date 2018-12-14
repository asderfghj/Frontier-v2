#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Model.h"
#include "Mesh.h"

namespace frontier
{
	void Model::LoadModel(std::string _path)
	{
		tinyobj::attrib_t inAttrib;
		std::vector<tinyobj::shape_t> inShapes;
		std::vector<tinyobj::material_t> inMats;
		std::string errorMsg;
		int basePathEndIndex;
		bool hasTexCoords = true;

		for (size_t i = 0; i < _path.size(); i++)
		{
			if (_path[i] == '/')
			{
				basePathEndIndex = i;
			}
		}

		tinyobj::LoadObj(&inAttrib, &inShapes, &inMats, &errorMsg, _path.c_str(), _path.substr(0, basePathEndIndex + 1).c_str());



		if (!errorMsg.empty())
		{
			std::cout << errorMsg << std::endl;
		}

		for (int i = 0; i < inMats.size(); i++)
		{
			Material newMaterial(inMats[i].name, glm::vec3(inMats[i].ambient[0], inMats[i].ambient[1], inMats[i].ambient[2]), glm::vec3(inMats[i].specular[0], inMats[i].specular[1], inMats[i].specular[2]), glm::vec3(inMats[i].diffuse[0], inMats[i].diffuse[1], inMats[i].diffuse[2]), inMats[i].shininess);
			m_modelMats.push_back(newMaterial);
		}

		std::vector<GLfloat> vertices;
		std::vector<GLfloat> normals;
		std::vector<GLfloat> texCoords;

		for (unsigned int i = 0; i < inShapes.size(); i++)
		{
			for (unsigned int j = 0; j < inShapes[i].mesh.indices.size(); j++)
			{
				int indicesIndex = inShapes[i].mesh.indices[j].vertex_index * 3;
				vertices.push_back(inAttrib.vertices[indicesIndex]);
				vertices.push_back(inAttrib.vertices[indicesIndex + 1]);
				vertices.push_back(inAttrib.vertices[indicesIndex + 2]);

				int normalIndex = inShapes[i].mesh.indices[j].normal_index * 3;
				normals.push_back(inAttrib.normals[normalIndex]);
				normals.push_back(inAttrib.normals[normalIndex + 1]);
				normals.push_back(inAttrib.normals[normalIndex + 2]);

				if (hasTexCoords)
				{
					int texCoordsIndex = inShapes[i].mesh.indices[j].texcoord_index * 2;
					if (texCoordsIndex > -1)
					{
						texCoords.push_back(inAttrib.texcoords[texCoordsIndex]);
						texCoords.push_back(inAttrib.texcoords[texCoordsIndex + 1]);
					}
					else
					{
						hasTexCoords = false;
					}
				}
			}

			std::shared_ptr<Mesh> mesh;

			if (hasTexCoords)
			{
				mesh = std::make_shared<Mesh>(vertices, normals, texCoords);
			}
			else
			{
				mesh = std::make_shared<Mesh>(vertices, normals);
			}

			m_meshes.push_back(mesh);

		}

		std::cout << "Model Processed" << std::endl;

	}

	std::shared_ptr<Model> Model::Create(const char *_path, std::weak_ptr<Resources> _resources)
	{
		std::shared_ptr<Model> rtn = std::make_shared<Model>();
		rtn->LoadModel(_path);
		_resources.lock()->AddCreatedResource(rtn);
		return rtn;
	}

	void Model::Draw(std::shared_ptr<Shader> _shader)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->Draw(_shader);
		}
	}

	void Model::DrawDepthMap(glm::mat4 _model, glm::mat4 _lightspace, std::shared_ptr<Shader> _depthBufShader)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->DrawDepthMap(_model, _lightspace, _depthBufShader);
		}
	}

	void Model::DrawPBR(std::shared_ptr<Shader> _shader)
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i]->DrawPBR(_shader);
		}
	}


}
