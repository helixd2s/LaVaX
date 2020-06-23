#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkImage_T.hpp"

namespace dxv {

    VkResult VkImage_T::Create(const dxv::VkDevice_T* device, HPTR(VkImageCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);


        return VK_SUCCESS;
    };

};
