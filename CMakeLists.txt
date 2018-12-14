cmake_minimum_required(VERSION 2.6)
project (FRONTIERENGINE)

include_directories(
	src
	contrib/glm
	contrib/stb_image
	contrib/tinyobj
)


if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
    contrib/msvc-windows-x86/openal-soft/include
    contrib/msvc-windows-x86/ogg/include
    contrib/msvc-windows-x86/vorbis/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/ogg/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/vorbis/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(game
	src/game/main.cpp
	src/game/asteroidbehavior.cpp
	src/game/asteroidbehavior.h
	src/game/PlayerController.cpp
	src/game/PlayerController.h
	src/game/ProjectileBehavior.cpp
	src/game/ProjectileBehavior.h
	src/game/AsteroidSpawner.cpp
	src/game/AsteroidSpawner.h
	src/game/FPSCamera.cpp
	src/game/FPSCamera.h
	src/game/LightMove.cpp
	src/game/LightMove.h
)

add_library(frontier

	src/frontier/Camera.cpp
	src/frontier/Camera.h
	src/frontier/Core.cpp
	src/frontier/Core.h
	src/frontier/Entity.cpp
	src/frontier/Entity.h
	src/frontier/Component.cpp
	src/frontier/Component.h
	src/frontier/Input.cpp
	src/frontier/Input.h
	src/frontier/Environment.cpp
	src/frontier/Environment.h
	src/frontier/Timer.cpp
	src/frontier/Timer.h
	src/frontier/MeshRenderer.cpp
	src/frontier/MeshRenderer.h
	src/frontier/Resource.cpp
	src/frontier/Resource.h
	src/frontier/Resources.cpp
	src/frontier/Resources.h
	src/frontier/Shader.cpp
	src/frontier/Shader.h
	src/frontier/Texture.cpp
	src/frontier/Texture.h
	src/frontier/Transform.cpp
	src/frontier/Transform.h
	src/frontier/MyEngine.h
	src/frontier/Mesh.cpp
	src/frontier/Mesh.h
	src/frontier/Model.cpp
	src/frontier/Model.h
	src/frontier/Sound.cpp
	src/frontier/Sound.h
	src/frontier/AudioPlayer.cpp
	src/frontier/AudioPlayer.h
	src/frontier/Skybox.cpp
	src/frontier/Skybox.h
	src/frontier/CubemapTexture.cpp
	src/frontier/CubemapTexture.h
	src/frontier/Collider.cpp
	src/frontier/Collider.h
	src/frontier/UIImage.cpp
	src/frontier/UIImage.h
	src/frontier/UIButton.cpp
	src/frontier/UIButton.h
	src/frontier/Prefab.cpp
	src/frontier/Prefab.h
	src/frontier/Pooler.cpp
	src/frontier/Pooler.h
)

add_library(frontier_graphicsEX
	src/graphicsextension/Light.cpp
	src/graphicsextension/Light.h
	src/graphicsextension/PointLight.cpp
	src/graphicsextension/PointLight.h
	src/graphicsextension/DirectionalLight.cpp
	src/graphicsextension/DirectionalLight.h
	src/graphicsextension/SpotLight.cpp
	src/graphicsextension/SpotLight.h
	src/graphicsextension/LightController.cpp
	src/graphicsextension/LightController.h
	src/graphicsextension/RenderTexture.cpp
	src/graphicsextension/RenderTexture.h
	src/graphicsextension/RenderQuad.cpp
	src/graphicsextension/RenderQuad.h
	src/graphicsextension/DepthMap.cpp
	src/graphicsextension/DepthMap.h
	src/graphicsextension/FrontierGraphics.h
)

if(MSVC)
	target_link_libraries(frontier
		SDL2 glew32 opengl32 OpenAL32 ogg vorbis vorbisfile
	)
	
	target_link_libraries(frontier_graphicsEX
		SDL2 glew32 opengl32
	)
else()
	target_link_libraries(frontier
		SDL2 GLU GLEW GL AL ogg vorbis vorbisfile
	)
	
	target_link_libraries(frontier_graphicsEX
		SDL2 GLU GLEW GL
	)
	
endif()

target_link_libraries(game frontier)

target_link_libraries(game frontier_graphicsEX)

ADD_DEPENDENCIES(game frontier)

ADD_DEPENDENCIES(game frontier_graphicsEX)

if(MSVC)
  add_custom_command(TARGET frontier POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:frontier>"
  )

  add_custom_command(TARGET frontier POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:frontier>"
  )
  
    add_custom_command(TARGET frontier_graphicsEX POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:frontier_graphicsEX>"
  )

  add_custom_command(TARGET frontier_graphicsEX POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:frontier_graphicsEX>"
  )

  add_custom_command(TARGET frontier POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/bin/OpenAL32.dll"
      "$<TARGET_FILE_DIR:frontier>"
  )
endif()


