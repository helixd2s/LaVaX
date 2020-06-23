#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    class VkBufferView_T {
    protected:
        ComPtr<ID3D12DescriptorHeap> heap = {};
        VkBufferViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;

    public:
        VkBufferView_T() {}
        VkBufferView_T(const dxv::VkDevice_T* device, HPTR(VkBufferViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const dxv::VkDevice_T* device, HPTR(VkBufferViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

        // 
        ComPtr<ID3D12DescriptorHeap>& Heap() { return this->heap; };
        const ComPtr<ID3D12DescriptorHeap>& Heap() const { return this->heap; };

        //
        D3D12_CPU_DESCRIPTOR_HANDLE Handle() const { return this->heap->GetCPUDescriptorHandleForHeapStart(); };

        // 
        ID3D12DescriptorHeap* Get() const { return heap.Get(); };
    };

};
