#include "pch.h"
#include "framework.h"

#include "objects/VkDevice_T.hpp"
#include "objects/VkPhysicalDevice_T.hpp"

// Provided by VK_VERSION_1_0
VkResult vkCreateDevice(
    VkPhysicalDevice                physicalDevice,
    const VkDeviceCreateInfo*       pCreateInfo,
    const VkAllocationCallbacks*    pAllocator,
    VkDevice*                       pDevice
)
{   
    // TODO: use pAllocator for allocate that class...
    auto allocation = new dxv::VkDevice_T(reinterpret_cast<dxv::VkPhysicalDevice_T*>(physicalDevice), *pCreateInfo);
    *pDevice = VkDevice(allocation);
    return VK_SUCCESS; // TODO: Result Info
};
