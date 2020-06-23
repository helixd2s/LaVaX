#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    class VkBuffer_T {
    protected:
        ComPtr<ID3D12Resource> resource = {};
        VkBufferCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        
    public:
        VkBuffer_T() {}
        VkBuffer_T(const dxv::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const dxv::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        ComPtr<ID3D12Resource> GetResource() const { return resource; };
        ID3D12Resource* Get() const { return resource.Get(); };
    };

};
