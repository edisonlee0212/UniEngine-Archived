#pragma once
#include "UniEngineAPI.h"
namespace UniEngine
{
	class Texture2D;
	class UNIENGINE_API ResourceBehaviour {
	protected:
		friend class EditorManager;
		std::shared_ptr<Texture2D> _Icon;
	public:
		std::string Name;
		virtual size_t GetHashCode() const
		{
			return reinterpret_cast<size_t>(this);
		}
	};
}
