#ifndef _AUDIOPLAYER_H_
#define _AUDIOPLAYER_H_

#include "glm.hpp"
#include "Component.h" 

namespace frontier
{

	class Sound;
	class Entity;

	//!This class holds a sound resource which can then be attached to a entity can can be played in various different ways.
	class AudioPlayer : public Component
	{
	private:
		//! the attached sound
		std::shared_ptr<Sound> m_attachedSound;

	public:
		//!Initialises the audio player component, this will be called by AddComponent in the Entity class, adds a sound to the audio player.
		/*!
			\param _parent The entity that this component is attached to.
			\param _sound The sound that will be played by this audio player component.
		*/
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Sound> _sound);

		//!Plays the currently attached sound.
		/*!
			\param _looping Whether the audio source will play continuously on a loop (Set to false by default).
		*/
		void Play(bool _looping = false);

		//!Plays the currently attached sound.
		/*!
			\param _soundPosition Where the sound will play from.
			\param _listenerPosition Where the sound will be heard from.
			\param _looping Whether the audio source will play continuously on a loop.
		*/
		void Play(glm::vec3 _soundPosition, glm::vec3 _listenerPosition, bool _looping = false);

		//!Plays the currently attached sound with the pitch shifted randomly between the two provided floats.
		/*!
			\param _vol The volume of the audio.
			\param _varMin The minimum value on the variance.
			\param _varMax The maximum value on the variance.
		*/
		void PlayWithVariance(float _vol, float _varMin, float _varMax);

		//!Attaches a new sound to the audio player.
		/*!
			\param _sound The new sound to be attached to the audio player.
		*/
		void AttachSound(std::shared_ptr<Sound> _sound);

		//! Stops playing the sound.
		void Stop();

	};

}

#endif