#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkDescriptorSetLayout_T.hpp"
#include "VkPipelineLayout_T.hpp"

namespace lvx {

    VkResult VkPipelineLayout_T::Create(const lvx::VkDevice_T* device, HPTR(VkPipelineLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        std::vector<CD3DX12_ROOT_PARAMETER1> rootParameters = {};
        for (uint32_t i=0;i<createInfo->setLayoutCount;i++) {
            rootParameters.push_back(reinterpret_cast<VkDescriptorSetLayout_T*>(createInfo->pSetLayouts[i])->GetRootParameters());
        };

        // TODO: samplers support
        rootSignatureDesc.Init_1_1(rootParameters.size(), rootParameters.data(), 0u, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

        // 
        ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_1, &signature, &error));
        ThrowIfFailed(device->GetDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)));

        // TODO: Corrent Result
        return VK_SUCCESS;
    };

};
