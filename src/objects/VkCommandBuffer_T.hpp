#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkCommandBuffer_T {
    protected:
        ComPtr<ID3D12GraphicsCommandList4> commandList = {};
        VkImageViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        VkRenderPass_T* renderPassBind = {};
        VkFramebuffer_T* framebufferBind = {};
        uint32_t currentSubpass = 0u;
        std::vector<VkClearColorValue> clearColors = {};
        VkClearDepthStencilValue clearDepthValue = {};

    public:
        VkCommandBuffer_T() {}
        VkCommandBuffer_T(const lvx::VkDevice_T* device, const HPTR(VkCommandBufferAllocateInfo) createInfo) {
            this->result = this->Create(device, createInfo);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, const HPTR(VkCommandBufferAllocateInfo) createInfo);
        ID3D12GraphicsCommandList4* Get() const { return commandList.Get(); };

        VkResult BeginRenderPass(const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents);
        VkResult NextSubpass(VkSubpassContents contents);
        VkResult EndRenderPass();
        VkResult BarrierSubpass(const uint32_t& lsp);
    };

};
