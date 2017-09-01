#pragma once

template <class T>
class Singleton
{
private:
	static T* _singleton;

public:
	static T* GetSingleton(void);
	void ReleaseSingleton(void);

protected:
	Singleton(void) {}
	virtual ~Singleton(void) {}
};


template <typename T>
T* Singleton<T>::_singleton = 0;

template <typename T>
T* Singleton<T>::GetSingleton(void)
{
	if (!_singleton) _singleton = new T;
	return _singleton;
}

template <typename T>
void Singleton<T>::ReleaseSingleton(void)
{
	if (_singleton)
	{
		delete _singleton;
		_singleton = 0;
	}
}