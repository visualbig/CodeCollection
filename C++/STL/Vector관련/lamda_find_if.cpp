#include <algorithm>

//Value Declaration

typedef struct _SearchObj
{
	int no;
	// 객체 아무거나
}SearchObj;


std::vector<SearchObj*> m_serachobj;


//cpp


void* find_serach(const int no)
{
auto pObj1 = std::find_if(m_serachobj.begin(), m_serachobj.end(), [=](const SearchObj *pSearchObj){ return pSearchObj->no ==  no; });
// 원래 find로 해도 작동해야하나 컴파일 실패로 임시 방편으로 find_if로 작성함
return *pObj1;
}