#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkImageView_T.hpp"

namespace dxv {

    VkResult VkImageView_T::Create(const dxv::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // Describe and create a SRV for the texture.
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        //srvDesc.Format = textureDesc.Format; // TODO: Format
        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;

        // TODO: Correct Image View
        //device->GetDevice()->CreateShaderResourceView(createInfo->image, &srvDesc, m_srvHeap->GetCPUDescriptorHandleForHeapStart());

        return VK_SUCCESS;
    };

};
