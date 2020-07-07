#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkBuffer_T.hpp"

namespace lvx {

    VkResult VkBuffer_T::Create(const lvx::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        
        // Describe and create a Texture2D.
        D3D12_RESOURCE_DESC textureDesc = {};
        textureDesc.MipLevels = 1;
        textureDesc.Format = DXGI_FORMAT_UNKNOWN;
        textureDesc.Width = createInfo->size;
        //textureDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR; // For Vulkan API unusual term...
        textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE; // TODO: flags support

        // 
        textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

        // 
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;

        
        return VK_SUCCESS;
    };

};
