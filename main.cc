#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdint.h>
#include "Config.hh"

int main(int argv, char* argc[]) {

	const uintptr_t phys = 0x50000; 
	const uintptr_t log = 0x40000;
	const size_t size = 20 * sizeof(int);
	
	const void* ptr = reinterpret_cast<const void*>(phys);
	const void* ptr2 = reinterpret_cast<const void*>(phys+size+1);
	const void* ptr3 = reinterpret_cast<const void*>(log + size);

	config::setPhys(phys);
	config::setVirt(log);
	config::setSize(size);
		

}
