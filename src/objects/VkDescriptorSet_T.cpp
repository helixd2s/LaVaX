#include "pch.h"
#include "VkDevice_T.hpp"
#include "VkDescriptorSet_T.hpp"
#include "VkDescriptorSetLayout_T.hpp"

namespace dxv {

    VkDescriptorSet_T::VkDescriptorSet_T(const dxv::VkDevice_T* device, const dxv::VkDescriptorPool_T* descriptorPool, const dxv::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks) {
        // TODO: Extended Types, Per Every Range Heaps
        D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
        srvHeapDesc.NumDescriptors = UINT(descriptorSetLayout->getFullRange());
        srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        // TODO: Return Result 
        ThrowIfFailed(device->getDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&heap)));

        // Per Binding Offsets and Full Range
        this->offsets = descriptorSetLayout->getOffsets();
        this->fullRange = descriptorSetLayout->getFullRange();
    };

};
