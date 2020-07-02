#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkDeviceMemory_T {
    protected:
        ComPtr<ID3D12Heap> memoryHeap = {};
        VkImageViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        
        
    public:
        VkDeviceMemory_T() {}
        VkDeviceMemory_T(const lvx::VkDevice_T* device, ComPtr<ID3D12Heap> memoryHeap = {});

        // 
        ID3D12Heap* Get() const { return memoryHeap.Get(); };
    };

};
