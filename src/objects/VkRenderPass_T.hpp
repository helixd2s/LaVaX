#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    // TODO: VkRenderPassCreateInfo2 based object
    class VkRenderPass_T {
    protected:
        VkRenderPassCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;

    public:
        VkRenderPass_T() {}
        VkRenderPass_T(const dxv::VkDevice_T* device, HPTR(VkRenderPassCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const dxv::VkDevice_T* device, HPTR(VkRenderPassCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        const VkRenderPassCreateInfo& GetCreateInfo() { return createInfo; };
    };

};
