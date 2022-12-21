#pragma once

#include <map>
#include <memory>
#include <random>

#include "Resource.h"

namespace Heavenly::Resources
{

class Manager {
public:
	using UUIDType = decltype(IResource::UUID);

	template <class ResourceT, typename ...ArgsT>
	requires std::is_base_of_v<IResource, ResourceT>
	ResourceT* CreateResource(ArgsT&&... args)
	{
		std::random_device rand_dev;
		std::mt19937 rng(rand_dev());
		std::uniform_int_distribution<UUIDType> dist(0, std::numeric_limits<UUIDType>::max());
		auto _newUUID = dist(rng);

		auto _newResource = std::make_unique<ResourceT>(_newUUID, std::forward<ArgsT>(args)...);
		auto* _newResourcePtr = _newResource.get();
		resources[_newUUID] = std::move(_newResource);
		return _newResourcePtr;
	}

	template <class ResourceT, typename ...ArgsT>
	requires std::is_base_of_v<IResource, ResourceT>
	ResourceT* GetResource(UUIDType uuid) const
	{
		if (resources.count(uuid))
		{
			return dynamic_cast<ResourceT*>(resources.at(uuid));
		}
	}

	inline void DeleteResource(UUIDType uuid) { resources.erase(uuid); }

private:
	std::map<UUIDType, std::unique_ptr<IResource>> resources;
};

}
