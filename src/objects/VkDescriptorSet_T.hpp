#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dvx {

    // 
    class VkDescriptorSet_T {
    protected:
        ComPtr<ID3D12DescriptorHeap> heap = {};
        std::vector<uintptr_t> offsets = {};
        size_t fullRange = 0u;
        VkResult result = VK_SUCCESS;

    public:
        VkDescriptorSet_T() {}
        VkDescriptorSet_T(const dvx::VkDevice_T* device, const dvx::VkDescriptorPool_T* descriptorPool, const dvx::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, descriptorPool, descriptorSetLayout, callbacks);
        };

        VkResult Create(const dvx::VkDevice_T* device, const dvx::VkDescriptorPool_T* descriptorPool, const dvx::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks);

        // 
        ID3D12DescriptorHeap* Get() const { return heap.Get(); };
    };

};
