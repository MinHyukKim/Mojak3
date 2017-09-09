#pragma once

class cMapObject;

class cMapLoder
{
private:

public:
	void Create(cMapObject** ppMap, int nMapSize, LPD3DXMATERIAL pTexMtl);



	cMapLoder(void);
	virtual ~cMapLoder(void);
};

