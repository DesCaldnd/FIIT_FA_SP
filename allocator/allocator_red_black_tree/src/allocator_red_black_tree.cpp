#include <not_implemented.h>

#include "../include/allocator_red_black_tree.h"

allocator_red_black_tree::~allocator_red_black_tree()
{
    throw not_implemented("allocator_red_black_tree::~allocator_red_black_tree()", "your code should be here...");
}

allocator_red_black_tree::allocator_red_black_tree(
    allocator_red_black_tree &&other) noexcept
{
    throw not_implemented("allocator_red_black_tree::allocator_red_black_tree(allocator_red_black_tree &&) noexcept", "your code should be here...");
}

allocator_red_black_tree &allocator_red_black_tree::operator=(
    allocator_red_black_tree &&other) noexcept
{
    throw not_implemented("allocator_red_black_tree &allocator_red_black_tree::operator=(allocator_red_black_tree &&) noexcept", "your code should be here...");
}

allocator_red_black_tree::allocator_red_black_tree(
        size_t space_size,
        std::pmr::memory_resource *parent_allocator,
        allocator_with_fit_mode::fit_mode allocate_fit_mode)
{
    throw not_implemented("allocator_red_black_tree::allocator_red_black_tree(size_t ,std::pmr::memory_resource *,allocator_with_fit_mode::fit_mode)", "your code should be here...");
}

allocator_red_black_tree::allocator_red_black_tree(const allocator_red_black_tree &other)
{
    throw not_implemented("allocator_red_black_tree::allocator_red_black_tree(const allocator_red_black_tree &other)", "your code should be here...");
}

allocator_red_black_tree &allocator_red_black_tree::operator=(const allocator_red_black_tree &other)
{
    throw not_implemented("allocator_red_black_tree &allocator_red_black_tree::operator=(const allocator_red_black_tree &other)", "your code should be here...");
}

bool allocator_red_black_tree::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    throw not_implemented("bool allocator_red_black_tree::do_is_equal(const std::pmr::memory_resource &other) const noexcept", "your code should be here...");
}

[[nodiscard]] void *allocator_red_black_tree::do_allocate_sm(
    size_t size)
{
    throw not_implemented("[[nodiscard]] void *allocator_red_black_tree::do_allocate_sm(size_t)", "your code should be here...");
}


void allocator_red_black_tree::do_deallocate_sm(
    void *at)
{
    throw not_implemented("void allocator_red_black_tree::do_deallocate_sm(void *)", "your code should be here...");
}

void allocator_red_black_tree::set_fit_mode(allocator_with_fit_mode::fit_mode mode)
{
    throw not_implemented("void allocator_red_black_tree::set_fit_mode(allocator_with_fit_mode::fit_mode)", "your code should be here...");
}


std::vector<allocator_test_utils::block_info> allocator_red_black_tree::get_blocks_info() const
{
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_red_black_tree::get_blocks_info() const", "your code should be here...");
}

std::vector<allocator_test_utils::block_info> allocator_red_black_tree::get_blocks_info_inner() const
{
    throw not_implemented("std::vector<allocator_test_utils::block_info> allocator_red_black_tree::get_blocks_info_inner() const", "your code should be here...");
}


allocator_red_black_tree::rb_iterator allocator_red_black_tree::begin() const noexcept
{
    throw not_implemented("allocator_red_black_tree::rb_iterator allocator_red_black_tree::begin() const noexcept", "your code should be here...");
}

allocator_red_black_tree::rb_iterator allocator_red_black_tree::end() const noexcept
{
    throw not_implemented("allocator_red_black_tree::rb_iterator allocator_red_black_tree::end() const noexcept", "your code should be here...");
}


bool allocator_red_black_tree::rb_iterator::operator==(const allocator_red_black_tree::rb_iterator &other) const noexcept
{
    throw not_implemented("bool allocator_red_black_tree::rb_iterator::operator==(const allocator_red_black_tree::rb_iterator &) const noexcept", "your code should be here...");
}

bool allocator_red_black_tree::rb_iterator::operator!=(const allocator_red_black_tree::rb_iterator &other) const noexcept
{
    throw not_implemented("bool allocator_red_black_tree::rb_iterator::operator!=(const allocator_red_black_tree::rb_iterator &) const noexcept", "your code should be here...");
}

allocator_red_black_tree::rb_iterator &allocator_red_black_tree::rb_iterator::operator++() & noexcept
{
    throw not_implemented("allocator_red_black_tree::rb_iterator &allocator_red_black_tree::rb_iterator::operator++() & noexcept", "your code should be here...");
}

allocator_red_black_tree::rb_iterator allocator_red_black_tree::rb_iterator::operator++(int n)
{
    throw not_implemented("allocator_red_black_tree::rb_iterator allocator_red_black_tree::rb_iterator::operator++(int)", "your code should be here...");
}

size_t allocator_red_black_tree::rb_iterator::size() const noexcept
{
    throw not_implemented("size_t allocator_red_black_tree::rb_iterator::size() const noexcept", "your code should be here...");
}

void *allocator_red_black_tree::rb_iterator::operator*() const noexcept
{
    throw not_implemented("void *allocator_red_black_tree::rb_iterator::operator*() const noexcept", "your code should be here...");
}

allocator_red_black_tree::rb_iterator::rb_iterator()
{
    throw not_implemented("allocator_red_black_tree::rb_iterator::rb_iterator()", "your code should be here...");
}

allocator_red_black_tree::rb_iterator::rb_iterator(void *trusted)
{
    throw not_implemented("allocator_red_black_tree::rb_iterator::rb_iterator(void *)", "your code should be here...");
}

bool allocator_red_black_tree::rb_iterator::occupied() const noexcept
{
    throw not_implemented("bool allocator_red_black_tree::rb_iterator::occupied() const noexcept", "your code should be here...");
}
