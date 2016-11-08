#pragma  once

#include <string>
#include <map>
#include <vector>
#include <memory>



#ifndef _UNICODE
typedef std::string CtrString;
#else
typedef std::wstring CtrString;
#endif


typedef std::vector<CtrString> CtrList;

typedef std::map<CtrString, CtrString> CtrMap;


#define Vec(T)		std::vector<T>
#define Map(T,U)	std::map<T,U>

template <typename T>
class DeleteObj
{
public:
	static void AllDel(T& delObj)
	{
		T::const_iterator iter;

		for (iter = delObj.begin(); iter != delObj.end(); iter++)
		{
			delete (*iter);
		}

	}

};

//»ç¿ë¹ý 
// Vec(DelObj*)		m_delobj;
// DeleteObj<Vec(DelObj*)>::AllDel(m_delobj);