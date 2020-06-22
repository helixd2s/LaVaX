#include "pch.h"
#include "VkInstance_T.hpp"
#include "VkPhysicalDevice_T.hpp"

namespace dxv {

    // 
    VkInstance_T::VkInstance_T(HPTR(VkInstanceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) pAllocator)
    {
        UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
        // Enable the debug layer (requires the Graphics Tools "optional feature").
        // NOTE: Enabling the debug layer after device creation will invalidate the active device.
        {
            ComPtr<ID3D12Debug> debugController;
            if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
            {
                debugController->EnableDebugLayer();

                // Enable additional debug layers.
                dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
            }
        }
#endif

        ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&this->factory))); // TODO: VkResult Conversion
    };

    // 
    VkResult VkInstance_T::EnumeratePhysicalDevices(uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) 
    {
        if (this->devices.size() <= 0) {
            ComPtr<IDXGIAdapter1> adapter = {};
            for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != this->factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex)
            {
                DXGI_ADAPTER_DESC1 desc;
                adapter->GetDesc1(&desc);

                // Look Only for D3D12 Devices
                if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE || !SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, _uuidof(ID3D12Device), nullptr))) { continue; }
                this->devices.push_back(VkPhysicalDevice(new dxv::VkPhysicalDevice_T(this, adapter)));
            }
        };

        if (pPhysicalDeviceCount) {
            *pPhysicalDeviceCount = uint32_t(this->devices.size());
        };

        if (pPhysicalDevices) {
            memcpy(pPhysicalDevices, this->devices.data(), this->devices.size() * sizeof(VkPhysicalDevice));
        };

        return VK_SUCCESS; // TODO: Corrent Result
    };

};
