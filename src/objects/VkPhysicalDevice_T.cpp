#include "pch/pch.h"
#include "VkInstance_T.hpp"
#include "VkPhysicalDevice_T.hpp"

namespace dvx {

    VkPhysicalDevice_T::VkPhysicalDevice_T(const dvx::VkInstance_T* instance, ComPtr<IDXGIAdapter1> adapter) : instance(VkInstance(instance)), adapter(adapter) {};

};
