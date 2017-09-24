#pragma once

#define g_pMath cMath::GetInstance()

class cMath
{
private:
public:
	int GetInt(int nNum) { return Random(nNum); }
	int GetFromIntTo(int nFrom, int nTo) { return Random(nFrom, nTo); }
	float GetFloat(void) { return this->Random(); }
	float GetFloat(float fNum) { return this->Random(fNum); }
	float GetFromFloatTo(float fFrom, float fTo) { return this->Random(fFrom, fTo); }

	const int Random(int nNum) { return rand() % nNum; }
	const int Random(int nFrom, int nTo) { return rand() % (nTo - nFrom + 1) + nFrom; }
	const float Random(void) { return ((float)rand() / (float)RAND_MAX); }
	const float Random(float fNum) { return ((float)rand() / (float)RAND_MAX * fNum); }
	const float Random(float fFrom, float fTo) { return ((float)rand() / (float)RAND_MAX * (fTo - fFrom) + fFrom); }

	const bool Probability(float fPercent) { return Random(100.0f) <= fPercent; }

	static cMath* GetInstance(void) { static cMath instance; return &instance; }
private:
	cMath(void);
	virtual ~cMath(void);
};

