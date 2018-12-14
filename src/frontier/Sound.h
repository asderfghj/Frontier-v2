#include <memory>
#include <string>
#include <AL/al.h>
#include "glm.hpp"
#include "Resource.h"

namespace frontier
{
	struct SoundImpl;
	class Resources;

	//!Container for a sound. Uses OpenAL.
	class Sound : public Resource
	{

	private:
		std::shared_ptr<SoundImpl> m_impl;
		ALuint m_sid;

	public:
		//!Creates a sound from an ogg file.
		/*!
			\param _path The filepath for the sound.
			\param _resources A pointer to the resources file.
		*/
		static std::shared_ptr<Sound> Create(std::string _path, std::shared_ptr<Resources> _resources);

		//!Loads the sound file from a filepath
		/*!
			\param _path The filepath for the sound.
		*/
		void Load(std::string _path);

		//!Plays the sound with a pitch shift
		/*!
			\param _vol The volume of the sound when playing.
			\param _varMin The minimum pitch of the sound.
			\param _varMax The maximum pitch of the sound.
			\param _soundPosition The position of the sound.
			\param _listenerPosition The position of the listener.
		*/
		void Play(float _vol, float _varMin, float _varMax, glm::vec3 _soundPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _listenerPosition = glm::vec3(0.0f, 0.0f, 0.0f));
		
		//!Plays the sound
		/*!
			\param _soundPosition The position of the sound.
			\param _listenerPosition The position of the listener.
			\param _looping Whether the sound should loop.
		*/
		void Play(glm::vec3 _soundPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _listenerPosition = glm::vec3(0.0f, 0.0f, 0.0f), bool _looping = false);
		
		//!Stops playing the sound if it is already playing.
		void Stop();
	};
}