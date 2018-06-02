#pragma once
#include <cstddef>
#include <cstdint>

struct config_consts {
	uint64_t PHYS;
	size_t SIZE;
	uint64_t VIRT; 
} config_consts;

class config32phys {

public:

	static void setPhys(uint64_t phys) {
		config_consts.PHYS = phys;
	}

	static void setVirt(uint64_t virt) {
		config_consts.VIRT = virt;
	}

	static void setSize(size_t size) {
		config_consts.SIZE = size;
	}
	
	static size_t getSize() {
		return config_consts.SIZE;
	}

	static uint64_t getPhys() {
		return config_consts.PHYS;
	}

	static uint64_t getVirt() { 
		return config_consts.VIRT;
	}
};
class configOffset {
	
public:
	static void setPhys(uint64_t phys) {
		config_consts.PHYS = phys;
	}

	static void setVirt(uint64_t virt) {
		config_consts.VIRT = virt;
	}

	static void setSize(size_t size) {
		config_consts.SIZE = size;
	}
	
	static size_t getSize() {
		return config_consts.SIZE;
	}

	static uint64_t getPhys() {
		return config_consts.PHYS;
	}

	static uint64_t getVirt() { 
		return config_consts.VIRT;
	}
};

class config64phys {

public:

	static void setPhys(uint64_t phys) {
		config_consts.PHYS = phys;
	}

	static void setVirt(uint64_t virt) {
		config_consts.VIRT = virt;
	}

	static void setSize(size_t size) {
		config_consts.SIZE = size;
	}
	
	static size_t getSize() {
		return config_consts.SIZE;
	}

	static uint64_t getPhys() {
		return config_consts.PHYS;
	}

	static uint64_t getVirt() { 
		return config_consts.VIRT;
	}
}; 
