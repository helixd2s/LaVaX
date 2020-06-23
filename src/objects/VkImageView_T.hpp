#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    class VkImageView_T {
    protected:
        VkImageViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        D3D12_CPU_DESCRIPTOR_HANDLE handle = {};
        
    public:
        VkImageView_T() {}
        VkImageView_T(const dxv::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const dxv::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        D3D12_CPU_DESCRIPTOR_HANDLE& Handle() { return handle; };
        const D3D12_CPU_DESCRIPTOR_HANDLE& Handle() const { return handle; };
    };

};
