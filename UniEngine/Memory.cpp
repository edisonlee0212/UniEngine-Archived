#include "pch.h"
#include "Memory.h"

size_t UniEngine::Memory::_TotalSize;

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
