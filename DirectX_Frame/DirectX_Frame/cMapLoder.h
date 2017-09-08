#pragma once

class cMapObject;

class cMapLoder
{
private:

public:
	void Create(cMapObject** ppMap, int nMapSize);



	cMapLoder(void);
	virtual ~cMapLoder(void);
};

