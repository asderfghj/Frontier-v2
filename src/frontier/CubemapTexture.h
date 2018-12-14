#include <memory>
#include <string>
#include <vector>
#include <GL/glew.h>
#include "Resource.h"

namespace frontier
{
	class Resources;

	//!Resource class for a cubemap texture, mainly used for skyboxes.
	class CubemapTexture : public Resource
	{
	private:
		GLuint m_id;
		int m_textureLocation;
	public:
		//!Creates a new Cubemap and returns a pointer to it
		/*!
			\param _paths The paths where each of the cubemap textures are stored.
			\param _resources A pointer to the resources class so that the resource can be stored in memory and won't go out of scope.
			\param _textureLocation Where the texture will be stored when passed to the GPU.
		*/
		static std::shared_ptr<CubemapTexture> Create(std::vector<std::string> _paths, std::shared_ptr<Resources> _resources, int _textureLocation);

		//!Sets the texture, mainly used in the create function.
		/*!
			\param _newID The ID for the initialised texture
			\param _textureLocation Where the texture will be stored when passed to the GPU.
		*/
		void SetTexture(GLuint _newID, int _textureLocation);

		//!Returns the initialised texture ID.
		GLuint GetTexture();

		//!Returns the texture location.
		int GetTextureLocation();

		//!Binds the texture.
		void Bindtexture();

	};
}