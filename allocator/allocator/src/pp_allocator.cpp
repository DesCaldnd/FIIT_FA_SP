//
// Created by Des Caldnd on 6/29/2024.
//

#include "pp_allocator.h"


void smart_mem_resource::do_deallocate(void *p, size_t, size_t)
{
    do_deallocate_sm(p);
}

void *smart_mem_resource::do_allocate(size_t _Bytes, size_t _Align)
{
    return do_allocate_sm(_Bytes);
}

void *test_mem_resource::do_allocate_sm(size_t n)
{
    return ::operator new(n);
}

void test_mem_resource::do_deallocate_sm(void *p)
{
    ::operator delete(p);
}

bool test_mem_resource::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    auto p = dynamic_cast<const test_mem_resource *>(&other);
    return p != nullptr;
}
