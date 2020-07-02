#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkImage_T {
    protected:
        ComPtr<ID3D12Resource> resource = {};
        VkImageCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        
    public:
        VkImage_T() {}
        VkImage_T(const lvx::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        ComPtr<ID3D12Resource> GetResource() const { return resource; };
        ID3D12Resource* Get() const { return resource.Get(); };
    };

};
