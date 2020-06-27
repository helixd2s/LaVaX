#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkCommandPool_T.hpp"

namespace dvx {

    VkResult VkCommandPool_T::Create(const dvx::VkDevice_T* device, HPTR(VkCommandPoolCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        // 
        return VK_SUCCESS;
    };

};
