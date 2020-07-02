#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    // TODO: VkCommandPoolCreateInfo2 based object
    class VkCommandPool_T {
    protected:
        ComPtr<ID3D12CommandAllocator> commandAllocator = {};
        VkCommandPoolCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;

    public:
        VkCommandPool_T() {}
        VkCommandPool_T(const lvx::VkDevice_T* device, HPTR(VkCommandPoolCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkCommandPoolCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        const VkCommandPoolCreateInfo& GetCreateInfo() { return createInfo; };

        // 
        ID3D12CommandAllocator* Get() const { return commandAllocator.Get(); };
    };

};
