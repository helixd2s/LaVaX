#pragma once

#include "generals/objects.hpp"

// 
namespace dxv {

    class VkDescriptorSetLayout_T {
    protected:
        CD3DX12_ROOT_PARAMETER1 rootParameters = {};
        std::vector<CD3DX12_DESCRIPTOR_RANGE1> ranges = {};
        std::vector<uintptr_t> offsets = {};
        size_t fullRange = 0u;

    public:
        VkDescriptorSetLayout_T() {}
        VkDescriptorSetLayout_T(const dxv::VkPhysicalDevice_T* device, HPTR(VkDescriptorSetLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

        // 
        size_t getDescriptorCount() const { return this->ranges.size(); }
        const size_t& getFullRange() const { return this->fullRange; };
        const std::vector<uintptr_t>& getOffsets() const { return this->offsets; };
    };

};
