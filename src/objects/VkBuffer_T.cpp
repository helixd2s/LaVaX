#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkBuffer_T.hpp"

namespace lvx {

    VkResult VkBuffer_T::Create(const lvx::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        
        // Describe and create a Texture2D.
        D3D12_RESOURCE_DESC bufferDesc = {};
        bufferDesc.MipLevels = 1;
        bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
        bufferDesc.Width = createInfo->size;
        //bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR; // For Vulkan API unusual term...
        bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE; // TODO: flags support
        bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

        // 
        bufferDesc.SampleDesc.Count = 1;
        bufferDesc.SampleDesc.Quality = 0;

        // Used default access flags 
        // TODO: Get Access Flags by Buffer Usage (if single usage defined)
        // TODO: Use Memory Heaps for resources
        ThrowIfFailed(device->GetDevice()->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&resource)));

        // 
        return VK_SUCCESS;
    };

};
