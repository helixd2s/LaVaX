#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    // 
    class VkDescriptorSet_T {
    protected:
        ComPtr<ID3D12DescriptorHeap> heap = {};
        std::vector<uintptr_t> offsets = {};
        size_t fullRange = 0u;
        VkResult result = VK_SUCCESS;

    public:
        VkDescriptorSet_T() {}
        VkDescriptorSet_T(const lvx::VkDevice_T* device, HPTR(VkDescriptorSetAllocateInfo) createInfo, const lvx::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, descriptorSetLayout, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkDescriptorSetAllocateInfo) createInfo, const lvx::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks);

        // 
        ID3D12DescriptorHeap* Get() const { return heap.Get(); };
    };

};
