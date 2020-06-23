#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkFramebuffer_T.hpp"
#include "VkRenderPass_T.hpp"
#include "VkImageView_T.hpp"

namespace dxv {

    VkResult VkFramebuffer_T::Create(const dxv::VkDevice_T* device, HPTR(VkFramebufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // 
        auto renderPass = reinterpret_cast<VkRenderPass_T*>(this->createInfo.renderPass);
        this->colorAttachments.resize(0);
        this->depthStencilAttachment = {};

        // TODO: Multiple Subpass Support
        if (renderPass->GetCreateInfo().subpassCount > 0) {   // TODO: caching of subpass and attachments
            auto subpass = renderPass->GetCreateInfo().pSubpasses[0];
            for (uint32_t i=0;i<subpass.colorAttachmentCount;i++) {
                auto attachment = subpass.pColorAttachments[i];
                auto imageView = createInfo->pAttachments[attachment.attachment];
                this->colorAttachments.push_back(reinterpret_cast<VkImageView_T*>(imageView)->Handle());
            };
            if (subpass.pDepthStencilAttachment) {
                auto attachment = subpass.pDepthStencilAttachment[0];
                auto imageView = createInfo->pAttachments[attachment.attachment];
                this->depthStencilAttachment = reinterpret_cast<VkImageView_T*>(imageView)->Handle();
            };
        };

        // TODO: Correct VkResult
        return VK_SUCCESS;
    };

};
