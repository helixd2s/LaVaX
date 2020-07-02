#include "pch/pch.h"
#include "VkDescriptorSetLayout_T.hpp"



namespace lvx {

    

    VkResult VkDescriptorSetLayout_T::Create(const lvx::VkPhysicalDevice_T* device, HPTR(VkDescriptorSetLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->fullRange = 0u; D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL;

        // TODO: Measure Visibility by OR Operation
        for (uint32_t i = 0; i < createInfo->bindingCount; i++) {
            this->ranges.push_back(CD3DX12_DESCRIPTOR_RANGE1{});
            this->ranges.back().Init(convertDescriptorType(createInfo->pBindings[i].descriptorType), createInfo->pBindings[i].descriptorCount, 0, createInfo->pBindings[i].binding, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);

            // offsets needs for binding in heaps
            this->offsets.push_back(this->fullRange);
            this->fullRange += createInfo->pBindings[i].descriptorCount;
        };

        // 
        this->rootParameters.InitAsDescriptorTable(UINT(this->ranges.size()), this->ranges.data(), visibility);
        return VK_SUCCESS; // TODO: Corrent Result
    };

};
