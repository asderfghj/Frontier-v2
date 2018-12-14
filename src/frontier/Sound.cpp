#include "Sound.h"
#include "Resources.h"

#include <vorbis/vorbisfile.h>

#include <iostream>
#include <vector>

namespace frontier
{
	struct SoundImpl
	{
		ALuint id;

		~SoundImpl()
		{
			alDeleteBuffers(1, &id);
		}

		void load_ogg(std::string _fileName, std::vector<char> &_buffer, ALenum &_format, ALsizei &_freq)
		{
			int endian = 0;
			int bitSream = 0;
			long bytes = 0;
			char array[2048] = { 0 };
			vorbis_info *pInfo = NULL;
			OggVorbis_File oggFile = {0};

			if (ov_fopen(_fileName.c_str(), &oggFile) != 0)
			{
				std::cout << "Failed to open file '" << _fileName << "' for decoding" << std::endl;
				throw std::exception();
			}

			pInfo = ov_info(&oggFile, -1);

			if (pInfo->channels == 1)
			{
				_format = AL_FORMAT_MONO16;
			}
			else
			{
				_format = AL_FORMAT_STEREO16;
			}

			_freq = pInfo->rate;

			while (true)
			{
				bytes = ov_read(&oggFile, array, 2048, endian, 2, 1, &bitSream);
				
				if (bytes < 0)
				{
					ov_clear(&oggFile);
					std::cout << "Failed to decode file '" << _fileName << "'." << std::endl;
				}
				else if (bytes == 0)
				{
					break;
				}

				_buffer.insert(_buffer.end(), array, array + bytes);
			}

			ov_clear(&oggFile);
		}

	};

	std::shared_ptr<Sound> Sound::Create(std::string _path, std::shared_ptr<Resources> _resources)
	{
		std::shared_ptr<Sound> rtn = std::make_shared<Sound>();
		rtn->Load(_path);
		_resources->AddCreatedResource(rtn);
		return rtn;
	}

	void Sound::Load(std::string _path)
	{
		m_impl = std::make_shared <SoundImpl>();

		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<char> bufferData;

		alGenBuffers(1, &m_impl->id);

		m_impl->load_ogg(_path.c_str(), bufferData, format, freq);

		alBufferData(m_impl->id, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);

	}

	void Sound::Play(float _vol, float _varMin, float _varMax, glm::vec3 _soundPosition, glm::vec3 _listenerPosition)
	{
		_varMin *= 1000.0f;
		_varMax *= 1000.0f;
		float variance = (std::rand() % ((int)_varMin + 1 - (int)_varMax) + (int)_varMin) / 1000.0f;
		m_sid = 0;
		alGenSources(1, &m_sid);
		alListener3f(AL_POSITION, _listenerPosition.x, _listenerPosition.y, _listenerPosition.z);
		alSource3f(m_sid, AL_POSITION, _soundPosition.x, _soundPosition.y, _soundPosition.z);
		alSourcei(m_sid, AL_BUFFER, m_impl->id);
		alSourcef(m_sid, AL_PITCH, variance);
		alSourcef(m_sid, AL_GAIN, _vol);
		alSourcePlay(m_sid);
	}

	void Sound::Play(glm::vec3 _soundPosition, glm::vec3 _listenerPosition, bool _looping)
	{
		m_sid = 0;
		alGenSources(1, &m_sid);
		alListener3f(AL_POSITION, _listenerPosition.x, _listenerPosition.y, _listenerPosition.z);
		alSource3f(m_sid, AL_POSITION, _soundPosition.x, _soundPosition.y, _soundPosition.z);
		alSourcei(m_sid, AL_LOOPING, _looping);
		alSourcei(m_sid, AL_BUFFER, m_impl->id);
		alSourcePlay(m_sid);
	}

	void Sound::Stop()
	{
		alSourceStop(m_sid);
	}

}