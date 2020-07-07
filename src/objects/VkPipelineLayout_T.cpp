#include "pch/pch.h"
#include "VkPipelineLayout_T.hpp"
#include "VkDescriptorSetLayout_T.hpp"


namespace lvx {

    VkResult VkDescriptorSetLayout_T::Create(const lvx::VkDevice_T* device, HPTR(VkPipelineLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        std::vector<CD3DX12_ROOT_PARAMETER1> parameters = {};
        for (uint32_t i=0;i<createInfo->setLayoutCount;i++) {
            parameters.push_back(reinterpret_cast<VkDescriptorSetLayout*>(createInfo->pSetLayouts[i])->GetRootParameters());
        };

        // TODO: samplers support
        rootSignatureDesc.Init_1_1(rootParameters.size(), rootParameters.data(), 0u, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

        // 
        ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_1, &signature, &error));
        ThrowIfFailed(device->GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&signature)));

        // TODO: Corrent Result
        return VK_SUCCESS;
    };

};
