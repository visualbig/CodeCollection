#include <algorithm>

//Value Declaration

typedef struct _SearchObj
{
	int no;
	// ��ü �ƹ��ų�
}SearchObj;


std::vector<SearchObj*> m_serachobj;


//cpp


void* find_serach(const int no)
{
auto pObj1 = std::find_if(m_serachobj.begin(), m_serachobj.end(), [=](const SearchObj *pSearchObj){ return pSearchObj->no ==  no; });
// ���� find�� �ص� �۵��ؾ��ϳ� ������ ���з� �ӽ� �������� find_if�� �ۼ���
return *pObj1;
}