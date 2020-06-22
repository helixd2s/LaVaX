#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    class VkFramebuffer_T {
    protected:
        VkFramebufferCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        
        // When RenderPass used
        std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> colorAttachments = {};
        D3D12_CPU_DESCRIPTOR_HANDLE depthStencilAttachment = {};
        
    public:
        VkFramebuffer_T() {}
        VkFramebuffer_T(const dxv::VkDevice_T* device, HPTR(VkFramebufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const dxv::VkDevice_T* device, HPTR(VkFramebufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

    };

};
