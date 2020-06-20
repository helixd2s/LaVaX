#pragma once

#include "pch.h"
#include "framework.h"
#include "generals/objects.hpp"

namespace dxv {
	class VkDevice_T { 
	public:
		VkDevice_T() {}
		VkDevice_T(const dxv::VkPhysicalDevice_T* physicalDevice, const VkAllocationCallbacks& callbacks, const VkDeviceCreateInfo& createInfo);

	};
};
