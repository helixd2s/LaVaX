#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkCommandBuffer_T.hpp"
#include "VkCommandPool_T.hpp"

namespace lvx {

    VkResult VkCommandBuffer_T::Create(const lvx::VkDevice_T* device, const HPTR(VkCommandBufferAllocateInfo) createInfo) {
        // Create the command list.
        this->device = VkDevice(device);

        // TODO: Secondary command list support (i.e. Bundle)
        // TODO: PipelineState support
        ThrowIfFailed(device->GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, reinterpret_cast<VkCommandPool_T*>(createInfo->commandPool)->Get(), nullptr, IID_PPV_ARGS(&commandList)));

        // 
        return VK_SUCCESS;
    };

};
