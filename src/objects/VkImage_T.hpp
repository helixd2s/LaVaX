#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkImage_T {
    protected:
        ComPtr<ID3D12Resource> resource = {};
        ComPtr<ID3D12Heap> memory = {}; // Used for copy from buffer to image
        VkImageCreateInfo createInfo = {};
        VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        D3D12_RESOURCE_DESC textureDesc = {};
        
    public:
        VkImage_T() {}
        VkImage_T(const lvx::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        VkResult BindMemory(const lvx::VkDevice_T* device, const lvx::VkDeviceMemory_T* memory, const VkDeviceSize& offset = 0ull);
        VkResult GetMemoryRequirements(const lvx::VkDevice_T* device, VkMemoryRequirements* requirements);
        ComPtr<ID3D12Resource> GetResource() const { return resource; };
        ID3D12Resource* Get() const { return resource.Get(); };
    };

};
