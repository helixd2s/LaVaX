#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkDescriptorSetLayout_T {
    protected:
        CD3DX12_ROOT_PARAMETER1 rootParameters = {};
        std::vector<CD3DX12_DESCRIPTOR_RANGE1> ranges = {};
        std::vector<uintptr_t> offsets = {};
        size_t fullRange = 0u;
        VkResult result = VK_SUCCESS;

    public:
        VkDescriptorSetLayout_T() {}
        VkDescriptorSetLayout_T(const lvx::VkPhysicalDevice_T* device, HPTR(VkDescriptorSetLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkPhysicalDevice_T* device, HPTR(VkDescriptorSetLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        size_t GetDescriptorCount() const { return this->ranges.size(); }
        const size_t& GetFullRange() const { return this->fullRange; };
        const std::vector<uintptr_t>& GetOffsets() const { return this->offsets; };

        
    };

};
