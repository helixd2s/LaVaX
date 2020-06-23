#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkBuffer_T.hpp"
#include "VkBufferView_T.hpp"

namespace dxv {

    VkResult VkBufferView_T::Create(const dxv::VkDevice_T* device, HPTR(VkBufferViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // Needs to copy into main heaps (i.e. as DirectX 12 Version)
        D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
        srvHeapDesc.NumDescriptors = 1u;
        srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        // TODO: Return Result 
        ThrowIfFailed(device->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&this->heap)));

        // Describe and create a SRV for the texture.
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Format = convertFormat(createInfo->format);
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;

        // TODO: Correct StructureByteStride
        srvDesc.Buffer.FirstElement = createInfo->offset;
        srvDesc.Buffer.NumElements = createInfo->range;
        srvDesc.Buffer.StructureByteStride = 1u;

        // TODO: Return Result 
        device->GetDevice()->CreateShaderResourceView(reinterpret_cast<VkBuffer_T*>(createInfo->buffer)->GetResource().Get(), &srvDesc, this->heap->GetCPUDescriptorHandleForHeapStart());
        return VK_SUCCESS;
    };

};
