#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dvx {
    class VkPhysicalDevice_T {
    protected:
        ComPtr<IDXGIAdapter1> adapter = {};
        VkInstance instance = VK_NULL_HANDLE;

    public:
        VkPhysicalDevice_T() {};
        VkPhysicalDevice_T(const dvx::VkInstance_T* instance, ComPtr<IDXGIAdapter1> adapter = {});

        // 
        IDXGIAdapter1* Get() const { return this->adapter.Get(); };
    };
};
