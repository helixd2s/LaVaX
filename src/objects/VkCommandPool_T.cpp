#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkCommandPool_T.hpp"

namespace dxv {

    VkResult VkCommandPool_T::Create(const dxv::VkDevice_T* device, HPTR(VkCommandPoolCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // 
        return VK_SUCCESS;
    };

};
