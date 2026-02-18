#include <gtest/gtest.h>
#include <iostream>
#include <allocator_global_heap.h>

TEST(allocatorGlobalHeapTests, test1)
{
    std::unique_ptr<smart_mem_resource> allocator_instance(new allocator_global_heap());
    auto block = reinterpret_cast<int *>(allocator_instance->allocate(sizeof(unsigned char) * 0));
    std::unique_ptr<smart_mem_resource> allocator_another_instance(new allocator_global_heap());
    allocator_another_instance->deallocate(block, 1);
}

TEST(allocatorGlobalHeapTests, test2)
{
    std::unique_ptr<smart_mem_resource> allocator_instance(new allocator_global_heap());
    
    auto first_block = reinterpret_cast<char *>(allocator_instance->allocate(sizeof(char) * 11));
    
    strcpy(first_block, "0123456789");
    
    allocator_instance->deallocate(first_block, 1);
}

TEST(allocatorGlobalHeapTests, test3)
{
    int const values_to_allocate_count = 30;

    std::unique_ptr<smart_mem_resource> allocator_instance(new allocator_global_heap());
    
    auto first_block = reinterpret_cast<unsigned int *>(allocator_instance->allocate(sizeof(unsigned int) * values_to_allocate_count));
    auto second_block = reinterpret_cast<unsigned int *>(allocator_instance->allocate(sizeof(unsigned long int) * values_to_allocate_count));
    auto third_block = reinterpret_cast<double *>(allocator_instance->allocate(sizeof(double) * values_to_allocate_count));
    
    for (int i = 0; i < values_to_allocate_count; i++)
    {
        first_block[i] = i;
        second_block[i] = i * i;
        third_block[i] = i / 2;
    }
    
    allocator_instance->deallocate(third_block, 1);
    allocator_instance->deallocate(first_block, 1);
    allocator_instance->deallocate(second_block, 1);
}

TEST(allocatorGlobalHeapTests, test4)
{
    int const values_to_allocate_count = 75;

    std::unique_ptr<smart_mem_resource> allocator_instance(new allocator_global_heap);
    
    auto first_block = reinterpret_cast<short *>(allocator_instance->allocate(sizeof(short) * values_to_allocate_count));
    auto second_block = reinterpret_cast<float *>(allocator_instance->allocate(sizeof(float) * values_to_allocate_count));
    
    for (int i = 0; i < values_to_allocate_count; i++)
    {
        second_block[i] = first_block[i] = (i & 1)
            ? i / 2.0
            : i;
    }
    
    allocator_instance->deallocate(first_block, 1);
    allocator_instance->deallocate(second_block, 1);
}

int main(
    int argc,
    char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}