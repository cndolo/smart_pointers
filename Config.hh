#pragma once
#include <cstddef>
#include <cstdint>

struct ImageConfig{
	static uint64_t PHYS_BASE;
	static size_t SIZE;
	static uint64_t VIRT_BASE; 
	static uint64_t KERN_END;
	static uint64_t physBase() { return ImageConfig::PHYS_BASE; }
	static size_t size() { return ImageConfig::SIZE; }
	static uint64_t virtBase() { return ImageConfig::VIRT_BASE; }	

	static void setPhysBase(uint64_t phys) { ImageConfig::PHYS_BASE = phys; }
	static void setSize(size_t size) { ImageConfig::SIZE = size; }
	static void setVirtBase(uint64_t virt) { ImageConfig::VIRT_BASE = virt; }
};

struct MMIOConfig{
	static uint64_t PHYS_BASE;
	static size_t SIZE;
	static uint64_t VIRT_BASE; 
	
	static uint64_t physBase() { return MMIOConfig::PHYS_BASE; }
	static size_t size() { return MMIOConfig::SIZE; }
	static uint64_t virtBase() { return MMIOConfig::VIRT_BASE; }

	static void setPhysBase(uint64_t phys) { PHYS_BASE = phys; }
	static void setSize(size_t size) { SIZE = size; }
	static void setVirtBase(uint64_t virt) { VIRT_BASE = virt; }
};
struct KernelConfig{
	static uint64_t PHYS_BASE;
	static size_t SIZE;
	static uint64_t VIRT_BASE; 
	
	static uint64_t physBase() { return KernelConfig::PHYS_BASE; }
	static size_t size() { return KernelConfig::SIZE; }
	static uint64_t virtBase() { return KernelConfig::VIRT_BASE; }

	static void setPhysBase(uint64_t phys) { PHYS_BASE = phys; }
	static void setSize(size_t size) { SIZE = size; }
	static void setVirtBase(uint64_t virt) { VIRT_BASE = virt ;}
};


