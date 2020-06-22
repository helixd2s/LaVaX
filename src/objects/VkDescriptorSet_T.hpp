#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    // 
    class VkDescriptorSet_T {
    protected:
        ComPtr<ID3D12DescriptorHeap> heap = {};
        std::vector<uintptr_t> offsets = {};
        size_t fullRange = 0u;
        VkResult result = VK_SUCCESS;

    public:
        VkDescriptorSet_T() {}
        VkDescriptorSet_T(const dxv::VkDevice_T* device, const dxv::VkDescriptorPool_T* descriptorPool, const dxv::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, descriptorPool, descriptorSetLayout, callbacks);
        };

        VkResult Create(const dxv::VkDevice_T* device, const dxv::VkDescriptorPool_T* descriptorPool, const dxv::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks);
    };

};
