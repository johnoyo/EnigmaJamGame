#pragma once

#include "../Utilities.h"
#include "../HumbleAPI.h"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <unordered_map>

namespace HBL 
{
	class HBL_API SoundManager 
	{
	public:
		SoundManager(const SoundManager&) = delete;

		static SoundManager& Get() 
		{
			static SoundManager instance;
			return instance;
		}

		static void Start() { Get().IStart(); }
		static void Update() { Get().IUpdate(); }
		static void Clean() { Get().IClean(); }
		static void Play(const std::string& source, bool playLooped = false, bool startPaused = false) { Get().IPlay(source, playLooped, startPaused); }

	private:
		SoundManager() {}

		void IStart();
		void IUpdate();
		void IClean();
		bool IExists(const std::string& soundName);
		void IPlay(const std::string& source, bool playLooped = false, bool startPaused = false);
		bool ISucceededOrWarn(const std::string& message, FMOD_RESULT result);

		FMOD::System* system = nullptr;
		FMOD::Channel* channel = nullptr;
		FMOD::ChannelGroup* channelGroup = nullptr;
		FMOD_RESULT result;
		std::unordered_map<std::string, FMOD::Sound*> sounds;
	};
}
