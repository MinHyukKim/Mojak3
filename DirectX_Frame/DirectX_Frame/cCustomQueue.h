#pragma once

template<typename T>
class cCustomQueue
{
private:
	std::vector<T> m_vecAsterNode;

public:
	void Push(const T& AstarNode)
	{
		AstarNode.SetPriority(m_vecAsterNode.size());
		m_vecAsterNode.push_back(AstarNode);
		Update_Push(m_vecAsterNode.size() - 1);
	}
	const T Top(void)
	{
		if (m_vecAsterNode.empty()) return NULL;
		return m_vecAsterNode[0];
	}
	void Pop(void)
	{
		if (m_vecAsterNode.empty()) return;
		m_vecAsterNode[0].SetPointer(m_vecAsterNode[m_vecAsterNode.size() - 1].GetPointer());
		m_vecAsterNode.pop_back();
		if (m_vecAsterNode.empty()) return;
		Update_Pop(0);
	}
	void Clear(void) { m_vecAsterNode.clear(); }
	int Size(void) { return m_vecAsterNode.size(); }

	void Update_Push(int _nPriority)
	{
		int nParent = (_nPriority - 1) / 2;
		if (!_nPriority || m_vecAsterNode[_nPriority] >= m_vecAsterNode[nParent]) return;

		cAstar* temp = m_vecAsterNode[_nPriority].GetPointer();
		m_vecAsterNode[_nPriority].SetPointer(m_vecAsterNode[nParent].GetPointer());
		m_vecAsterNode[nParent].SetPointer(temp);

		m_vecAsterNode[_nPriority].SetPriority(_nPriority);
		m_vecAsterNode[nParent].SetPriority(nParent);

		this->Update_Push(nParent);
	}
	void Update_Pop(int _nPriority)
	{
		int nChild = _nPriority * 2 + 1;
		if (m_vecAsterNode.size() <= nChild) return;
		nChild = (nChild + 1 < m_vecAsterNode.size() && m_vecAsterNode[nChild + 1] <= m_vecAsterNode[nChild]) ? nChild + 1 : nChild;
		if (m_vecAsterNode[_nPriority] < m_vecAsterNode[nChild]) return;

		cAstar* temp = m_vecAsterNode[_nPriority].GetPointer();
		m_vecAsterNode[_nPriority].SetPointer(m_vecAsterNode[nChild].GetPointer());
		m_vecAsterNode[nChild].SetPointer(temp);

		m_vecAsterNode[_nPriority].SetPriority(_nPriority);
		m_vecAsterNode[nChild].SetPriority(nChild);

		this->Update_Pop(nChild);
	}

	cCustomQueue(void);
	virtual ~cCustomQueue(void);
private:
};

