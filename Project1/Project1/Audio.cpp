#include "Audio.h"
#include <iostream>



Audio::Audio()
{
}


Audio::~Audio()
{
}

void Audio::Set_Pan(float input_pan)
{
	pan = input_pan;
	if (channel_ptr)
	{
		channel_ptr->setPan(pan);
	}
}

void Audio::Set_Volume(int input_volume)
{
	volume = float(input_volume);
	if (channel_ptr)
	{
		channel_ptr->setVolume(volume);
	}
}

void Audio::Set_Mute(bool input_mute)
{
	is_mute = input_mute;
	if (channel_ptr)
	{
		channel_ptr->setMute(is_mute);
	}
}

void Audio::Set_Audio_Data(const std::string & input_id, AudioManager::AudioType input_audio_type)
{
	audio_data_ptr = TheAudio::Instance()->Get_Audio_Data(input_audio_type, input_id);
}

bool Audio::Play()
{
	if (!channel_ptr)
	{

		if (!channel_ptr)
		{
			std::cout << "Audio failed to play..." << std::endl;
		}
		else
		{
			channel_ptr->setLoopCount(-1);
		}
	}
	TheAudio::Instance()->Get_Audio_System()->playSound(audio_data_ptr, channel_group_ptr, false, &channel_ptr);
	return false;
}

void Audio::Pause()
{
	if (!channel_ptr)
	{
		channel_ptr->setPaused(true);
	}
}

void Audio::Resume()
{
	if (!channel_ptr)
	{
		channel_ptr->setPaused(false);
	}
}

void Audio::Stop()
{
	if (!channel_ptr)
	{
		channel_ptr->stop();
		channel_ptr = nullptr;
	}
}
