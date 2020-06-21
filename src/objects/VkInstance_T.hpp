#pragma once

#include "pch.h"
#include "framework.h"
#include "generals/objects.hpp"

namespace dxv {
	class VkInstance_T { 
	protected:
		std::vector<VkPhysicalDevice> devices = {};
		ComPtr<IDXGIFactory4> factory = {};
	public:
		VkInstance_T() {}
		VkInstance_T(const VkInstanceCreateInfo& createInfo, const VkAllocationCallbacks& pAllocator);

		// Provided by VK_VERSION_1_0
		VkResult EnumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
	};
};
