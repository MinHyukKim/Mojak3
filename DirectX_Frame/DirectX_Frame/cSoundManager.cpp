#include "stdafx.h"
#include "cObject.h"
#include "SoundManager.h"

cSoundManager::cSoundManager(void)
{

}

cSoundManager::~cSoundManager(void)
{

}

HRESULT cSoundManager::Init(void)
{
	//���� �ý��� ����
	System_Create(&_system);

	//�ʱ�ȭ
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);


	return S_OK;
}

void cSoundManager::Destroy(void)
{
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}

	_mTotalSounds.clear();
	_mTotalChannels.clear();
}


void cSoundManager::Update(void)
{
	_system->update();
}

void cSoundManager::AddSound(std::string keyName, std::string soundName, bool bgm, bool loop)
{
	//�ʿ� ���尡 �ִٸ� �߰����� ����
	if (_mTotalSounds.find(keyName) != _mTotalSounds.end()) return;

	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_mTotalSounds[keyName]);
		}
		else
		{
			//�Ϲ� �����....
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_mTotalSounds[keyName]);
		}
	}
	else
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_mTotalSounds[keyName]);
	}

}

Channel* cSoundManager::Play(std::string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.find(keyName);
	if (iter == _mTotalSounds.end()) return NULL;

	//ä���� ���� ������ ������ ������ ä�����
	_system->playSound(FMOD_CHANNEL_FREE, iter->second, false, &_mTotalChannels[keyName]);
	_mTotalChannels[keyName]->setVolume(volume);

	return _mTotalChannels[keyName];
}

Channel* cSoundManager::Play(std::string keyName)
{
	//���� ã�� ������ ����
	arrSoundsIter iter = _mTotalSounds.find(keyName);
	if (iter == _mTotalSounds.end()) return NULL;

	//ä���� ���� ������ ������ ������ ä�����
	_system->playSound(FMOD_CHANNEL_FREE, iter->second, false, &_mTotalChannels[keyName]);

	return _mTotalChannels[keyName];
}

void cSoundManager::Pause(std::string keyName)
{
	//ä�� ã�� ������ ����
	arrChannelsIter iter = _mTotalChannels.find(keyName);
	if (iter == _mTotalChannels.end()) return;

	iter->second->setPaused(true);
}

void cSoundManager::Resume(std::string keyName)
{
	arrChannelsIter iter = _mTotalChannels.find(keyName);
	if (iter == _mTotalChannels.end()) return;

	iter->second->setPaused(false);
}

void cSoundManager::Stop(std::string keyName)
{
	arrChannelsIter iter = _mTotalChannels.find(keyName);
	if (iter == _mTotalChannels.end()) return;

	//���� ������ ä�� ������ ����
	iter->second->stop();
	_mTotalChannels.erase(iter);
}

void cSoundManager::SetPosition(std::string keyName, unsigned int ms)
{
	arrChannelsIter iter = _mTotalChannels.find(keyName);
	if (iter == _mTotalChannels.end()) return;

	iter->second->setPosition(ms, FMOD_TIMEUNIT_MS);
}

void cSoundManager::OrderSound(LPCSTR keyName)
{
	bool isPlaye;
	if (_channel) _channel->isPlaying(&isPlaye);
	else isPlaye = false;

	if (!isPlaye) _channel = this->Play(keyName);
}

bool cSoundManager::isPauseSound(std::string keyName)
{
	arrChannelsIter iter = _mTotalChannels.find(keyName);
	if (iter == _mTotalChannels.end()) return false;

	bool isPaused;
	iter->second->getPaused(&isPaused);
	return isPaused;
}

bool cSoundManager::isPlaySound(std::string keyName)
{
	arrChannelsIter iter = _mTotalChannels.find(keyName);
	if (iter == _mTotalChannels.end()) return false;

	bool isPlaying;
	iter->second->isPlaying(&isPlaying);
	return isPlaying;
}

unsigned int cSoundManager::GetLength(std::string keyName)
{
	arrSoundsIter iter = _mTotalSounds.find(keyName);
	if (iter == _mTotalSounds.end()) return NULL;

	unsigned int length = 0;
	iter->second->getLength(&length, FMOD_TIMEUNIT_MS);
	return length;
}

unsigned int cSoundManager::GetPosition(std::string keyName)
{
	arrChannelsIter iter = _mTotalChannels.find(keyName);
	if (iter == _mTotalChannels.end()) return false;

	unsigned int position = 0;
	iter->second->getPosition(&position, FMOD_TIMEUNIT_MS);
	return position;
}
