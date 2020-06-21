#include "pch.h"
#include "VkDevice_T.hpp"
#include "VkPhysicalDevice_T.hpp"

namespace dxv {

	VkDevice_T::VkDevice_T(const dxv::VkPhysicalDevice_T* physicalDevice, const VkDeviceCreateInfo& createInfo, const VkAllocationCallbacks& callbacks) {

        // TODO: Measure Feature Level By Extensions
        ThrowIfFailed(D3D12CreateDevice(
            physicalDevice->Get(),
            D3D_FEATURE_LEVEL_12_1,
            IID_PPV_ARGS(&device)
        )); // TODO: VkResult Conversion
	}

};
