#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <map>
#include <fmod.hpp>

#include "Singleton.h"

class AudioManager
{
public:
	enum AudioType { SFX, MUSIC, VOICE };

	AudioManager();
	AudioManager(const AudioManager&);
	AudioManager& operator=(AudioManager&);
	~AudioManager();

	friend class Singleton<AudioManager>;

	bool Init();
	void Shutdown();

	bool Load_From_File(const std::string& input_filename, AudioType input_audio_type, const std::string& input_id);
	void Unload_from_File(AudioType input_audio_type, const std::string& input_id);

	void Update();

	FMOD::System* Get_Audio_System() { return audio_system_ptr; };
	FMOD::Sound* Get_Audio_Data(AudioType input_audio_type, const std::string input_id);


private:

	FMOD::System* audio_system_ptr = nullptr;

	std::map<std::string, FMOD::Sound*> sfx_map;
	std::map<std::string, FMOD::Sound*> music_map;
	std::map<std::string, FMOD::Sound*> voice_map;
};

typedef Singleton<AudioManager> TheAudio;

#endif

