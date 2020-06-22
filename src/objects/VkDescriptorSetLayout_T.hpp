#pragma once

//#include <vector>
#include "pch.h"
#include "generals/objects.hpp"

// 
namespace dxv {

    class VkDescriptorSetLayout_T {
	protected:
		CD3DX12_ROOT_PARAMETER1 rootParameters = {};
		std::vector<CD3DX12_DESCRIPTOR_RANGE1> ranges = {};
		std::vector<uint32_t> offsets = {};
		size_t fullRange = 0u;
	public:
		VkDescriptorSetLayout_T() {}
		VkDescriptorSetLayout_T(const dxv::VkPhysicalDevice_T* device, HPTR(VkDescriptorSetLayoutCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

		
		size_t getDescriptorCount() const { return this->ranges.size(); }
		size_t getFullRange() const { return this->fullRange; };
		std::vector<uint32_t> getOffsets() const { return this->offsets; };
	};

};
