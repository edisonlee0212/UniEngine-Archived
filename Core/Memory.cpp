#include "pch.h"
#include "Memory.h"

void* operator new(size_t size)
{
	void* p = std::malloc(size);
	UniEngine::Memory::_TotalSize += size;
	return p;
}

void operator delete(void* p, size_t size)
{
	UniEngine::Memory::_TotalSize -= size;
	free(p);
}
