#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkFramebuffer_T.hpp"

namespace dxv {

    VkResult VkFramebuffer_T::Create(const dxv::VkDevice_T* device, HPTR(VkFramebufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        

        return VK_SUCCESS;
    };

};
