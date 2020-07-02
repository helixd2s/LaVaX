#include <lvx/LaVaXulkan.hpp>

#include "pch/pch.h"
#include "objects/VkInstance_T.hpp"

#ifndef BUILD_EXPORTS
#define BUILD_EXPORTS
#endif

namespace lvx {

    // 
    BUILD_API VkResult vkCreateInstance(
        const VkInstanceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkInstance* pInstance
    )
    {   // TODO: use pAllocator for allocate that class...
        auto allocation = new VkInstance_T(pCreateInfo, *pAllocator);
        *pInstance = VkInstance(allocation);
        return VK_SUCCESS; // TODO: Result Info
    };

    // 
    BUILD_API VkResult vkEnumeratePhysicalDevices(
        VkInstance instance,
        uint32_t* pPhysicalDeviceCount,
        VkPhysicalDevice* pPhysicalDevices
    )
    {
        return reinterpret_cast<VkInstance_T*>(instance)->EnumeratePhysicalDevices(pPhysicalDeviceCount, pPhysicalDevices);
    };

};
