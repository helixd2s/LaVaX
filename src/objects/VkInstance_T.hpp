#pragma once

#include "generals/objects.hpp"

// 
namespace dxv {
	class VkInstance_T {
	protected:
		std::vector<VkPhysicalDevice> devices = {};
		ComPtr<IDXGIFactory4> factory = {};
	public:
		VkInstance_T() {}
		VkInstance_T(HPTR(VkInstanceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) pAllocator);

		// 
		VkResult EnumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);
	};
};
