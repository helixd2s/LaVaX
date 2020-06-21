#pragma once

#include "pch.h"
#include "generals/objects.hpp"

// 
namespace dxv {
	class VkPhysicalDevice_T { 
	protected:
		ComPtr<IDXGIAdapter1> adapter = {};
		VkInstance instance = VK_NULL_HANDLE;
	public:
		VkPhysicalDevice_T() {};
		VkPhysicalDevice_T(const dxv::VkInstance_T* instance, ComPtr<IDXGIAdapter1> adapter = {});

		// 
		IDXGIAdapter1* Get() const { return this->adapter.Get(); };
	};
};
