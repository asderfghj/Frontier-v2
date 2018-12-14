#include <iostream>
#include <memory>
#include "frontier/MyEngine.h"
#include "graphicsextension/FrontierGraphics.h"
#include <exception>
#include "ProjectileBehavior.h"
#include "PlayerController.h"
#include "AsteroidBehavior.h"
#include "AsteroidSpawner.h"
#include "LightMove.h"
#include "FPSCamera.h"


void safe_main();

int main()
{
	try
	{
		safe_main();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Something went wrong" << std::endl;
	}

	std::cin.get();
	
	return 0;
}

void safe_main()
{
	std::shared_ptr<frontier::Core> _core = std::make_shared<frontier::Core>();

	_core->Init(_core, 1000, 800);


	//RESOURCES
	//Material Display Models
	std::shared_ptr<frontier::Model> SphereModel = frontier::Model::Create("../resources/models/sphere/sphere.obj", _core->GetResources());
	std::shared_ptr<frontier::Model> PlaneModel = frontier::Model::Create("../resources/models/plane/plane.obj", _core->GetResources());

	//object models
	std::shared_ptr<frontier::Model> HatchetModel = frontier::Model::Create("../resources/models/Hatchet/Hatchet.obj", _core->GetResources());
	std::shared_ptr<frontier::Model> CanModel = frontier::Model::Create("../resources/models/coke/coke.obj", _core->GetResources());


	//floor textures
	std::shared_ptr<frontier::Texture> floorAlbedo = frontier::Texture::Create("../resources/textures/woodPlanksPBR/albedo.jpg", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> floorNormal = frontier::Texture::Create("../resources/textures/woodPlanksPBR/normal.jpg", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> floorRoughness = frontier::Texture::Create("../resources/textures/woodPlanksPBR/roughness.jpg", _core->GetResources(), 4);

	//object textures
	//hatchet textures
	std::shared_ptr<frontier::Texture> hatchetAlbedo = frontier::Texture::Create("../resources/textures/HatchetPBR/albedo.png", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> hatchetNormal = frontier::Texture::Create("../resources/textures/HatchetPBR/normal.png", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> hatchetMetallic = frontier::Texture::Create("../resources/textures/HatchetPBR/metallic.png", _core->GetResources(), 3);
	std::shared_ptr<frontier::Texture> hatchetRoughness = frontier::Texture::Create("../resources/textures/HatchetPBR/Roughness.png", _core->GetResources(), 4);
	std::shared_ptr<frontier::Texture> hatchetAO = frontier::Texture::Create("../resources/textures/HatchetPBR/ao.png", _core->GetResources(), 5);
	//coke can textures
	std::shared_ptr<frontier::Texture> cokeAlbedo = frontier::Texture::Create("../resources/textures/cokePBR/albedo.png", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> cokeNormal = frontier::Texture::Create("../resources/textures/cokePBR/normal.png", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> cokeMetallic = frontier::Texture::Create("../resources/textures/cokePBR/metallic.png", _core->GetResources(), 3);
	std::shared_ptr<frontier::Texture> cokeRoughness = frontier::Texture::Create("../resources/textures/cokePBR/Roughness.png", _core->GetResources(), 4);
	std::shared_ptr<frontier::Texture> cokeAO = frontier::Texture::Create("../resources/textures/cokePBR/ao.png", _core->GetResources(), 5);

	//material textures
	//dirt
	std::shared_ptr<frontier::Texture> dirtAlbedo = frontier::Texture::Create("../resources/textures/dirtPBR/albedo.jpg", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> dirtNormal = frontier::Texture::Create("../resources/textures/dirtPBR/normal.jpg", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> dirtRoughness = frontier::Texture::Create("../resources/textures/dirtPBR/Roughness.jpg", _core->GetResources(), 4);
	std::shared_ptr<frontier::Texture> dirtAO = frontier::Texture::Create("../resources/textures/dirtPBR/ao.jpg", _core->GetResources(), 5);

	//ground
	std::shared_ptr<frontier::Texture> groundAlbedo = frontier::Texture::Create("../resources/textures/groundPBR/albedo.jpg", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> groundNormal = frontier::Texture::Create("../resources/textures/groundPBR/normal.jpg", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> groundRoughness = frontier::Texture::Create("../resources/textures/groundPBR/Roughness.jpg", _core->GetResources(), 4);
	std::shared_ptr<frontier::Texture> groundAO = frontier::Texture::Create("../resources/textures/groundPBR/ao.jpg", _core->GetResources(), 5);

	//paving
	std::shared_ptr<frontier::Texture> pavingAlbedo = frontier::Texture::Create("../resources/textures/pavingPBR/albedo.jpg", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> pavingNormal = frontier::Texture::Create("../resources/textures/pavingPBR/normal.jpg", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> pavingRoughness = frontier::Texture::Create("../resources/textures/pavingPBR/Roughness.jpg", _core->GetResources(), 4);

	//paving stones
	std::shared_ptr<frontier::Texture> pavingStonesAlbedo = frontier::Texture::Create("../resources/textures/pavingStonesPBR/albedo.jpg", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> pavingStonesNormal = frontier::Texture::Create("../resources/textures/pavingStonesPBR/normal.jpg", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> pavingStonesRoughness = frontier::Texture::Create("../resources/textures/pavingStonesPBR/Roughness.jpg", _core->GetResources(), 4);
	std::shared_ptr<frontier::Texture> pavingStonesAO = frontier::Texture::Create("../resources/textures/pavingStonesPBR/ao.jpg", _core->GetResources(), 5);

	//rocks
	std::shared_ptr<frontier::Texture> rocksAlbedo = frontier::Texture::Create("../resources/textures/rocksPBR/albedo.jpg", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> rocksNormal = frontier::Texture::Create("../resources/textures/rocksPBR/normal.jpg", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> rocksRoughness = frontier::Texture::Create("../resources/textures/rocksPBR/Roughness.jpg", _core->GetResources(), 4);
	std::shared_ptr<frontier::Texture> rocksAO = frontier::Texture::Create("../resources/textures/rocksPBR/ao.jpg", _core->GetResources(), 5);

	//rusty metal
	std::shared_ptr<frontier::Texture> rustyMetalAlbedo = frontier::Texture::Create("../resources/textures/rustyMetalPBR/albedo.jpg", _core->GetResources(), 1);
	std::shared_ptr<frontier::Texture> rustyMetalNormal = frontier::Texture::Create("../resources/textures/rustyMetalPBR/normal.jpg", _core->GetResources(), 2);
	std::shared_ptr<frontier::Texture> rustyMetalMetallic = frontier::Texture::Create("../resources/textures/rustyMetalPBR/metallic.jpg", _core->GetResources(), 3);
	std::shared_ptr<frontier::Texture> rustyMetalRoughness = frontier::Texture::Create("../resources/textures/rustyMetalPBR/Roughness.jpg", _core->GetResources(), 4);

	//ENTITIES
	//floor
	std::shared_ptr<frontier::Entity> _PBRPlane = _core->AddEntity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(50.0f, 1.0f, 50.0f));
	//floor mesh
	_PBRPlane->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(PlaneModel);
	_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(floorAlbedo, frontier::MeshRenderer::ALBEDO);
	_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(floorNormal, frontier::MeshRenderer::NORMAL);
	_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(floorRoughness, frontier::MeshRenderer::ROUGHNESS);

	//spheres
	//dirt sphere
	std::shared_ptr<frontier::Entity> _sphere1 = _core->AddEntity(glm::vec3(-20.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f));
	_sphere1->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(SphereModel);
	_sphere1->getComponent<frontier::MeshRenderer>()->AttachTexture(dirtAlbedo, frontier::MeshRenderer::ALBEDO);
	_sphere1->getComponent<frontier::MeshRenderer>()->AttachTexture(dirtNormal, frontier::MeshRenderer::NORMAL);
	_sphere1->getComponent<frontier::MeshRenderer>()->AttachTexture(dirtRoughness, frontier::MeshRenderer::ROUGHNESS);
	_sphere1->getComponent<frontier::MeshRenderer>()->AttachTexture(dirtAO, frontier::MeshRenderer::AO);

	//ground sphere
	std::shared_ptr<frontier::Entity> _sphere2 = _core->AddEntity(glm::vec3(-10.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f));
	_sphere2->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(SphereModel);
	_sphere2->getComponent<frontier::MeshRenderer>()->AttachTexture(groundAlbedo, frontier::MeshRenderer::ALBEDO);
	_sphere2->getComponent<frontier::MeshRenderer>()->AttachTexture(groundNormal, frontier::MeshRenderer::NORMAL);
	_sphere2->getComponent<frontier::MeshRenderer>()->AttachTexture(groundRoughness, frontier::MeshRenderer::ROUGHNESS);
	_sphere2->getComponent<frontier::MeshRenderer>()->AttachTexture(groundAO, frontier::MeshRenderer::AO);

	//paving sphere
	std::shared_ptr<frontier::Entity> _sphere3 = _core->AddEntity(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f));
	_sphere3->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(SphereModel);
	_sphere3->getComponent<frontier::MeshRenderer>()->AttachTexture(pavingAlbedo, frontier::MeshRenderer::ALBEDO);
	_sphere3->getComponent<frontier::MeshRenderer>()->AttachTexture(pavingNormal, frontier::MeshRenderer::NORMAL);
	_sphere3->getComponent<frontier::MeshRenderer>()->AttachTexture(pavingRoughness, frontier::MeshRenderer::ROUGHNESS);

	//paving stones sphere
	std::shared_ptr<frontier::Entity> _sphere4 = _core->AddEntity(glm::vec3(10.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f));
	_sphere4->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(SphereModel);
	_sphere4->getComponent<frontier::MeshRenderer>()->AttachTexture(pavingStonesAlbedo, frontier::MeshRenderer::ALBEDO);
	_sphere4->getComponent<frontier::MeshRenderer>()->AttachTexture(pavingStonesNormal, frontier::MeshRenderer::NORMAL);
	_sphere4->getComponent<frontier::MeshRenderer>()->AttachTexture(pavingStonesRoughness, frontier::MeshRenderer::ROUGHNESS);
	_sphere4->getComponent<frontier::MeshRenderer>()->AttachTexture(pavingStonesAO, frontier::MeshRenderer::AO);

	//rocks sphere
	std::shared_ptr<frontier::Entity> _sphere5 = _core->AddEntity(glm::vec3(20.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f));
	_sphere5->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(SphereModel);
	_sphere5->getComponent<frontier::MeshRenderer>()->AttachTexture(rocksAlbedo, frontier::MeshRenderer::ALBEDO);
	_sphere5->getComponent<frontier::MeshRenderer>()->AttachTexture(rocksNormal, frontier::MeshRenderer::NORMAL);
	_sphere5->getComponent<frontier::MeshRenderer>()->AttachTexture(rocksRoughness, frontier::MeshRenderer::ROUGHNESS);
	_sphere5->getComponent<frontier::MeshRenderer>()->AttachTexture(rocksAO, frontier::MeshRenderer::AO);

	//rusty metal sphere
	std::shared_ptr<frontier::Entity> _sphere6 = _core->AddEntity(glm::vec3(30.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f));
	_sphere6->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(SphereModel);
	_sphere6->getComponent<frontier::MeshRenderer>()->AttachTexture(rustyMetalAlbedo, frontier::MeshRenderer::ALBEDO);
	_sphere6->getComponent<frontier::MeshRenderer>()->AttachTexture(rustyMetalNormal, frontier::MeshRenderer::NORMAL);
	_sphere6->getComponent<frontier::MeshRenderer>()->AttachTexture(rustyMetalRoughness, frontier::MeshRenderer::ROUGHNESS);
	_sphere6->getComponent<frontier::MeshRenderer>()->AttachTexture(rustyMetalMetallic, frontier::MeshRenderer::METALLIC);

	//hatchet
	std::shared_ptr<frontier::Entity> _PBRHatchet = _core->AddEntity(glm::vec3(40.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f));
	//hatchet mesh
	_PBRHatchet->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(HatchetModel);
	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetAlbedo, frontier::MeshRenderer::ALBEDO);
	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetNormal, frontier::MeshRenderer::NORMAL);
	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetMetallic, frontier::MeshRenderer::METALLIC);
	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetRoughness, frontier::MeshRenderer::ROUGHNESS);
	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetAO, frontier::MeshRenderer::AO);

	//coke can
	std::shared_ptr<frontier::Entity> _PBRCokeCan = _core->AddEntity(glm::vec3(-30.0f, 15.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.3f));
	//coke mesh
	_PBRCokeCan->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(CanModel);
	_PBRCokeCan->getComponent<frontier::MeshRenderer>()->AttachTexture(cokeAlbedo, frontier::MeshRenderer::ALBEDO);
	_PBRCokeCan->getComponent<frontier::MeshRenderer>()->AttachTexture(cokeNormal, frontier::MeshRenderer::NORMAL);
	_PBRCokeCan->getComponent<frontier::MeshRenderer>()->AttachTexture(cokeMetallic, frontier::MeshRenderer::METALLIC);
	_PBRCokeCan->getComponent<frontier::MeshRenderer>()->AttachTexture(cokeRoughness, frontier::MeshRenderer::ROUGHNESS);
	_PBRCokeCan->getComponent<frontier::MeshRenderer>()->AttachTexture(cokeAO, frontier::MeshRenderer::AO);

	//LIGHTING
	//directional light
	std::shared_ptr<frontier::Entity> _directionalLight = _core->AddEntity(glm::vec3(10.0f, 0.0f, 10.0f));
	_directionalLight->AddComponent<frontier::DirectionalLight, glm::vec3, glm::vec3, glm::vec3, glm::vec3>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(5.0f, -5.0f, 5.0f));

	//point lights
	std::shared_ptr<frontier::Entity> _pointLight1 = _core->AddEntity(glm::vec3(-20.0f, 15.0f, 10.0f));
	_pointLight1->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0, 0.045, 0.0075);
	std::shared_ptr<frontier::Entity> _pointLight2 = _core->AddEntity(glm::vec3(20.0f, 15.0f, 10.0f));
	_pointLight2->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0, 0.045, 0.0075);
	/*std::shared_ptr<frontier::Entity> _pointLight3 = _core->AddEntity(glm::vec3(-35.0f, 15.0f, 10.0f));
	_pointLight3->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0, 0.045, 0.0075);*/



	//CAMERA
	_core->GetMainCamera()->GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(0.0f, 15.0f, -15.0f));
	_core->GetMainCamera()->GetEntity()->AddComponent<FPSCamera>();

	_core->Start();

}