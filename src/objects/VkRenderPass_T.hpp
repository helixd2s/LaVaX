#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    // TODO: VkRenderPassCreateInfo2 based object
    class VkRenderPass_T { 
    protected: friend VkFramebuffer_T; friend VkCommandBuffer_T;
        // Imported From VKH helpers
        VkRenderPassCreateInfo createInfo = {};
        std::vector<VkAttachmentDescription> attachments = {};
        std::vector<VkSubpassDescription> subpasses = {};
        std::vector<VkSubpassDependency> dependencies = {};
        std::vector<std::vector<VkAttachmentReference>> color_attachments = {};
        std::vector<std::vector<VkAttachmentReference>> input_attachments = {};
        std::vector<VkAttachmentReference> depth_stencil_attachment {};

        // 
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;

    public:
        VkRenderPass_T() {}
        VkRenderPass_T(const lvx::VkDevice_T* device, HPTR(VkRenderPassCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkRenderPassCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        const VkRenderPassCreateInfo& GetCreateInfo() { return createInfo; };
    };

};
