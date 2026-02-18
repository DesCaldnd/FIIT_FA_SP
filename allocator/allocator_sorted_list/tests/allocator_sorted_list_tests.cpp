#include <gtest/gtest.h>
#include <list>

#include "../include/allocator_sorted_list.h"

TEST(allocatorSortedListPositiveTests, test1)
{
    std::unique_ptr<smart_mem_resource> alloc(new allocator_sorted_list(3000, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
    
    auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int) * 250));
    
    auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(int) * 250));
    alloc->deallocate(first_block, 1);
    
    first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int) * 245));
    
    alloc->deallocate(second_block, 1);
    alloc->deallocate(first_block, 1);
}

TEST(allocatorSortedListPositiveTests, test2)
{
    std::unique_ptr<smart_mem_resource> alloc(new allocator_sorted_list(3000, nullptr,
                                                            allocator_with_fit_mode::fit_mode::the_worst_fit));
    
    auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int) * 250));
    
    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(alloc.get());
    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::first_fit);
    auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(char) * 500));
    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
    auto third_block = reinterpret_cast<double *>(alloc->allocate(sizeof(double *) * 100));
    
    alloc->deallocate(first_block, 1);
    alloc->deallocate(second_block, 1);
    alloc->deallocate(third_block, 1);
}

TEST(allocatorSortedListPositiveTests, test3)
{
    std::unique_ptr<smart_mem_resource> allocator(new allocator_sorted_list(5000, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
    
    int iterations_count = 100;
    
    std::list<void *> allocated_blocks;
    srand((unsigned)time(nullptr));
    
    for (auto i = 0; i < iterations_count; i++)
    {
        switch (rand() % 2)
        {
            case 0:
                try
                {
                    allocated_blocks.push_front(allocator->allocate(sizeof(void *) * (rand() % 251 + 50)));
                    std::cout << "allocation succeeded" << std::endl;
                }
                catch (std::bad_alloc const &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case 1:
                if (allocated_blocks.empty())
                {
                    std::cout << "No blocks to deallocate" << std::endl;
                    
                    break;
                }
                
                auto it = allocated_blocks.begin();
                std::advance(it, rand() % allocated_blocks.size());
                allocator->deallocate(*it, 1);
                allocated_blocks.erase(it);
                std::cout << "deallocation succeeded" << std::endl;
                break;
        }
    }
    
    while (!allocated_blocks.empty())
    {
        auto it = allocated_blocks.begin();
        std::advance(it, rand() % allocated_blocks.size());
        allocator->deallocate(*it, 1);
        allocated_blocks.erase(it);
        std::cout << "deallocation succeeded" << std::endl;
    }
}

TEST(allocatorSortedListPositiveTests, test4)
{
    std::unique_ptr<smart_mem_resource> alloc(new allocator_sorted_list(1000, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
    
    auto first_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char) * 250));
    auto second_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(char) * 150));
    auto third_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char) * 300));
    
    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(alloc.get());
    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_worst_fit);
    auto four_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char) * 50));
    
    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
    auto five_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char) * 50));
    
    alloc->deallocate(first_block, 1);
    alloc->deallocate(second_block, 1);
    alloc->deallocate(third_block, 1);
    alloc->deallocate(four_block, 1);
    alloc->deallocate(five_block, 1);
}

TEST(allocatorSortedListPositiveTests, test5)
{
    std::unique_ptr<smart_mem_resource> alloc(new allocator_sorted_list(3000, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
    
    auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(char) * 250));
    auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(char) * 500));
    auto third_block = reinterpret_cast<double *>(alloc->allocate(sizeof(char) * 250));
    alloc->deallocate(first_block, 1);
    first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(char) * 245));

    std::unique_ptr<smart_mem_resource> allocator(new allocator_sorted_list(7500, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(allocator.get());
    int iterations_count = 10000;
    
    std::list<void *> allocated_blocks;
    srand((unsigned)time(nullptr));
    
    for (auto i = 0; i < iterations_count; i++)
    {
        switch (rand() % 2)
        {
            case 0:
                try
                {
                    switch (rand() % 3)
                    {
                        case 0:
                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::first_fit);
                        case 1:
                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
                        case 2:
                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_worst_fit);
                    }
                    
                    allocated_blocks.push_front(allocator->allocate(sizeof(char) * rand() % 251 + 50));
                    std::cout << "allocation succeeded" << std::endl;
                }
                catch (std::bad_alloc const &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case 1:
                if (allocated_blocks.empty())
                {
                    std::cout << "No blocks to deallocate" << std::endl;
                    
                    break;
                }
                
                auto it = allocated_blocks.begin();
                std::advance(it, rand() % allocated_blocks.size());
                allocator->deallocate(*it, 1);
                allocated_blocks.erase(it);
                std::cout << "deallocation succeeded" << std::endl;
                break;
        }
    }
    
    while (!allocated_blocks.empty())
    {
        auto it = allocated_blocks.begin();
        std::advance(it, rand() % allocated_blocks.size());
        allocator->deallocate(*it, 1);
        allocated_blocks.erase(it);
        std::cout << "deallocation succeeded" << std::endl;
    }
}

TEST(allocatorSortedListNegativeTests, test1)
{
    std::unique_ptr<smart_mem_resource> alloc(new allocator_sorted_list(3000, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
    
    ASSERT_THROW(alloc->allocate(sizeof(char) * 3100), std::bad_alloc);
}

int main(
    int argc,
    char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}