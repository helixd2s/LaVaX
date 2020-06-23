#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {
    class VkInstance_T {
    protected:
        ComPtr<IDXGIFactory4> factory = {};
        std::vector<VkPhysicalDevice> devices = {};
        std::vector<const char*> enabledExtensions = {};
        std::vector<const char*> enabledLayers = {};

    public:
        VkInstance_T() {}
        VkInstance_T(HPTR(VkInstanceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) pAllocator) {
            this->Create(createInfo, pAllocator);
        };

        // 
        VkResult Create(HPTR(VkInstanceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) pAllocator);
        VkResult EnumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices);

        // 
        IDXGIFactory4* Get() const { return factory.Get(); };
    };
};
