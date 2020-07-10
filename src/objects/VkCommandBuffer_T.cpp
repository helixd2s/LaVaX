#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkCommandBuffer_T.hpp"
#include "VkCommandPool_T.hpp"
#include "VkRenderPass_T.hpp"
#include "VkFramebuffer_T.hpp"
#include "VkImageView_T.hpp"

namespace lvx {

    //
    D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE convertLoadOp(const VkAttachmentLoadOp& loadOp) {
        switch(loadOp) {
            case VK_ATTACHMENT_LOAD_OP_CLEAR: return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR; break;
            case VK_ATTACHMENT_LOAD_OP_LOAD: return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE; break;
            case VK_ATTACHMENT_LOAD_OP_DONT_CARE: return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_DISCARD; break;
        };
        return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_NO_ACCESS;
    };

        //
    D3D12_RENDER_PASS_ENDING_ACCESS_TYPE convertStoreOp(const VkAttachmentStoreOp& storeOp) {
        switch(storeOp) {
            case VK_ATTACHMENT_STORE_OP_DONT_CARE: return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_DISCARD; break;
            case VK_ATTACHMENT_STORE_OP_NONE_QCOM: return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_NO_ACCESS; break;
            case VK_ATTACHMENT_STORE_OP_STORE: return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE; break;
        };
        //return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_RESOLVE;
        return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_NO_ACCESS;
    };

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

        // TODO: Resolve Type
        std::vector<D3D12_RENDER_PASS_RENDER_TARGET_DESC> passes(framebuffers.size());
        for (uint32_t i=0;i<framebuffers.size();i++) {
            auto& initialLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].initialLayout;
            auto& targetLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].finalLayout;
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebufferBind->GetCreateInfo().pAttachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]]);

            // 
            for (int i=0;i<4u;i++) { passes[i].BeginningAccess.Clear.ClearValue.Color[0] = clearColors[i].float32[0]; };
            passes[i].cpuDescriptor = framebuffers[i];
            passes[i].BeginningAccess.Type = convertLoadOp(renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].loadOp); //= getResourceState(initialLayout);
            passes[i].EndingAccess.Type = convertStoreOp(renderPassBind->attachments[framebufferBind->subpasses[lsp].colorAttachmentsIndex[i]].storeOp);
        };

        // TODO: Resolve Type
        D3D12_RENDER_PASS_DEPTH_STENCIL_DESC depthpass = {};
        { // Barrier Depth Stencil
            auto& initialLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].initialLayout;
            auto& targetLayout = renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].finalLayout;
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebufferBind->GetCreateInfo().pAttachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex]);

            // 
            depthpass.cpuDescriptor = framebufferBind->subpasses[lsp].depthStencilAttachment;
            depthpass.DepthBeginningAccess.Type = convertLoadOp(renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].loadOp);
            depthpass.DepthEndingAccess.Type = convertStoreOp(renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].storeOp);
            depthpass.StencilBeginningAccess.Type = convertLoadOp(renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].stencilLoadOp);
            depthpass.StencilEndingAccess.Type = convertStoreOp(renderPassBind->attachments[framebufferBind->subpasses[lsp].depthStencilAttachmentIndex].stencilStoreOp);
            depthpass.DepthBeginningAccess.Clear.ClearValue.DepthStencil.Depth = this->clearDepthValue.depth;
            depthpass.DepthBeginningAccess.Clear.ClearValue.DepthStencil.Stencil = this->clearDepthValue.stencil;
            depthpass.StencilBeginningAccess.Clear.ClearValue.DepthStencil.Depth = this->clearDepthValue.depth;
            depthpass.StencilBeginningAccess.Clear.ClearValue.DepthStencil.Stencil = this->clearDepthValue.stencil;
        };

        // 
        //commandList->OMSetRenderTargets(framebuffers.size(), framebuffers.data(), FALSE, &framebufferBind->subpasses[lsp].depthStencilAttachment);
        commandList->BeginRenderPass(passes.size(), passes.data(), &depthpass, D3D12_RENDER_PASS_FLAG_NONE);

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
        commandList->EndRenderPass();
        this->BarrierSubpass(lsp); // Transition is Required!
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
