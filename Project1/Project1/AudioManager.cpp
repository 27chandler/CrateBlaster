#include "AudioManager.h"
#include <iostream>



AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
	Shutdown();
}

bool AudioManager::Init()
{
	FMOD::System_Create(&audio_system_ptr);

	if (audio_system_ptr->init(100, FMOD_INIT_NORMAL, 0) != FMOD_OK)
	{
		std::cout << "FMOD failed to init..." << std::endl;
		return false;
	}
	
	return true;
}

void AudioManager::Shutdown()
{
	audio_system_ptr->release();
}

bool AudioManager::Load_From_File(const std::string& input_filename, AudioType input_audio_type, const std::string& input_id)
{
	std::cout << "Opening audio file: " << input_filename << std::endl;

	switch (input_audio_type)
	{
		case SFX:
		{
			FMOD::Sound* sfx = nullptr;

			audio_system_ptr->createSound(input_filename.c_str(),FMOD_DEFAULT,0,&sfx);

			if (!sfx)
			{
				std::cout << input_filename << " failed to load..." << std::endl;
				return false;
			}

			sfx_map[input_id] = sfx;
			break;
		}
		case MUSIC: case VOICE:
		{
			FMOD::Sound* audio = nullptr;

			audio_system_ptr->createSound(input_filename.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &audio);

			if (!audio)
			{
				std::cout << input_filename << " failed to load..." << std::endl;
				return false;
			}

			if (input_audio_type == MUSIC)
			{
				music_map[input_id] = audio;
			}
			else
			{
				voice_map[input_id] = audio;
			}
			break;
		}
	}
	return true;
}

void AudioManager::Unload_from_File(AudioType input_audio_type, const std::string& input_id)
{
	switch (input_audio_type)
	{
		case SFX:
		{
			sfx_map[input_id]->release();
			sfx_map.erase(input_id);
			break;
		}
		case MUSIC:
		{
			music_map[input_id]->release();
			music_map.erase(input_id);
			break;
		}
		case VOICE:
		{
			voice_map[input_id]->release();
			voice_map.erase(input_id);
			break;
		}
	}
}

void AudioManager::Update()
{
	audio_system_ptr->update();
}

FMOD::Sound* AudioManager::Get_Audio_Data(AudioType input_audio_type, const std::string input_id)
{
	switch (input_audio_type)
	{
		case SFX:
		{
			return sfx_map[input_id];
			break;
		}
		case MUSIC:
		{
			return music_map[input_id];
			break;
		}
		case VOICE:
		{
			return voice_map[input_id];
			break;
		}
	}
	return nullptr;
}
