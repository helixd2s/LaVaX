#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkImage_T.hpp"
#include "VkDeviceMemory_T.hpp"

namespace lvx {

    // 
    UINT getSampleCount(const vkh::VkSampleCountFlags& samples){
        if (samples.e1) return 1u;
        if (samples.e2) return 2u;
        if (samples.e4) return 4u;
        if (samples.e8) return 8u;
        if (samples.e16) return 16u;
        if (samples.e32) return 32u;
        if (samples.e64) return 64u;
        return 1u;
    };

    // 
    UINT getSampleCount(const VkSampleCountFlagBits& samples){
        switch(samples) {
            case VK_SAMPLE_COUNT_1_BIT: return 1u; break;
            case VK_SAMPLE_COUNT_2_BIT: return 2u; break;
            case VK_SAMPLE_COUNT_4_BIT: return 4u; break;
            case VK_SAMPLE_COUNT_8_BIT: return 8u; break;
            case VK_SAMPLE_COUNT_16_BIT: return 16u; break;
            case VK_SAMPLE_COUNT_32_BIT: return 32u; break;
            case VK_SAMPLE_COUNT_64_BIT: return 64u; break;
            default: return 1u;
        };
        return 1u;
    };

    // 
    VkResult VkImage_T::Create(const lvx::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // Describe and create a Texture2D.
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

        // 
        textureDesc.SampleDesc.Count = getSampleCount(createInfo->samples);
        textureDesc.SampleDesc.Quality = 0; // TODO: Implement Quality

        // 
        // TODO: Use Memory Heaps for resources
        this->initialLayout = createInfo->initialLayout;

        // TODO: Correct VkResult
        return VK_SUCCESS;
    };

    // 
    VkResult VkImage_T::BindMemory(const lvx::VkDevice_T* device, const lvx::VkDeviceMemory_T* memory, const VkDeviceSize& offset) {
        // TODO: Missed features...
        ThrowIfFailed(device->GetDevice()->CreatePlacedResource(memory->Get(), offset, &textureDesc, getResourceState(this->initialLayout), nullptr, IID_PPV_ARGS(&resource)));

        // TODO: Correct VkResult
        return VK_SUCCESS;
    };
    
    // 
    VkResult VkImage_T::GetMemoryRequirements(const lvx::VkDevice_T* device, VkMemoryRequirements* requirements) {
        D3D12_RESOURCE_ALLOCATION_INFO allocationInfo = device->GetDevice()->GetResourceAllocationInfo(0u, 1u, &textureDesc); // TODO: Multi-GPU Support
        requirements->alignment = allocationInfo.Alignment;
        requirements->size = allocationInfo.SizeInBytes;
        requirements->memoryTypeBits = 1u; 

        // TODO: Correct VkResult
        return VK_SUCCESS;
    };

};
