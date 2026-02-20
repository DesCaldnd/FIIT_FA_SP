#include <gtest/gtest.h>
#include <list>
#include <allocator_red_black_tree.h>

TEST(allocatorRBTPositiveTests, test1)
{
	std::unique_ptr<smart_mem_resource> alloc(new allocator_red_black_tree(3000, nullptr, allocator_with_fit_mode::fit_mode::first_fit));

	auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int) * 250));

	auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(int) * 250));
	alloc->deallocate(first_block, 1);

	first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int) * 229));

	auto third_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int) * 250));

	alloc->deallocate(second_block, 1);
	alloc->deallocate(first_block, 1);
	alloc->deallocate(third_block, 1);

}

TEST(allocatorRBTPositiveTests, test5)
{
    std::unique_ptr<smart_mem_resource> allocator(new allocator_red_black_tree(20'000, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(allocator.get());
	int iterations_count = 100000;

	std::list<void *> allocated_blocks;
	srand((unsigned)time(nullptr));

	for (auto i = 0; i < iterations_count; i++)
	{
		switch (rand() % 3)
		{
			case 0:
			case 1:
				try
				{
					switch (rand() % 3)
					{
						case 0:
                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::first_fit);
							break;
						case 1:
                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
							break;
						case 2:
                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_worst_fit);
							break;
					}

					allocated_blocks.push_front(allocator->allocate(sizeof(char) * (rand() % 251 + 50)));
				}
				catch (std::bad_alloc const &ex)
				{
					std::cout << ex.what() << std::endl;
				}
				break;
			case 2:
				if (allocated_blocks.empty())
				{
					break;
				}

				auto it = allocated_blocks.begin();
				allocator->deallocate(*it, 1);
				allocated_blocks.erase(it);
				std::cout << "deallocation succeeded" << std::endl;
				break;
		}
	}

	while (!allocated_blocks.empty())
	{
		auto it = allocated_blocks.begin();
		allocator->deallocate(*it, 1);
		allocated_blocks.erase(it);
	}

}


TEST(allocatorRBTPositiveTests, test7)
{
    std::unique_ptr<smart_mem_resource> allocator(new allocator_red_black_tree(7500, nullptr, allocator_with_fit_mode::fit_mode::first_fit));
	int iterations_count = 10000;

	void* first = allocator->allocate(1 * 286);
	void* second = allocator->allocate(1 * 226);
	void* third = allocator->allocate(1 * 221);
	void* fourth = allocator->allocate(1 * 274);
	void* fifth = allocator->allocate(1 * 71);

	allocator->deallocate(second, 1);

	void* six = allocator->allocate(1 * 128);
	void* seven = allocator->allocate(1 * 174);
	void* eight = allocator->allocate(1 * 76);

	allocator->deallocate(first, 1);
	allocator->deallocate(six, 1);

	void* ten = allocator->allocate(1 * 201);

	void* eleven = allocator->allocate(1 * 234);
}


int main(
    int argc,
    char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}