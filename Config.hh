#pragma once
#include <cstddef>
#include <cstdint>

struct ImageConfig{
	
	static uint64_t PHYS_BASE;
	static size_t SIZE;
	static uint64_t VIRT_BASE; 

	static uint64_t physBase() { return PHYS_BASE; }
	static size_t size() { return SIZE; }
	static uint64_t virtBase() { return VIRT_BASE; }

	static void setPhysBase(uint64_t phys) { PHYS_BASE =phys; }
	static void setSize(size_t size) { SIZE =size; }
	static void setVirtBase(uint64_t virt) { VIRT_BASE =virt; }
};

struct KernelConfig{
	
	static uint64_t PHYS_BASE;
	static size_t SIZE;
	static uint64_t VIRT_BASE; 

	static uint64_t physBase() { return PHYS_BASE; }
	static size_t size() { return SIZE; }
	static uint64_t virtBase() { return VIRT_BASE; }

	static void setPhysBase(uint64_t phys) { PHYS_BASE =phys; }
	static void setSize(size_t size) { SIZE =size; }
	static void setVirtBase(uint64_t virt) { VIRT_BASE =virt ;}
};

struct MMIOConfig{
	
	static uint64_t PHYS_BASE;
	static size_t SIZE;
	static uint64_t VIRT_BASE; 

	static uint64_t physBase() { return PHYS_BASE; }
	static size_t size() { return SIZE; }
	static uint64_t virtBase() { return VIRT_BASE; }

	static void setPhysBase(uint64_t phys) { PHYS_BASE =phys; }
	static void setSize(size_t size) { SIZE =size; }
	static void setVirtBase(uint64_t virt) { VIRT_BASE =virt; }
};



