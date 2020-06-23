#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkFramebuffer_T.hpp"
#include "VkRenderPass_T.hpp"
#include "VkImageView_T.hpp"

namespace dxv {

    VkResult VkFramebuffer_T::Create(const dxv::VkDevice_T* device, HPTR(VkFramebufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // Needs to copy into main heaps (i.e. as DirectX 12 Version)
        D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
        srvHeapDesc.NumDescriptors = createInfo->attachmentCount;
        srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        // TODO: Return Result 
        ThrowIfFailed(device->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&this->heap)));

        // 
        for (uint32_t i = 0; i < createInfo->attachmentCount; i++) {

            // But required type conversion...
            device->GetDevice()->CopyDescriptorsSimple(
                1u, reinterpret_cast<VkImageView_T*>(createInfo->pAttachments[i])->Handle(),
                CD3DX12_CPU_DESCRIPTOR_HANDLE(this->heap->GetCPUDescriptorHandleForHeapStart(), i, device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)),
                D3D12_DESCRIPTOR_HEAP_TYPE_RTV
            );

            // Descriptor Type Correctly
            //reinterpret_cast<VkImageView_T*>(createInfo->pAttachments[i])->Create(device, CD3DX12_CPU_DESCRIPTOR_HANDLE(this->heap->GetCPUDescriptorHandleForHeapStart(), i, device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));

        };

        // 
        auto renderPass = reinterpret_cast<VkRenderPass_T*>(this->createInfo.renderPass); this->subpasses.resize(0u);
        for (uint32_t i=0;i<renderPass->subpasses.size();i++) {
            auto subpass = renderPass->subpasses[i];
            this->subpasses.push_back(VkSubpass_T{});
            for (uint32_t i=0;i<subpass.colorAttachmentCount;i++) {
                auto& attachment = subpass.pColorAttachments[i];
                this->subpasses.back().colorAttachments.push_back(CD3DX12_CPU_DESCRIPTOR_HANDLE(this->heap->GetCPUDescriptorHandleForHeapStart(), attachment.attachment, device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)));
            };
            if (subpass.pDepthStencilAttachment) {
                auto& attachment = subpass.pDepthStencilAttachment[0];
                this->subpasses.back().depthStencilAttachment = CD3DX12_CPU_DESCRIPTOR_HANDLE(this->heap->GetCPUDescriptorHandleForHeapStart(), attachment.attachment, device->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            };
        };

        // TODO: Correct VkResult
        return VK_SUCCESS;
    };

};
