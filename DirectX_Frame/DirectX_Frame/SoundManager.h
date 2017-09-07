#pragma once
#include "fmod/inc/fmod.hpp"
#pragma comment (lib, "fmod/lib/fmodex_vc.lib")

#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 10

#define TOTALSOUNDBUFFER (EXTRACHANNELBUFFER + SOUNDBUFFER)

using namespace FMOD;

class cObject;

class SoundDB : public cObject
{
public:
	typedef std::map<std::string, Sound*> arrSounds;
	typedef std::map<std::string, Sound*>::iterator arrSoundsIter;
	typedef std::map<std::string, Channel*> arrChannels;
	typedef std::map<std::string, Channel*>::iterator arrChannelsIter;

private:
	Channel* _channel;
	System* _system;

	arrSounds _mTotalSounds;
	arrChannels _mTotalChannels;
public:
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);


	void AddSound(std::string keyName, std::string soundName, bool background, bool loop);

	Channel* Play(std::string keyName, float volume);
	Channel* Play(std::string keyName);
	void Pause(std::string keyName);
	void Resume(std::string keyName);
	void Stop(std::string keyName);
	void SetPosition(std::string keyName, unsigned int ms);

	void SetChannel(Channel* channel) { _channel = channel; }
	void OrderSound(const TCHAR* keyName);

	bool isPauseSound(std::string keyName);
	bool isPlaySound(std::string keyName);
	unsigned int GetLength(std::string keyName);
	unsigned int GetPosition(std::string keyName);

	SoundDB(void);
	virtual ~SoundDB(void);
};

