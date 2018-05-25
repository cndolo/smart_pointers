#include <cstddef>
#include <cstdint>

struct config_consts {
	uint64_t PHYS;
	size_t SIZE;
	uint64_t VIRT; 
} config_consts;

class config {

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

};
