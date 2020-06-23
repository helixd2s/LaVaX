#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkDescriptorSet_T.hpp"
#include "VkDescriptorSetLayout_T.hpp"

namespace dxv {

    // Bindable ONLY FOR ONE Descriptor Set Layout
    VkResult VkDescriptorSet_T::Create(const dxv::VkDevice_T* device, const dxv::VkDescriptorPool_T* descriptorPool, const dxv::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks) {
        // TODO: Extended Types, Per Every Range Heaps
        D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
        srvHeapDesc.NumDescriptors = UINT(descriptorSetLayout->GetFullRange());
        srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        // TODO: Return Result 
        ThrowIfFailed(device->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&heap)));

        // Per Binding Offsets and Full Range
        this->offsets = descriptorSetLayout->GetOffsets();
        this->fullRange = descriptorSetLayout->GetFullRange();
        return VK_SUCCESS; // TODO: Corrent Result
    };

};
