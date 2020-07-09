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

    // Barrier Subpass Images
    VkResult VkCommandBuffer_T::BarrierSubpass(const uint32_t& lsp) {
        auto& renderPassInfo = renderPassBind->GetCreateInfo();
        auto& framebuffers = framebufferBind->subpasses[lsp].colorAttachments;
        auto& initialLayouts = framebufferBind->subpasses[lsp].colorAttachmentsInitialLayout;
        auto& targetLayouts = framebufferBind->subpasses[lsp].colorAttachmentsTargetLayout;
        
        // Barrier All Render Targets
        for (uint32_t i=0;i<framebuffers.size();i++) {
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebuffers[i]);
            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(imageView->GetResource(), getResourceState(initialLayouts[i]), getResourceState(targetLayouts[i])));
        };
        
        { // Barrier Depth Stencil
            const auto* imageView = reinterpret_cast<VkImageView_T*>(framebufferBind->subpasses[lsp].depthStencilAttachment);
            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(imageView->GetResource(), getResourceState(framebufferBind->subpasses[lsp].depthStencilAttachmentInitialLayout), getResourceState(framebufferBind->subpasses[lsp].depthStencilAttachmentTargetLayout)));
        };
    };

};
