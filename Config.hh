#pragma once
#include <cstddef>
#include <cstdint>

struct config_consts{
	uint64_t PHYS;
	size_t SIZE;
	uint64_t VIRT; 
};

config_consts off_config;
config_consts phys32_config;
config_consts phys64_config;

class config32phys {

public:

	static void setPhys(uint64_t phys) {
		off_config.PHYS = phys;
	}

	static void setVirt(uint64_t virt) {
		off_config.VIRT = virt;
	}

	static void setSize(size_t size) {
		off_config.SIZE = size;
	}
	
	static size_t getSize() {
		return off_config.SIZE;
	}

	static uint64_t getPhys() {
		return off_config.PHYS;
	}

	static uint64_t getVirt() { 
		return off_config.VIRT;
	}
};
class configOffset {
	
public:
	static void setPhys(uint64_t phys) {
		phys32_config.PHYS = phys;
	}

	static void setVirt(uint64_t virt) {
		phys32_config.VIRT = virt;
	}

	static void setSize(size_t size) {
		phys32_config.SIZE = size;
	}
	
	static size_t getSize() {
		return phys32_config.SIZE;
	}

	static uint64_t getPhys() {
		return phys32_config.PHYS;
	}

	static uint64_t getVirt() { 
		return phys32_config.VIRT;
	}
};

class config64phys {

public:

	static void setPhys(uint64_t phys) {
		phys64_config.PHYS = phys;
	}

	static void setVirt(uint64_t virt) {
		phys64_config.VIRT = virt;
	}

	static void setSize(size_t size) {
		phys64_config.SIZE = size;
	}
	
	static size_t getSize() {
		return phys64_config.SIZE;
	}

	static uint64_t getPhys() {
		return phys64_config.PHYS;
	}

	static uint64_t getVirt() { 
		return phys64_config.VIRT;
	}
}; 
