#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdint.h>
#include "Config.hh"
#include "AbstractOffsetPtr.hh"
#include "Globals.hh"

int main(int argv, char* argc[]) {

	const uintptr_t phys = 0x5000; 
	const uintptr_t log = 0x5200;
	const size_t size = 20 * sizeof(int);
	
	const void* ptr = reinterpret_cast<const void*>(phys + (size-1));
	const void* ptr2 = reinterpret_cast<const void*>(phys+size+1);
	const void* ptr3 = reinterpret_cast<const void*>(log + size);
	
	std::cout<<"phys: "<<ptr<<std::endl;
	std::cout<<"size: "<<size<<std::endl;
	std::cout<<"log: "<<log<<std::endl;

	uint64_t physBase = ImageConfig::physBase();
	std::cout<<"physBase: "<<physBase<<std::endl;
	ImageConfig::setSize(size);	
	std::cout<<"size: "<<ImageConfig::size()<<std::endl;
	
	isEqual<int, double> eq;
	
	isEqual<int, int> hello;
	
	AbstractOffsetPtr<ImageConfig, int> off;
	bool val = off.isValidPhysAddress(ptr);
	std::cout<<"valid: "<<val<<std::endl;	
	
	bool val2 = off.isValidVirtAddress(ptr);
	std::cout<<"valid: "<<val2<<std::endl;	
	//AbstractOffsetPtr<KernelConfig, int> off2 = Globals<AbstractOffsetPtr, AbstractOffsetPtr>::convert(off);
	
}
