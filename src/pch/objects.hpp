#pragma once

// 
#include "pch/pch.h"

// 
#define HPTR(NAME) const vkt::uni_dir<vkh::NAME,::NAME>&
#define UPTR(NAME) const vkt::uni_arg<NAME>&

// 
namespace dxv {
    
    class VkInstance_T;
    class VkDevice_T;
    class VkQueue_T;
    class VkPhysicalDevice_T;
    class VkDescriptorSetLayout_T;
    class VkDescriptorSet_T;
    class VkDescriptorPool_T;
    class VkPipelineLayout_T;
    class VkCommandPool_T;
    class VkCommandBuffer_T;
    class VkBuffer_T;
    class VkBufferView_T;
    class VkImage_T;
    class VkImageView_T;
    class VkDeviceMemory_T;
    class VkRenderPass_T;
    class VkFramebuffer_T;

    // Final Fight
    D3D12_SRV_DIMENSION convertDimension(const VkImageViewType& type) {
        switch(type) {
            case VK_IMAGE_VIEW_TYPE_1D: return D3D12_SRV_DIMENSION_TEXTURE1D; break;
            case VK_IMAGE_VIEW_TYPE_2D: return D3D12_SRV_DIMENSION_TEXTURE2D; break;
            case VK_IMAGE_VIEW_TYPE_3D: return D3D12_SRV_DIMENSION_TEXTURE3D; break;
            case VK_IMAGE_VIEW_TYPE_1D_ARRAY: return D3D12_SRV_DIMENSION_TEXTURE1DARRAY; break;
            case VK_IMAGE_VIEW_TYPE_2D_ARRAY: return D3D12_SRV_DIMENSION_TEXTURE2DARRAY; break;
            case VK_IMAGE_VIEW_TYPE_CUBE: return D3D12_SRV_DIMENSION_TEXTURECUBE; break;
            case VK_IMAGE_VIEW_TYPE_CUBE_ARRAY: return D3D12_SRV_DIMENSION_TEXTURECUBEARRAY; break;
            default: 
        };
        return D3D12_SRV_DIMENSION_UNKNOWN;
    };

    // Format Fight
    DXGI_FORMAT convertFormat(const VkFormat& format) {
        switch(format) {
            // Signed float 32-bit
            case VK_FORMAT_R32G32B32A32_SFLOAT: DXGI_FORMAT_R32G32B32A32_FLOAT;
            case VK_FORMAT_R32G32B32_SFLOAT   : DXGI_FORMAT_R32G32B32_FLOAT;
            case VK_FORMAT_R32G32_SFLOAT      : DXGI_FORMAT_R32G32_FLOAT;
            case VK_FORMAT_R32_SFLOAT         : DXGI_FORMAT_R32_FLOAT;

            // Unsigned int 32-bit
            case VK_FORMAT_R32G32B32A32_UINT: DXGI_FORMAT_R32G32B32A32_UINT;
            case VK_FORMAT_R32G32B32_UINT   : DXGI_FORMAT_R32G32B32_UINT;
            case VK_FORMAT_R32G32_UINT      : DXGI_FORMAT_R32G32_UINT;
            case VK_FORMAT_R32_UINT         : DXGI_FORMAT_R32_UINT;

            // Signed int 32-bit
            case VK_FORMAT_R32G32B32A32_SINT: DXGI_FORMAT_R32G32B32A32_UINT;
            case VK_FORMAT_R32G32B32_SINT   : DXGI_FORMAT_R32G32B32_UINT;
            case VK_FORMAT_R32G32_SINT      : DXGI_FORMAT_R32G32_UINT;
            case VK_FORMAT_R32_SINT         : DXGI_FORMAT_R32_UINT;

            // Signed float 16-bit
            case VK_FORMAT_R16G16B16A16_SFLOAT: DXGI_FORMAT_R16G16B16A16_FLOAT;
            case VK_FORMAT_R16G16_SFLOAT      : DXGI_FORMAT_R16G16_FLOAT;
            case VK_FORMAT_R16_SFLOAT         : DXGI_FORMAT_R16_FLOAT;

            // Unsigned int 16-bit
            case VK_FORMAT_R16G16B16A16_UINT: DXGI_FORMAT_R16G16B16A16_UINT;
            case VK_FORMAT_R16G16_UINT      : DXGI_FORMAT_R16G16_UINT;
            case VK_FORMAT_R16_UINT         : DXGI_FORMAT_R16_UINT;

            // Signed int 16-bit
            case VK_FORMAT_R16G16B16A16_SINT: DXGI_FORMAT_R16G16B16A16_SINT;
            case VK_FORMAT_R16G16_SINT      : DXGI_FORMAT_R16G16_SINT;
            case VK_FORMAT_R16_SINT         : DXGI_FORMAT_R16_SINT;
            
            // Unsigned norm 16-bit
            case VK_FORMAT_R16G16B16A16_UNORM: DXGI_FORMAT_R16G16B16A16_UNORM;
            case VK_FORMAT_R16G16_UNORM      : DXGI_FORMAT_R16G16_UNORM;
            case VK_FORMAT_R16_UNORM         : DXGI_FORMAT_R16_UNORM;

            // Signed norm 16-bit
            case VK_FORMAT_R16G16B16A16_SNORM: DXGI_FORMAT_R16G16B16A16_SNORM;
            case VK_FORMAT_R16G16_SNORM      : DXGI_FORMAT_R16G16_SNORM;
            case VK_FORMAT_R16_SNORM         : DXGI_FORMAT_R16_SNORM;

            // Unsigned int 8-bit
            case VK_FORMAT_R8G8B8A8_UINT    : DXGI_FORMAT_R8G8B8A8_UINT;
            case VK_FORMAT_R8G8_UINT        : DXGI_FORMAT_R8G8_UINT;
            case VK_FORMAT_R8_UINT          : DXGI_FORMAT_R8_UINT;

            // Signed int 8-bit
            case VK_FORMAT_R8G8B8A8_SINT    : DXGI_FORMAT_R8G8B8A8_SINT;
            case VK_FORMAT_R8G8_SINT        : DXGI_FORMAT_R8G8_SINT;
            case VK_FORMAT_R8_SINT          : DXGI_FORMAT_R8_SINT;

            // Unsigned norm 8-bit
            case VK_FORMAT_R8G8B8A8_SRGB    : DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
            case VK_FORMAT_R8G8B8A8_UNORM   : DXGI_FORMAT_R8G8B8A8_UNORM;
            case VK_FORMAT_R8G8_UNORM       : DXGI_FORMAT_R8G8_UNORM;
            case VK_FORMAT_R8_UNORM         : DXGI_FORMAT_R8_UNORM;

            // Signed norm 8-bit
            case VK_FORMAT_R8G8B8A8_SNORM   : DXGI_FORMAT_R8G8B8A8_SNORM;
            case VK_FORMAT_R8G8_SNORM       : DXGI_FORMAT_R8G8_SNORM;
            case VK_FORMAT_R8_SNORM         : DXGI_FORMAT_R8_SNORM;
            
            // Depth and Stencil
            case VK_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D24_UNORM_S8_UINT;
            case VK_FORMAT_D32_SFLOAT_S8_UINT: DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
            case VK_FORMAT_D32_SFLOAT        : DXGI_FORMAT_D32_FLOAT;

            // Broken?
            case VK_FORMAT_A2R10G10B10_UINT_PACK32: DXGI_FORMAT_R10G10B10A2_UINT;
            case VK_FORMAT_A2R10G10B10_UNORM_PACK32: DXGI_FORMAT_R10G10B10A2_UNORM;
        };

        // Not Detected... 
        return DXGI_FORMAT_UNKNOWN;
    };

    D3D12_DESCRIPTOR_RANGE_TYPE convertDescriptorType(const VkDescriptorType& type) {
        switch (type) {
            case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT: return D3D12_DESCRIPTOR_RANGE_TYPE_CBV; break;
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER: return D3D12_DESCRIPTOR_RANGE_TYPE_CBV; break;
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER: return D3D12_DESCRIPTOR_RANGE_TYPE_UAV; break;
            case VK_DESCRIPTOR_TYPE_SAMPLER: return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER; break;
            case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER: return D3D12_DESCRIPTOR_RANGE_TYPE_SRV; break;
            case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER: return D3D12_DESCRIPTOR_RANGE_TYPE_SRV; break;
            case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE: return D3D12_DESCRIPTOR_RANGE_TYPE_SRV; break;
            case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE: return D3D12_DESCRIPTOR_RANGE_TYPE_UAV; break;
            case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER: return D3D12_DESCRIPTOR_RANGE_TYPE_UAV; break;
        };
        return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
    };
    
};
