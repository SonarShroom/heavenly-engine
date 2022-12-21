#pragma once

#include <filesystem>

namespace Heavenly::Resources
{
class Manager;

class IResource
{
public:
	using UUIDType = unsigned int;

	explicit IResource(const UUIDType uuid) : UUID(uuid) { }
	virtual ~IResource() = default;

	IResource(const IResource&) = delete;
	IResource& operator = (const IResource&) = delete;

private:
	friend Manager;
	const UUIDType UUID = 0;
};

}
