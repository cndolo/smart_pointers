/* -*- mode:C++; -*- */
/* MIT License -- MyThOS: The Many-Threads Operating System
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright 2014 Randolf Rotta, Maik Krüger, and contributors, BTU Cottbus-Senftenberg
 */
#pragma once

#include "boot/memory-layout.h"
#include "util/compiler.hh"
#include "util/assert.hh"
#include <cstddef> // for size_t
#include <cstdint>

namespace mythos {

  extern char KERN_END SYMBOL("KERN_END");

  inline bool isKernelAddress(const void* ptr)
  {
    auto p = reinterpret_cast<uintptr_t>(ptr);
    return (p >= KERNELMEM_ADDR) && (p < KERNELMEM_ADDR + KERNELMEM_SIZE);
  }

  inline bool isImageAddress(const void* ptr)
  {
    auto p = reinterpret_cast<uintptr_t>(ptr);
    return (p >= VIRT_ADDR) && (p < VIRT_ADDR + uintptr_t(&KERN_END));
  }

  template<typename T>
  class PACKED LegacyPtr
  {
  public:
    LegacyPtr() : ptr(0) {}

    explicit LegacyPtr(uint64_t ptr) : ptr(ptr) {}

    static LegacyPtr fromImage(T* vp) {
      ASSERT(isImageAddress(vp));
      return LegacyPtr(reinterpret_cast<uintptr_t>(vp) - VIRT_ADDR);
    }

    static LegacyPtr fromKernel(T* vp) {
      ASSERT(isKernelAddress(vp));
      return LegacyPtr(reinterpret_cast<uintptr_t>(vp) - KERNELMEM_ADDR);
    }

    static LegacyPtr fromPhys(T* ptr) {
      return LegacyPtr(reinterpret_cast<uintptr_t>(ptr));
    }

    explicit operator bool() const { return ptr != 0; }
    bool operator==(LegacyPtr rhs) const { return ptr == rhs.ptr; }
    bool operator!=(LegacyPtr rhs) const { return ptr != rhs.ptr; }
    bool operator<(LegacyPtr rhs) const { return ptr < rhs.ptr; }
    bool operator<=(LegacyPtr rhs) const { return ptr <= rhs.ptr; }
    bool operator>=(LegacyPtr rhs) const { return ptr >= rhs.ptr; }
    bool operator>(LegacyPtr rhs) const { return ptr > rhs.ptr; }

    LegacyPtr& operator+=(size_t inc) { ptr += sizeof(T)*inc; return *this; }
    LegacyPtr operator+(size_t inc) const { return LegacyPtr(ptr+sizeof(T)*inc); }
    LegacyPtr& incbytes(size_t inc) { ptr += inc; return *this; }
    LegacyPtr plusbytes(size_t inc) const { return LegacyPtr(ptr+inc); }

    LegacyPtr& operator-=(size_t inc) { ptr -= sizeof(T)*inc; return *this; }
    LegacyPtr operator-(size_t inc) const { return LegacyPtr(ptr-sizeof(T)*inc); }
    size_t operator-(LegacyPtr rhs) const { return (ptr-rhs)/sizeof(T); }

    LegacyPtr& operator=(LegacyPtr rhs) { ptr = rhs.ptr; return *this; }

    uintptr_t physint() const { return ptr; }

    uintptr_t logint() const {
      ASSERT(kernelmem());
      return ptr + KERNELMEM_ADDR;
    }

    bool kernelmem() const { return ptr < KERNELMEM_SIZE; }

    bool canonical() const
    {
      static constexpr uintptr_t CANONICAL_MASK = ((1ull << (64 - 48))-1) << 48;
      return (ptr & CANONICAL_MASK) == 0 || (ptr & CANONICAL_MASK) == CANONICAL_MASK;
    }

    T* log() const { return reinterpret_cast<T*>(logint()); }
    T* operator->() const { return log(); }

  protected:
    uintptr_t ptr;
  };

  template<class T>
  LegacyPtr<T> physPtr(T* ptr) { return LegacyPtr<T>::fromPhys(ptr); }

  template<class T>
  LegacyPtr<T> physPtrFromImage(T* ptr) { return LegacyPtr<T>::fromImage(ptr); }

  template<class T>
  LegacyPtr<T> physPtrFromKernel(T* ptr) { return LegacyPtr<T>::fromKernel(ptr); }


  template<class T>
  T& operator*(LegacyPtr<T> ptr) { return *ptr.log(); }

  template<typename T>
  class PACKED LegacyPtr32
  {
  public:
    LegacyPtr32() : ptr(0) {}
    explicit LegacyPtr32(uint32_t ptr) : ptr(ptr) {}
    explicit LegacyPtr32(uint64_t ptr) : ptr(uint32_t(ptr)) {
      ASSERT(ptr <= 0xFFFFFFFF);
    }

    explicit operator bool() const { return ptr != 0; }
    bool operator==(LegacyPtr32 rhs) const { return ptr == rhs.ptr; }
    bool operator!=(LegacyPtr32 rhs) const { return ptr != rhs.ptr; }
    bool operator<(LegacyPtr32 rhs) const { return ptr < rhs.ptr; }
    bool operator<=(LegacyPtr32 rhs) const { return ptr <= rhs.ptr; }
    bool operator>=(LegacyPtr32 rhs) const { return ptr >= rhs.ptr; }
    bool operator>(LegacyPtr32 rhs) const { return ptr > rhs.ptr; }

    LegacyPtr32& operator+=(size_t inc) { ptr += sizeof(T)*inc; return *this; }
    LegacyPtr32 operator+(size_t inc) const { return LegacyPtr32(ptr+sizeof(T)*inc); }
    LegacyPtr32& incbytes(size_t inc) { ptr += inc; return *this; }
    LegacyPtr32 plusbytes(size_t inc) const { return LegacyPtr32(ptr+inc); }

    LegacyPtr32& operator-=(size_t inc) { ptr -= sizeof(T)*inc; return *this; }
    LegacyPtr32 operator-(size_t inc) const { return LegacyPtr32(ptr-sizeof(T)*inc); }
    size_t operator-(LegacyPtr32 rhs) const { return (ptr-rhs)/sizeof(T); }

    LegacyPtr32& operator=(LegacyPtr32 rhs) { ptr = rhs.ptr; return *this; }

    void* phys() const { return reinterpret_cast<void*>(ptr); }
    uintptr_t physint() const { return ptr; }

    uintptr_t logint() const { return uintptr_t(ptr) + KERNELMEM_ADDR; }
    T* log() const { return reinterpret_cast<T*>(logint()); }
    T* operator->() const { return log(); }

  protected:
    uint32_t ptr;
  };

  template<class T>
  T& operator*(LegacyPtr32<T> ptr) { return *ptr.log(); }

  template<class T>
  uint32_t kernel2phys(T* vp) {
    ASSERT(isKernelAddress(vp));
    return uint32_t(reinterpret_cast<uintptr_t>(vp) - KERNELMEM_ADDR);
  }

  template<class T>
  T* phys2kernel(uintptr_t phys) {
    return reinterpret_cast<T*>(phys + KERNELMEM_ADDR);
  }

  template<class T>
  T* image2kernel(T* vp) {
    ASSERT(isImageAddress(vp));
    return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(vp) - VIRT_ADDR + KERNELMEM_ADDR);
  }

} // namespace mythos
