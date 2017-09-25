#pragma once
#include "cUiObject.h"

class cUIImageView;

class cProgressBar : public cUiObject
{
private:
	RECT rc;

	float m_fX, m_fY;
	float m_fWidth;

	const char* keyBarDown;
	const char* keyBarUp;

	cUIImageView* m_pGaugeUp;
	cUIImageView* m_pGaugeDown;

public:

	HRESULT SetUp(float x, float y);
	HRESULT SetUp(const char* upKeyName, const char* downKeyName,
		float x, float y, int width, int height);
//	void Reset(void);
//	void Update(void);
//	void Render(void);
//
//	void SetGauge(float current, float max);
//	void SetX(int x) { m_fX = x; }
//	void SetY(int y) { m_fY = y; }
//
//	RECT GetRect(void) { return rc; }

	static cProgressBar* Create(void);
protected:
	cProgressBar(void);
	virtual ~cProgressBar(void);
};