#include "pch.h"
#include "Memory.h"

size_t UniEngine::Memory::m_totalSize;

void* operator new(size_t size)
{
	void* p = std::malloc(size);
	UniEngine::Memory::m_totalSize += size;
	return p;
}

void operator delete(void* p, size_t size)
{
	UniEngine::Memory::m_totalSize -= size;
	free(p);
}
