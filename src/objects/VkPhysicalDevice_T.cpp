#include "pch/pch.h"
#include "VkInstance_T.hpp"
#include "VkPhysicalDevice_T.hpp"

namespace lvx {

    class PropertyMaker { protected: 
        VkPhysicalDeviceMemoryProperties properties = {};
        uint32_t heapIndex = 0, heapCount = 0;
        uint32_t typeIndex = 0, typeCount = 0;

        // 
        public: PropertyMaker(){
            
        };

        void setProperties(VkPhysicalDeviceMemoryProperties* output) {
            *output = properties;
        };

        PropertyMaker& addHeap(VkMemoryHeap heap) {
            properties.memoryHeaps[heapIndex = heapCount++] = heap;
            properties.memoryHeapCount = heapCount;
            return *this;
        };

        PropertyMaker& addType(VkMemoryPropertyFlags propertyFlags) {
            properties.memoryTypes[typeIndex = typeCount++].heapIndex = heapIndex;
            properties.memoryTypes[typeIndex].propertyFlags = propertyFlags;
            properties.memoryTypeCount = typeCount;
            return *this;
        };
    };

    // 
    VkPhysicalDevice_T::VkPhysicalDevice_T(const lvx::VkInstance_T* instance, ComPtr<IDXGIAdapter1> adapter, ComPtr<ID3D12Device> device) : instance(VkInstance(instance)), adapter(adapter), device(device) {
    };
    
    // 
    const std::array<D3D12_HEAP_TYPE, 4u> heapTypes = {D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_TYPE_READBACK, D3D12_HEAP_TYPE_CUSTOM};
    void VkPhysicalDevice_T::GetPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
        PropertyMaker maker{};
        
        // 
        uint32_t i = 0u;
        for (auto& type : heapTypes) {   // 
            VkMemoryPropertyFlags flags = {};
            auto& properties = (heapType[i++] = device->GetCustomHeapProperties(nodeMask, type));
            
            // 
            if (properties.MemoryPoolPreference == D3D12_MEMORY_POOL_L1) { 
                flags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT; 
            };
            if (properties.CPUPageProperty == D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE) {
                flags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
            };
            if (properties.CPUPageProperty == D3D12_CPU_PAGE_PROPERTY_WRITE_BACK) {
                flags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
            };
            
            // TODO: Getting Heap Memory Size
            maker.addHeap(VkMemoryHeap{ .size = 1024 * 1024 * 1024 * 8u, .flags = 
                (properties.MemoryPoolPreference==D3D12_MEMORY_POOL_L1?VK_MEMORY_HEAP_DEVICE_LOCAL_BIT:0u) 
            }).addType(flags);
        };

        // 
        maker.setProperties(pMemoryProperties);
    };

};
