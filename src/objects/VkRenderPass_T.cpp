#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkRenderPass_T.hpp"

namespace dxv {

    // Do caching (alike RenderPass helper of VKH)
    VkResult VkRenderPass_T::Create(const dxv::VkDevice_T* device, HPTR(VkRenderPassCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) { 
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // 
        this->color_attachments.resize(0u);
        this->input_attachments.resize(0u);
        this->depth_stencil_attachment.resize(0u);

        // Subpass
        this->subpasses.resize(0u);
        for (uint32_t i=0;i<createInfo->subpassCount;i++) {
            this->subpasses.push_back(createInfo->pSubpasses[i]);

            // 
            this->color_attachments.push_back({});
            this->input_attachments.push_back({});
            this->depth_stencil_attachment.push_back({});

            // 
            for (uint32_t j=0;j<this->subpasses.back().colorAttachmentCount;j++) { this->color_attachments[i].push_back(this->subpasses.back().pColorAttachments[j]); };
            for (uint32_t j=0;j<this->subpasses.back().inputAttachmentCount;j++) { this->input_attachments[i].push_back(this->subpasses.back().pInputAttachments[j]); };
            this->depth_stencil_attachment[i] = *this->subpasses.back().pDepthStencilAttachment;

            // 
            this->subpasses.back().pColorAttachments = this->color_attachments[i].data();
            this->subpasses.back().pInputAttachments = this->input_attachments[i].data();
            this->subpasses.back().pDepthStencilAttachment = &this->depth_stencil_attachment[i];
        };
        this->createInfo.pSubpasses = this->subpasses.data();

        // Attachments
        this->attachments.resize(0u);
        for (uint32_t i=0;i<createInfo->attachmentCount;i++) {
            this->attachments.push_back(createInfo->pAttachments[i]);
        };
        this->createInfo.pAttachments = this->attachments.data();

        // Dependencies
        this->dependencies.resize(0u);
        for (uint32_t i=0;i<createInfo->dependencyCount;i++) {
            this->dependencies.push_back(createInfo->pDependencies[i]);
        };
        this->createInfo.pDependencies = this->dependencies.data();
        
        // TODO: Correct VkResult
        return VK_SUCCESS;
    };

};
