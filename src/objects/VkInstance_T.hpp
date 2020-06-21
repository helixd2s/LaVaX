#pragma once

#include "pch.h"
#include "framework.h"
#include "generals/objects.hpp"

namespace dxv {
	class VkInstance_T { 
	public:
		VkInstance_T() {}
		VkInstance_T(const VkAllocationCallbacks* pAllocator, const VkInstanceCreateInfo& createInfo);

	};
};
