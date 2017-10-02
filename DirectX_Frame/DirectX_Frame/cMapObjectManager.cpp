#include "StdAfx.h"
#include "cMapObjectManager.h"
#include "cBuilding.h"
#include "cMapTerrain.h"


cMapObjectManager::cMapObjectManager(void)
	:m_nBuildCursor(E_OBJECT_TYPE::BUILDING)
	,m_pSelectBuilding(nullptr)
{
}

cMapObjectManager::~cMapObjectManager(void)
{
}

cBuilding* cMapObjectManager::GetMapObject(char* szFolder, char* szFilename)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);

	if (m_mapBuilding.find(sFullPath) == m_mapBuilding.end())
	{
		cBuilding* pBuilding = cBuilding::Create();
		pBuilding->LoadModel(szFolder, szFilename);
		m_mapBuilding[sFullPath] = pBuilding;
	}
	return m_mapBuilding[sFullPath];
}

cBuilding* cMapObjectManager::RegisterMapObject(LPCSTR szFolder, LPCSTR szFilename, LPCSTR szKeyName)
{
	if (m_mapBuilding.find(szKeyName) == m_mapBuilding.end())
	{
		cBuilding* pBuilding = cBuilding::Create();
		pBuilding->LoadModel((LPSTR)szFolder, (LPSTR)szFilename);
		m_mapBuilding[szKeyName] = pBuilding;
	}
	return m_mapBuilding[szKeyName];
}

cBuilding * cMapObjectManager::RegisterMapObject(std::string & szFolder, std::string & szFilename, std::string & szKeyName)
{
	return this->RegisterMapObject(szFolder.c_str(), szFilename.c_str(), szKeyName.c_str());
}

cBuilding* cMapObjectManager::GetMapObject(LPCSTR szKeyName)
{
	if (m_mapBuilding.find(szKeyName) == m_mapBuilding.end()) return nullptr;

	return m_mapBuilding[szKeyName];
}

cBuilding * cMapObjectManager::GetMapObject(std::string & szKeyName)
{
	return this->GetMapObject(szKeyName.c_str());
}

bool cMapObjectManager::AppendBuilding(cBuilding* build)
{
	if (build == NULL) return false;

	cBuilding* pClone = cBuilding::Create(build);
	m_vecBuilding.push_back(pClone);

	return true;
}

bool cMapObjectManager::AppendBuilding(std::string & szKeyName)
{
	return this->AppendBuilding(this->GetMapObject(szKeyName));
	
}

bool cMapObjectManager::AppendBuilding(LPCSTR szKeyName)
{
	return this->AppendBuilding(this->GetMapObject(szKeyName));
}

cBuilding* cMapObjectManager::getMapObjectRotation()
{
	std::map<std::string, cBuilding*>::iterator iMapBuilding = m_mapBuilding.begin();
	for (int i = 0; i < m_nBuildCursor; i++) iMapBuilding++;
	//if (iMapBuilding == m_mapBuilding.end())
	//{
	//	iMapBuilding = m_mapBuilding.begin();
	//	m_nBuildCursor = 0;
	//}
	m_pSelectBuilding = iMapBuilding->second;

	return m_pSelectBuilding;
}

void cMapObjectManager::SetCursorIncrease()
{
	if (m_mapBuilding.size()-1 <= m_nBuildCursor)
	{
		m_nBuildCursor = 0;
	}
	else m_nBuildCursor++;
}

cBuilding * cMapObjectManager::GetLastMapObject()
{
	if (m_vecBuilding.empty()) return nullptr;
	return m_vecBuilding.back();
}

void cMapObjectManager::SetupBuilding(void)
{
	if (this->GetSelectObject() == NULL) return;
	this->AppendBuilding(this->GetSelectObject());
	m_vecBuilding.back()->SetPosition(&m_vLandPos);
}

bool cMapObjectManager::PopMapObject()
{
	if (m_vecBuilding.empty()) return false;
	SAFE_RELEASE(m_vecBuilding.back());
	m_vecBuilding.pop_back();
	return true;
}

//void cMapObjectManager::Update()
//{
//	//if (m_vecBuilding.size() > 0)
//	//{
//	//	for (int i = 0; i < m_vecBuilding.size(); i++)
//	//	{
//	//		m_vecBuilding[i]->Update();
//	//	}
//	//}
//}

void cMapObjectManager::Update(cMapTerrain* map)
{
	if (!m_pSelectBuilding) return;
	D3DXVECTOR3 vPos, vOrg, vDir;
	g_pRay->RayAtWorldSpace(&vOrg, &vDir);
	if (map->IsCollision(&vPos, &vOrg, &vDir))
	{
		m_vLandPos = vPos;
		m_vLandPos.y =  map->GetHeight(vPos.x, vPos.z);
	}
		
	 m_pSelectBuilding->SetPosition(&vPos);
}

void cMapObjectManager::Render()
{
	for each (auto p in m_vecBuilding) p->Render();
	SAFE_RENDER(m_pSelectBuilding);
}

void cMapObjectManager::SaveCurrentObjectsState(const char * filename)
{
	//저장할 빌딩이 없으면 리턴
	if (m_vecBuilding.size() < 1) return;
	FILE *fp;
	fp = fopen(filename, "w");
	for each(auto v in m_vecBuilding)
	{
		//오브젝트 타입 추가예정.
		D3DXMATRIX matTemp = v->GetMatrix();
		const char* test = v->GetFilenname();
		fprintf(fp, "%s\n", v->GetFilenname());
		fprintf(fp, "%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
			matTemp._11, matTemp._12, matTemp._13, matTemp._14,
			matTemp._21, matTemp._22, matTemp._23, matTemp._24,
			matTemp._31, matTemp._32, matTemp._33, matTemp._34,
			matTemp._41, matTemp._42, matTemp._43, matTemp._44);
	}

	fclose(fp);
}

void cMapObjectManager::LoadCurrentObjectsState(const char * filename)
{
	//현재 존재하는 오브젝트들 청소
	for each(auto p in m_vecBuilding)
	{
		SAFE_RELEASE(p);
	}
	m_vecBuilding.clear();

	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) return;
	while (!feof(fp))
	{
		char cTemp[255];
		D3DXMATRIX matTemp;
		fgets(cTemp, 255, fp);
		cTemp[strlen(cTemp) - 1] = '\0';
		fscanf(fp, "%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
			&matTemp._11, &matTemp._12, &matTemp._13, &matTemp._14,
			&matTemp._21, &matTemp._22, &matTemp._23, &matTemp._24,
			&matTemp._31, &matTemp._32, &matTemp._33, &matTemp._34,
			&matTemp._41, &matTemp._42, &matTemp._43, &matTemp._44);
		AppendBuilding(cTemp);
		m_vecBuilding.back()->SetMatrix(matTemp);
	}
	fclose(fp);

}

void cMapObjectManager::Destroy()
{
	for each(auto it in m_mapBuilding)
	{
		it.second->Destroy();
		SAFE_RELEASE(it.second);
	}

//	m_pMapObjects->Destroy();
	for each(auto p in m_vecBuilding)
	{
		SAFE_RELEASE(p);
	}
	m_vecBuilding.clear();
}
