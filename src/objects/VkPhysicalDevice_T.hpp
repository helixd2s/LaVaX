#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {
    class VkPhysicalDevice_T {
    protected:
        ComPtr<IDXGIAdapter1> adapter = {};
        ComPtr<ID3D12Device> device = {};
        VkInstance instance = VK_NULL_HANDLE;
        UINT nodeMask = 1u;

    public:
        VkPhysicalDevice_T() {};
        VkPhysicalDevice_T(const lvx::VkInstance_T* instance, ComPtr<IDXGIAdapter1> adapter = {}, ComPtr<ID3D12Device> device = {});

        // 
        IDXGIAdapter1* Get() const { return this->adapter.Get(); };

        //
        //GetCustomHeapProperties
        void GetPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties);
    };
};
