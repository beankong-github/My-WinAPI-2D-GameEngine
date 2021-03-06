#pragma once

class CObj;

// 게임 내의 모든 오브젝트 관리
class CStage
{
private:
	vector<CObj*> m_arrObj[(UINT)EOBJ_TYPE::END];

public:
	virtual void Init() = 0;
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _dc);
	
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void AddObject(CObj* _obj, EOBJ_TYPE _objType) { m_arrObj[(UINT)_objType].push_back(_obj);	}
	const vector<CObj*>& GetObjects(EOBJ_TYPE _eType){ return m_arrObj[(UINT)_eType]; }
	void CreateTile(UINT _iCol,UINT _iRow );

	void Clear(EOBJ_TYPE _type);
	void Clear();

public:
	CStage();
	virtual ~CStage();

};
