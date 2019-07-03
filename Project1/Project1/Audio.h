#ifndef AUDIO_H
#define AUDIO_H

#include "AudioManager.h"
#include <string>

class Audio
{
public:
	Audio();
	~Audio();

	void Set_Pan(float input_pan);
	void Set_Volume(int input_volume);
	void Set_Mute(bool input_mute);
	void Set_Audio_Data(const std::string& input_id, AudioManager::AudioType input_audio_type);

public:

	bool Play();
	void Pause();
	void Resume();
	void Stop();



private:

	float pan = 0.0f; // -1.0f is fully left, 1.0f is fully right, 0.0f is middle
	float volume = 0.5f;
	bool is_mute = 0;

	FMOD::Sound* audio_data_ptr = nullptr;
	FMOD::Channel* channel_ptr = nullptr;
	FMOD::ChannelGroup* channel_group_ptr = nullptr;
};

#endif

