#include "pch/pch.h"
#include "VkInstance_T.hpp"
#include "VkPhysicalDevice_T.hpp"

namespace dxv {

    VkPhysicalDevice_T::VkPhysicalDevice_T(const dxv::VkInstance_T* instance, ComPtr<IDXGIAdapter1> adapter) : instance(VkInstance(instance)), adapter(adapter) {};

};
