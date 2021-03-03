#pragma once
#include "UniEngineAPI.h"
namespace UniEngine
{
	class Texture2D;
	class UNIENGINE_API ResourceBehaviour {
	protected:
		friend class EditorManager;
		std::shared_ptr<Texture2D> m_icon;
	public:
		std::string m_name;
		virtual size_t GetHashCode() const;
	};

	inline size_t ResourceBehaviour::GetHashCode() const
	{
		return reinterpret_cast<size_t>(this);
	}
}
