#pragma once
#include "UniEngineAPI.h"
namespace UniEngine
{
	template<typename T>
	class Singleton
	{
	protected:
		Singleton() = default;
		Singleton(Singleton&&) = default;
		Singleton(const Singleton&) = default;
		Singleton& operator=(Singleton&&) = default;
		Singleton& operator=(const Singleton&) = default;
	public:
		UNIENGINE_API static T& Get()
		{
			static T instance;
			return instance;
		}
	};
}