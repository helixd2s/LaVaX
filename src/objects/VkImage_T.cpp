#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkImage_T.hpp"

namespace dvx {

    VkResult VkImage_T::Create(const dvx::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);


        return VK_SUCCESS;
    };

};
