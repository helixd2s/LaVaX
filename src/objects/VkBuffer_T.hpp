#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkBuffer_T {
    protected:
        ComPtr<ID3D12Resource> resource = {};
        ComPtr<ID3D12Heap> memory = {}; // Used for copy from buffer to image
        VkBufferCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        D3D12_RESOURCE_DESC bufferDesc = {};
        D3D12_RESOURCE_STATES state = {}; // i.e. VkAccessFlags

    public:
        VkBuffer_T() {}
        VkBuffer_T(const lvx::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        ComPtr<ID3D12Resource> GetResource() const { return resource; };
        ID3D12Resource* Get() const { return resource.Get(); };
    };

};
