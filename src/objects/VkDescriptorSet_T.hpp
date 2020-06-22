#pragma once

#include "pch.h"
#include "generals/objects.hpp"

// 
namespace dxv {

	class VkDescriptorSet_T {
	protected:
		ComPtr<ID3D12DescriptorHeap> heap = {};
		std::vector<uintptr_t> offsets = {};
		size_t fullRange = 0u;
	public:
		VkDescriptorSet_T() {}
		VkDescriptorSet_T(const dxv::VkDevice_T* device, const dxv::VkDescriptorPool_T* descriptorPool, const dxv::VkDescriptorSetLayout_T* descriptorSetLayout, UPTR(VkAllocationCallbacks) callbacks);

	};

};
