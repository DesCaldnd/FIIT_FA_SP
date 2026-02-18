#include <not_implemented.h>
#include <cstddef>
#include "../include/allocator_buddies_system.h"

allocator_buddies_system::~allocator_buddies_system()
{
    throw not_implemented("allocator_buddies_system::~allocator_buddies_system()", "your code should be here...");
}

allocator_buddies_system::allocator_buddies_system(
    allocator_buddies_system &&other) noexcept
{
    throw not_implemented("allocator_buddies_system::allocator_buddies_system(allocator_buddies_system &&) noexcept", "your code should be here...");
}

allocator_buddies_system &allocator_buddies_system::operator=(
    allocator_buddies_system &&other) noexcept
{
    throw not_implemented("allocator_buddies_system &allocator_buddies_system::operator=(allocator_buddies_system &&) noexcept", "your code should be here...");
}

allocator_buddies_system::allocator_buddies_system(
        size_t space_size,
        std::pmr::memory_resource *parent_allocator,
        allocator_with_fit_mode::fit_mode allocate_fit_mode)
{
    throw not_implemented("allocator_buddies_system::allocator_buddies_system(size_t,std::pmr::memory_resource *,allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

[[nodiscard]] void *allocator_buddies_system::do_allocate_sm(
    size_t size)
{
    throw not_implemented("[[nodiscard]] void *allocator_buddies_system::do_allocate_sm(size_t)", "your code should be here...");
}

void allocator_buddies_system::do_deallocate_sm(void *at)
{
    throw not_implemented("void allocator_buddies_system::do_deallocate_sm(void *)", "your code should be here...");
}

allocator_buddies_system::allocator_buddies_system(const allocator_buddies_system &other)
{
    throw not_implemented("allocator_buddies_system::allocator_buddies_system(const allocator_buddies_system &other)", "your code should be here...");
}

allocator_buddies_system &allocator_buddies_system::operator=(const allocator_buddies_system &other)
{
    throw not_implemented("allocator_buddies_system &allocator_buddies_system::operator=(const allocator_buddies_system &other)", "your code should be here...");
}

bool allocator_buddies_system::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    throw not_implemented("bool allocator_buddies_system::do_is_equal(const std::pmr::memory_resource &other) const noexcept", "your code should be here...");
}

inline void allocator_buddies_system::set_fit_mode(
    allocator_with_fit_mode::fit_mode mode)
{
    throw not_implemented("inline void allocator_buddies_system::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}


std::vector<allocator_test_utils::block_info> allocator_buddies_system::get_blocks_info() const noexcept
{
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_buddies_system::get_blocks_info() const noexcept", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_buddies_system::get_blocks_info_inner() const
{
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_buddies_system::get_blocks_info_inner() const", "your code should be here...");
}

allocator_buddies_system::buddy_iterator allocator_buddies_system::begin() const noexcept
{
    throw not_implemented("allocator_buddies_system::buddy_iterator allocator_buddies_system::begin() const noexcept", "your code should be here...");
}

allocator_buddies_system::buddy_iterator allocator_buddies_system::end() const noexcept
{
    throw not_implemented("allocator_buddies_system::buddy_iterator allocator_buddies_system::end() const noexcept", "your code should be here...");
}

bool allocator_buddies_system::buddy_iterator::operator==(const allocator_buddies_system::buddy_iterator &other) const noexcept
{
    throw not_implemented("bool allocator_buddies_system::buddy_iterator::operator==(const allocator_buddies_system::buddy_iterator &) const noexcept", "your code should be here...");
}

bool allocator_buddies_system::buddy_iterator::operator!=(const allocator_buddies_system::buddy_iterator &other) const noexcept
{
    throw not_implemented("bool allocator_buddies_system::buddy_iterator::operator!=(const allocator_buddies_system::buddy_iterator &) const noexcept", "your code should be here...");
}

allocator_buddies_system::buddy_iterator &allocator_buddies_system::buddy_iterator::operator++() & noexcept
{
    throw not_implemented("allocator_buddies_system::buddy_iterator &allocator_buddies_system::buddy_iterator::operator++() & noexcept", "your code should be here...");
}

allocator_buddies_system::buddy_iterator allocator_buddies_system::buddy_iterator::operator++(int n)
{
    throw not_implemented("allocator_buddies_system::buddy_iterator allocator_buddies_system::buddy_iterator::operator++(int)", "your code should be here...");
}

size_t allocator_buddies_system::buddy_iterator::size() const noexcept
{
    throw not_implemented("size_t allocator_buddies_system::buddy_iterator::size() const noexcept", "your code should be here...");
}

bool allocator_buddies_system::buddy_iterator::occupied() const noexcept
{
    throw not_implemented("bool allocator_buddies_system::buddy_iterator::occupied() const noexcept", "your code should be here...");
}

void *allocator_buddies_system::buddy_iterator::operator*() const noexcept
{
    throw not_implemented("void *allocator_buddies_system::buddy_iterator::operator*() const noexcept", "your code should be here...");
}

allocator_buddies_system::buddy_iterator::buddy_iterator(void *start)
{
    throw not_implemented("allocator_buddies_system::buddy_iterator::buddy_iterator(void *)", "your code should be here...");
}

allocator_buddies_system::buddy_iterator::buddy_iterator()
{
    throw not_implemented("allocator_buddies_system::buddy_iterator::buddy_iterator()", "your code should be here...");
}
