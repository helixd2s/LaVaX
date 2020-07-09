#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkBuffer_T.hpp"
#include "VkDeviceMemory_T.hpp"

namespace lvx {

    VkResult VkBuffer_T::Create(const lvx::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        
        // Describe and create a Texture2D.
        bufferDesc.MipLevels = 1;
        bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
        bufferDesc.Width = createInfo->size;
        //bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR; // For Vulkan API unusual term...
        bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE; // TODO: flags support
        bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

        // 
        bufferDesc.SampleDesc.Count = 1;
        bufferDesc.SampleDesc.Quality = 0;

        // 
        return VK_SUCCESS;
    };

    VkResult VkBuffer_T::BindMemory(const lvx::VkDevice_T* device, const lvx::VkDeviceMemory_T* memory, const VkDeviceSize& offset){
        // Used default access flags 
        // TODO: Get Access Flags by Buffer Usage (if single usage defined)
        // TODO: Use Memory Heaps for resources
        ThrowIfFailed(device->GetDevice()->CreatePlacedResource(memory->Get(), offset, &bufferDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&resource)));

        // TODO: Correct VkResult
        return VK_SUCCESS;
    };

};
