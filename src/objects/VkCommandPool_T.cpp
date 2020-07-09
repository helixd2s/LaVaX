#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkCommandPool_T.hpp"

namespace lvx {

    VkResult VkCommandPool_T::Create(const lvx::VkDevice_T* device, HPTR(VkCommandPoolCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // TODO: Correct `queueFamilyIndex` Support
        // TODO: Secondary command list support (i.e. Bundle)
        ThrowIfFailed(device->GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)));

        // 
        return VK_SUCCESS;
    };

};
