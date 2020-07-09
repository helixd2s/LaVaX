#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkImageView_T.hpp"
#include "VkImage_T.hpp"

namespace lvx {

    VkResult VkImageView_T::Create(const lvx::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) 
    {
        // Needs to copy into main heaps (i.e. as DirectX 12 Version)
        D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
        srvHeapDesc.NumDescriptors = 1u;
        srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        // TODO: Return Result 
        ThrowIfFailed(device->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&this->heap)));
        return this->Create(device, *createInfo, *callbacks, this->heap->GetCPUDescriptorHandleForHeapStart());
    }

    VkResult VkImageView_T::Create(const lvx::VkDevice_T* device, const D3D12_CPU_DESCRIPTOR_HANDLE& Handle) {
        return this->Create(device, this->createInfo, this->callbacks, Handle);
    };

    VkResult VkImageView_T::Create(const lvx::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks, const D3D12_CPU_DESCRIPTOR_HANDLE& Handle) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);
        this->callbacks = const_cast<vkt::uni_arg<VkAllocationCallbacks>&>(callbacks);
        
        // Describe and create a SRV for the texture.
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = convertFormat(createInfo->format);
        srvDesc.ViewDimension = convertDimension(createInfo->viewType);

        // 
        if (srvDesc.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE1D) {
            srvDesc.Texture1D.MipLevels = createInfo->subresourceRange.levelCount;
            srvDesc.Texture1D.MostDetailedMip = createInfo->subresourceRange.baseMipLevel;
        };
        
        // 
        if (srvDesc.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE2D) {
            srvDesc.Texture2D.MipLevels = createInfo->subresourceRange.levelCount;
            srvDesc.Texture2D.MostDetailedMip = createInfo->subresourceRange.baseMipLevel;
        };

        // 
        if (srvDesc.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE3D) {
            srvDesc.Texture3D.MipLevels = createInfo->subresourceRange.levelCount;
            srvDesc.Texture3D.MostDetailedMip = createInfo->subresourceRange.baseMipLevel;
        };

        // 
        if (srvDesc.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE1DARRAY) {
            srvDesc.Texture1DArray.MipLevels = createInfo->subresourceRange.levelCount;
            srvDesc.Texture1DArray.ArraySize = createInfo->subresourceRange.layerCount;
            srvDesc.Texture1DArray.MostDetailedMip = createInfo->subresourceRange.baseMipLevel;
            srvDesc.Texture1DArray.FirstArraySlice = createInfo->subresourceRange.baseArrayLayer;
        };

        // 
        if (srvDesc.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE2DARRAY) {
            srvDesc.Texture2DArray.MipLevels = createInfo->subresourceRange.levelCount;
            srvDesc.Texture2DArray.ArraySize = createInfo->subresourceRange.layerCount;
            srvDesc.Texture2DArray.MostDetailedMip = createInfo->subresourceRange.baseMipLevel;
            srvDesc.Texture2DArray.FirstArraySlice = createInfo->subresourceRange.baseArrayLayer;
        };

        // 
        if (srvDesc.ViewDimension == D3D12_SRV_DIMENSION_TEXTURECUBE) {
            srvDesc.TextureCube.MipLevels = createInfo->subresourceRange.levelCount;
            srvDesc.TextureCube.MostDetailedMip = createInfo->subresourceRange.baseMipLevel;
        };

        // 
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc.Shader4ComponentMapping = D3D12_ENCODE_SHADER_4_COMPONENT_MAPPING(
            component(createInfo->components.r, D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_0),
            component(createInfo->components.g, D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_1),
            component(createInfo->components.b, D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_2),
            component(createInfo->components.a, D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_3)
        );

        // 
        device->GetDevice()->CreateShaderResourceView((this->resource = reinterpret_cast<VkImage_T*>(createInfo->image)->GetResource()).Get(), &srvDesc, Handle);
        
        // 
        return VK_SUCCESS; // TODO: Return Result 
    };

};
