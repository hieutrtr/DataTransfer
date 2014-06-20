#include "FileMapping.h"

CFileMapping::CFileMapping()
{
	m_pBuffer = NULL;
	m_lLength = 0;
}

CFileMapping::~CFileMapping()
{
	UnMap();
}

void* CFileMapping::Map(string strFileName)
{
	int fd;
	struct stat sb;
	fd = open(strFileName.c_str(), O_RDONLY);

	// Cannot open file to map
    if (fd == -1)
	{
		return NULL;
	}
        
	// Cannot get file size
    if (fstat(fd, &sb) == -1)           
	{
		return NULL;
	}        

	m_lLength = sb.st_size;
	m_pBuffer = mmap(0, m_lLength, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	return m_pBuffer;
}

void CFileMapping::UnMap()
{
	if (NULL != m_pBuffer)
	{
		munmap(m_pBuffer, m_lLength);
		m_pBuffer = NULL;
	}
}