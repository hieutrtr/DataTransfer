#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../Common/Common.h"

class CFileMapping
{
public:
	CFileMapping();
	~CFileMapping();
		
	inline long GetLength() { return m_lLength; }
	
	void* Map(string strFileName);
	void UnMap();
	
protected:
	void* m_pBuffer;
	long m_lLength;
};