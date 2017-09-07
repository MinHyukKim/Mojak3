#pragma once
//fmod hpp眠啊!!
#include "inc/fmod.hpp"

//lib傅农...
#pragma comment (lib, "lib/fmodex_vc.lib")

#define	g_pSoundManager cSoundManager::GetInstance()

#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 10

#define TOTALSOUNDBUFFER (EXTRACHANNELBUFFER + SOUNDBUFFER)

using namespace FMOD;


class cSoundManager
{
public:
	typedef std::map<std::string, Sound*> arrSounds;
	typedef std::map<std::string, Sound*>::iterator arrSoundsIter;
	typedef std::map<std::string, Channel*> arrChannels;
	typedef std::map<std::string, Channel*>::iterator arrChannelsIter;

private:
	Channel* _channel;
	Sound** _sound;
	System* _system;

	arrSounds _mTotalSounds;
	arrChannels _mTotalChannels;
public:
	virtual HRESULT Init(void);
	void Destroy(void);


	virtual void Update(void);


	void AddSound(std::string keyName, std::string soundName, bool background, bool loop);

	Channel* Play(std::string keyName, float volume);
	Channel* Play(std::string keyName);
	void Pause(std::string keyName);
	void Resume(std::string keyName);
	void Stop(std::string keyName);
	void SetPosition(std::string keyName, unsigned int ms);

	void SetChannel(Channel* channel) { _channel = channel; }
	void OrderSound(LPCSTR keyName);

	bool isPauseSound(std::string keyName);
	bool isPlaySound(std::string keyName);
	unsigned int GetLength(std::string keyName);
	unsigned int GetPosition(std::string keyName);

	//教臂沛 积己
	static cSoundManager* GetInstance() { static cSoundManager instance; return &instance; }

private:
	cSoundManager(void);
	virtual ~cSoundManager(void);
};

