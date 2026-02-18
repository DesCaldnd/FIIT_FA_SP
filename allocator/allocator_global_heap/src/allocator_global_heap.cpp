#include <not_implemented.h>
#include "../include/allocator_global_heap.h"

allocator_global_heap::allocator_global_heap()
{
    throw not_implemented("allocator_global_heap::allocator_global_heap()", "your code should be here...");
}

[[nodiscard]] void *allocator_global_heap::do_allocate_sm(
    size_t size)
{
    throw not_implemented("[[nodiscard]] void *allocator_global_heap::do_allocate_sm(size_t)", "your code should be here...");
}

void allocator_global_heap::do_deallocate_sm(
    void *at)
{
    throw not_implemented("void allocator_global_heap::do_deallocate_sm(void *)", "your code should be here...");
}

allocator_global_heap::~allocator_global_heap()
{
    throw not_implemented("allocator_global_heap::~allocator_global_heap()", "your code should be here...");
}

allocator_global_heap::allocator_global_heap(const allocator_global_heap &other)
{
    throw not_implemented("allocator_global_heap::allocator_global_heap(const allocator_global_heap &other)", "your code should be here...");
}

allocator_global_heap &allocator_global_heap::operator=(const allocator_global_heap &other)
{
    throw not_implemented("allocator_global_heap &allocator_global_heap::operator=(const allocator_global_heap &other)", "your code should be here...");
}

bool allocator_global_heap::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    throw not_implemented("bool allocator_global_heap::do_is_equal(const std::pmr::memory_resource &other) const noexcept", "your code should be here...");
}

allocator_global_heap::allocator_global_heap(allocator_global_heap &&other) noexcept
{
    throw not_implemented("allocator_global_heap::allocator_global_heap(allocator_global_heap &&) noexcept", "your code should be here...");
}

allocator_global_heap &allocator_global_heap::operator=(allocator_global_heap &&other) noexcept
{
    throw not_implemented("allocator_global_heap &allocator_global_heap::operator=(allocator_global_heap &&) noexcept", "your code should be here...");
}
