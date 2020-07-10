#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkCommandBuffer_T.hpp"
#include "VkCommandPool_T.hpp"
#include "VkRenderPass_T.hpp"
#include "VkFramebuffer_T.hpp"
#include "VkImageView_T.hpp"

namespace lvx {

    // 
    VkResult VkCommandBuffer_T::Create(const lvx::VkDevice_T* device, const HPTR(VkCommandBufferAllocateInfo) createInfo) {
        // Create the command list.
        this->device = VkDevice(device);

        // TODO: Secondary command list support (i.e. Bundle)
        // TODO: PipelineState support
        ThrowIfFailed(device->GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, reinterpret_cast<VkCommandPool_T*>(createInfo->commandPool)->Get(), nullptr, IID_PPV_ARGS(&commandList)));

        // 
        return VK_SUCCESS;
    };

    //
    VkResult VkCommandBuffer_T::BeginRenderPass(const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) {
        const uint32_t lsp = (this->currentSubpass = 0u); // reset subpass counter;
        this->renderPassBind = reinterpret_cast<VkRenderPass_T*>(pRenderPassBegin->renderPass);
        this->framebufferBind = reinterpret_cast<VkFramebuffer_T*>(pRenderPassBegin->framebuffer);

        // 
        auto& renderPassInfo = renderPassBind->GetCreateInfo();
        auto& framebuffers = framebufferBind->subpasses[lsp].colorAttachments;

        // Reserved for future usage
        for (uint32_t i=0;i<framebuffers.size();i++) {
            auto& initialLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].initialLayout;
            auto& targetLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].finalLayout;
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebufferBind->GetCreateInfo().pAttachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]]);
        };

        // Reserved for future usage
        { // Barrier Depth Stencil
            auto& initialLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].initialLayout;
            auto& targetLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].finalLayout;
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebufferBind->GetCreateInfo().pAttachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex]);
        };

        // 
        commandList->OMSetRenderTargets(framebuffers.size(), framebuffers.data(), FALSE, &framebufferBind->subpasses[lsp].depthStencilAttachment);

        // 
        return VK_SUCCESS;
    };

    // TODO: LoadOp Clear support
    VkResult VkCommandBuffer_T::NextSubpass(VkSubpassContents contents) {
        const uint32_t psp = this->currentSubpass++, lsp = this->currentSubpass;
        this->BarrierSubpass(psp); // Barrier Previous Subpass

        
        return VK_SUCCESS;
    };

    // TODO: LoadOp Clear support
    VkResult VkCommandBuffer_T::EndRenderPass() {
        const uint32_t lsp = this->currentSubpass;
        this->BarrierSubpass(lsp);
        return VK_SUCCESS;
    };

    // Barrier Subpass Images
    VkResult VkCommandBuffer_T::BarrierSubpass(const uint32_t& lsp) {
        auto& renderPassInfo = renderPassBind->GetCreateInfo();
        auto& framebuffers = framebufferBind->subpasses[lsp].colorAttachments;

        // Barrier All Render Targets
        for (uint32_t i=0;i<framebuffers.size();i++) {
            auto& initialLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].initialLayout;
            auto& targetLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].finalLayout;
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebufferBind->GetCreateInfo().pAttachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]]);

            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(imageView->GetResource(), getResourceState(initialLayout), getResourceState(targetLayout)));
        };

        { // Barrier Depth Stencil
            auto& initialLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].initialLayout;
            auto& targetLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].finalLayout;
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebufferBind->GetCreateInfo().pAttachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex]);

            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(imageView->GetResource(), getResourceState(initialLayout), getResourceState(targetLayout)));
        };

        return VK_SUCCESS;
    };

};
