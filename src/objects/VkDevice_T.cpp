#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkPhysicalDevice_T.hpp"
#include "VkDeviceMemory_T.hpp"

namespace lvx {

    VkResult VkDevice_T::Create(const lvx::VkPhysicalDevice_T* physicalDevice, HPTR(VkDeviceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks)
    {   // TODO: Measure Feature Level By Extensions
        if (!SUCCEEDED(D3D12CreateDevice( // Normal Mode
            physicalDevice->Get(),
            D3D_FEATURE_LEVEL_12_1,
            IID_PPV_ARGS(&device)
        ))) {
            ThrowIfFailed(D3D12CreateDevice( // Compatibility Mode
                physicalDevice->Get(),
                D3D_FEATURE_LEVEL_12_0,
                IID_PPV_ARGS(&device)
            ));
            std::cerr << "Enabled DirectX 12 Compatibility Mode" << std::endl;
        } else {
            std::cout << "Enabled DirectX 12 Normal Mode" << std::endl;
        };

        // TODO: VkResult Conversion
        return VK_SUCCESS;
    };

    VkResult VkDevice_T::AllocateMemory(const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
        auto deviceMemory = new VkDeviceMemory_T(this, pAllocateInfo, pAllocator);
        *pMemory = VkDeviceMemory(deviceMemory);
        return deviceMemory->Result();
    };

};
