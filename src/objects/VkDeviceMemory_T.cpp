#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkPhysicalDevice_T.hpp"
#include "VkDeviceMemory_T.hpp"

namespace lvx {

    VkResult VkDeviceMemory_T::Create(const lvx::VkDevice_T* device, const VkMemoryAllocateInfo* allocateInfo, const VkAllocationCallbacks* callbacks) {
        // TODO: Memory Heap Properties...
        D3D12_HEAP_PROPERTIES properties = {};
        
        // 
        D3D12_HEAP_DESC HeapDesc = { allocateInfo->allocationSize, properties, D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT, D3D12_HEAP_FLAG_NONE };
        ThrowIfFailed(device->GetDevice()->CreateHeap(&HeapDesc, IID_PPV_ARGS(&memoryHeap)));

        // 
        D3D12_HEAP_DESC HeapDesc = {};
        VkPhysicalDevice_T* pGPU = reinterpret_cast<VkPhysicalDevice_T*>(device->PhysicalDevice());
        HeapDesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
        //HeapDesc.Flags = ; // TODO: SUPPORT FOR `VkMemoryAllocateFlagsInfo`
        HeapDesc.Properties = pGPU->heapType[allocateInfo->memoryTypeIndex];
        HeapDesc.SizeInBytes = allocateInfo->allocationSize;

        // 
        ThrowIfFailed(device->GetDevice()->CreateHeap(&HeapDesc, IID_PPV_ARGS(&memoryHeap)));

        // 
        return VK_SUCCESS;
    };

};
