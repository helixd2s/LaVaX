#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkSubpass_T { public: 
        std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> colorAttachments = {};
        D3D12_CPU_DESCRIPTOR_HANDLE depthStencilAttachment = {};
    };

    class VkFramebuffer_T {
    protected:
        ComPtr<ID3D12DescriptorHeap> heap = {};
        VkFramebufferCreateInfo createInfo = {}; // TODO: Cache Create Info with All Pointers
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;

        // When RenderPass used
        std::vector<VkSubpass_T> subpasses = {};
        
    public:
        VkFramebuffer_T() {}
        VkFramebuffer_T(const lvx::VkDevice_T* device, HPTR(VkFramebufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkFramebufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        VkResult Result() const { return result; };

        // 
        ID3D12DescriptorHeap* Get() const { return heap.Get(); };
        
    };

};
