#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkDescriptorSetLayout_T {
    protected:
        ComPtr<ID3D12RootSignature> signature = {};
        ComPtr<ID3DBlob> signature = {}, error = {};
        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
        VkResult result = VK_SUCCESS;

    public:
        VkDescriptorSetLayout_T() {}
        VkDescriptorSetLayout_T(const lvx::VkDevice_T* device, HPTR(VkPipelineLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkPipelineLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

        
    };

};
