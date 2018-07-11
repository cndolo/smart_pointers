#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdint.h>

#include "Config.hh"
#include "Globals.hh"

#include "AbstractOffsetPtr32.hh"
#include "AbstractPhysPtr32.hh"
#include "AbstractPhysPtr64.hh"

#include "ImageOffsetPtr32.hh"
#include "KernelPhysPtr32.hh"
#include "MMIOPhysPtr64.hh"

int main(int argv, char* argc[]) {

	const uintptr_t phys = 0x5000; 
	const uintptr_t log = 0x5200;
	const size_t size = 20 * sizeof(int);
	
	uintptr_t ptr = uintptr_t(phys + (size-1));
	uintptr_t ptr2 = uintptr_t(phys+size+1);
	uintptr_t ptr3 = uintptr_t(log + (size-1));
	
	std::cout<<"phys: "<<ptr<<std::endl;
	std::cout<<"size: "<<size<<std::endl;
	std::cout<<"log: "<<log<<std::endl;
	
	/*
	 * CONFIGS
	 */

	uint64_t physBase = ImageConfig::physBase();
	std::cout<<"physBase: "<<physBase<<std::endl;
	
	ImageConfig::setPhysBase(phys);
	physBase = ImageConfig::physBase();
	std::cout<<"new physBase: "<<physBase<<std::endl;
	
	ImageConfig::setVirtBase(log);
	std::cout<<"new virtBase: "<<ImageConfig::virtBase()<<std::endl;

	ImageConfig::setSize(size);	
	std::cout<<"size: "<<ImageConfig::size()<<std::endl;
	
	isEqual<int, double> eq;
	
	isEqual<int, int> hello;
	
	/*
	 * 32-BIT OFFSET PTR
	 *
	 */

	std::cout<<"-------- 32 BIT OFFSET ------"<<std::endl;

	AbstractOffsetPtr32<ImageConfig, int> off;
	ImageOffsetPtr32<int>* image = new ImageOffsetPtr32<int>();

	uint64_t i_ptr = (uint64_t) (ptr + 1);

	ImageOffsetPtr32<int>* image2 = new ImageOffsetPtr32<int>(i_ptr);

	bool val = image->isValidPhysAddress(ptr);
	std::cout<<ptr<<" valid: "<<val<<std::endl;	
	
	bool val2 = image->isValidPhysAddress(ptr2);
	std::cout<<ptr2<<" valid: "<<val2<<std::endl;	
	
	bool val3 = image->isValidVirtAddress(ptr);
	std::cout<<ptr<<" valid: "<<val3<<std::endl;	
	
	bool val4 = image->isValidVirtAddress(ptr3);
	std::cout<<ptr3<<" valid: "<<val4<<std::endl;	
	
	auto off2 = convert<AbstractOffsetPtr32<ImageConfig, int>>(off);

	//auto off3 = convert<ImageOffsetPtr32<>>(off);	
	
	bool value = image->isValidVirtAddress(ptr);
	std::cout<<value<<std::endl;

	bool mem = image->mem();
	std::cout<<mem<<std::endl;

	bool can = image->canonical();

	auto log_im = image->log();
	
	/*
	 * 32-BIT PHYS PTR
	 *
	 */

	std::cout<<"------- 32 BIT PHYS -------"<<std::endl;
	

	AbstractPhysPtr32<KernelConfig, int> phys32;	
	KernelPhysPtr32<int>* kernel = new KernelPhysPtr32<int>();	
	
	std::cout<<"physBase: "<<KernelConfig::physBase()<<std::endl;
	uintptr_t k_phys = phys + phys;
	KernelConfig::setPhysBase(k_phys);
	std::cout<<"new physBase: "<<KernelConfig::physBase()<<std::endl;
	
	uintptr_t k_virt = log + log;
	KernelConfig::setVirtBase(k_virt);
	std::cout<<"new virtBase: "<<KernelConfig::virtBase()<<std::endl;

	size_t k_size = (size-1)*2;
	KernelConfig::setSize(k_size);	
	std::cout<<"size: "<<KernelConfig::size()<<std::endl;
	
	uintptr_t ptr4 = k_phys + k_phys;
   	uintptr_t ptr5 = k_phys + size;	
	uintptr_t ptr6 = k_virt + 1;
	
	bool val5 = kernel->isValidPhysAddress(ptr4);
	std::cout<<ptr4<<" valid: "<<val5<<std::endl;	
	
	bool val6 = kernel->isValidPhysAddress(ptr5);
	std::cout<<ptr5<<" valid: "<<val6<<std::endl;	

	bool val7 = kernel->isValidVirtAddress(ptr6);
	std::cout<<ptr6<<" valid: "<<val7<<std::endl;

	bool val8 = kernel->isValidVirtAddress(ptr6 + k_size);
	std::cout<<ptr6 + k_size<<" valid: "<<val5<<std::endl;	

	bool k_mem = kernel->mem();
	std::cout<<k_mem<<std::endl;

	bool k_can = kernel->canonical();
	std::cout<<k_can<<std::endl;

	/*
	 *	SEGMENTATION FAULT
	 */
	auto k_log = kernel->log();

	
	std::cout<<"-------- 64 BIT PHYS --------"<<std::endl;

	std::cout<<"physBase: "<<MMIOConfig::physBase()<<std::endl;
	uintptr_t m_phys = phys + phys + 1;
	MMIOConfig::setPhysBase(m_phys);
	std::cout<<"new physBase: "<<MMIOConfig::physBase()<<std::endl;
	
	uintptr_t m_virt = log + log + 1;
	MMIOConfig::setVirtBase(m_virt);
	std::cout<<"new virtBase: "<<MMIOConfig::virtBase()<<std::endl;

	size_t m_size = (size-1)*2;
	MMIOConfig::setSize(m_size);	
	std::cout<<"size: "<<MMIOConfig::size()<<std::endl;
	
	MMIOPhysPtr64<int>* mmio = new MMIOPhysPtr64<int>();

	std::cout<<"ptr: "<<ptr<<std::endl;

	auto from_phys = MMIOPhysPtr64<int>::fromPhys(ptr);
	std::cout<<"ptr: "<<mmio->getPtr()<<std::endl;
	
	auto fromVirt = MMIOPhysPtr64<int>::fromVirt(&from_phys);
	uintptr_t phys_int = fromVirt->physint();	

	uint64_t m_ptr = (uint64_t) ptr;

	MMIOPhysPtr64<int>* mmio2 = new MMIOPhysPtr64<int>(m_ptr);
	
	std::cout<<"ptr: "<<mmio2->getPtr()<<std::endl;
	
	uintptr_t ptr7 = m_phys + m_phys;
   	uintptr_t ptr8 = m_phys + size;	
	uintptr_t ptr9 = m_virt + 1;

	bool val9 = mmio->isValidPhysAddress(ptr7);
	std::cout<<ptr7<<" valid: "<<val9<<std::endl;

	bool val10 = mmio->isValidPhysAddress(ptr8);
	std::cout<<ptr8<<" valid: "<<val10<<std::endl;

	bool val11 = mmio->isValidVirtAddress(ptr9);
	std::cout<<ptr9<<" valid: "<<val11<<std::endl;

	ptr9 = mmio->physint();
	val9 = mmio->isValidPhysAddress(ptr9);
	std::cout<<ptr9<<" valid: "<<val9<<std::endl;

	auto new_abs = MMIOPhysPtr64<int>::fromPhys(ptr9);
	std::cout<<"ptr 9: "<<ptr9<<std::endl;
	ptr9 = mmio->physint();
	std::cout<<"ptr 9: "<<ptr9<<std::endl;

	bool m_mem = mmio->mem();
	std::cout<<m_mem<<std::endl;

	bool m_can = mmio->canonical();
	std::cout<<m_can<<std::endl;

	auto m_from_p = MMIOPhysPtr64<int>::fromPhys(mmio);
	auto m_from_v = MMIOPhysPtr64<int>::fromVirt(mmio);

	auto test = MMIOPhysPtr64<int>::fromPhys(ptr7);

}

