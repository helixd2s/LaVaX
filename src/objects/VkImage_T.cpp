#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkImage_T.hpp"

namespace lvx {

    VkResult VkImage_T::Create(const lvx::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);


        // Describe and create a Texture2D.
        D3D12_RESOURCE_DESC textureDesc = {};
        textureDesc.MipLevels = createInfo->mipLevels;
        textureDesc.Format = convertFormat(createInfo->format);
        textureDesc.Width = createInfo->extent.width;
        textureDesc.Height = createInfo->extent.height;
        textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE; // TODO: flags support
        textureDesc.DepthOrArraySize = createInfo->extent.depth;

        // 
        textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
        if (createInfo->imageType == VK_IMAGE_TYPE_2D) { textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; };
        if (createInfo->imageType == VK_IMAGE_TYPE_3D) { textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D; };

        // TODO: Multi-Sampling Support
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;

        // 
        ThrowIfFailed(device->GetDevice()->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &textureDesc, getResourceState(createInfo->initialLayout), nullptr, IID_PPV_ARGS(&resource)));

        // 
        return VK_SUCCESS;
    };

};
