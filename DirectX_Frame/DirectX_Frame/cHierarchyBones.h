#pragma once
class cHierarchyBones : public ID3DXAllocateHierarchy
{
public:
	enum LOAD_TYPE
	{
		LOAD_NULL = 0x0,
		LOAD_BONES = 0x1,
		LOAD_MESHS = 0x2,
	};

private:

public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;

//	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;

	cHierarchyBones(void);
	virtual ~cHierarchyBones(void);
};

