#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_SPLAY_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_SPLAY_TREE_H

#include <binary_search_tree.h>

namespace __detail
{
    class SPL_TAG;

    template<typename tkey, typename tvalue, typename compare>
    class bst_impl<tkey, tvalue, compare, SPL_TAG>
    {
        template<class ...Args>
        static binary_search_tree<tkey, tvalue, compare, SPL_TAG>::node* create_node(binary_search_tree<tkey, tvalue, compare, SPL_TAG>& cont, Args&& ...args);

        static void delete_node(binary_search_tree<tkey, tvalue, compare, SPL_TAG>& cont);

        //Does not invalidate node*, needed for splay tree
        static void post_search(binary_search_tree<tkey, tvalue, compare, SPL_TAG>::node**){}

        //Does not invalidate node*
        static void post_insert(binary_search_tree<tkey, tvalue, compare, SPL_TAG>& cont, binary_search_tree<tkey, tvalue, compare, SPL_TAG>::node**);

        static void erase(binary_search_tree<tkey, tvalue, compare, SPL_TAG>& cont, binary_search_tree<tkey, tvalue, compare, SPL_TAG>::node**);

        static void swap(binary_search_tree<tkey, tvalue, compare, SPL_TAG>& lhs, binary_search_tree<tkey, tvalue, compare, SPL_TAG>& rhs) noexcept;
    };
}

template<typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>>
class splay_tree final: public binary_search_tree<tkey, tvalue, compare, __detail::SPL_TAG>
{

    using parent = binary_search_tree<tkey, tvalue, compare, __detail::SPL_TAG>;
public:

    using value_type = parent::value_type;

    explicit splay_tree(
            const compare& comp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger *log = nullptr);

    explicit splay_tree(
            pp_allocator<value_type> alloc,
            const compare& comp = compare(),
            logger *log = nullptr);

    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit splay_tree(iterator begin, iterator end, const compare& cmp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger* log = nullptr);

    template<std::ranges::input_range Range>
    explicit splay_tree(Range&& range, const compare& cmp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger* log = nullptr);


    splay_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger* log = nullptr);

public:
    
    ~splay_tree() noexcept final;
    
    splay_tree(splay_tree const &other);
    
    splay_tree &operator=(splay_tree const &other);
    
    splay_tree(splay_tree &&other) noexcept;
    
    splay_tree &operator=(splay_tree &&other) noexcept;

};

template<typename compare, typename U, typename iterator>
explicit splay_tree(iterator begin, iterator end, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* log = nullptr) -> splay_tree<const typename std::iterator_traits<iterator>::value_type::first_type, typename std::iterator_traits<iterator>::value_type::second_type, compare>;

template<typename compare, typename U, std::ranges::forward_range Range>
explicit splay_tree(Range&& range, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* log = nullptr) -> splay_tree<const typename std::iterator_traits<typename std::ranges::iterator_t<Range>>::value_type::first_type, typename std::iterator_traits<typename std::ranges::iterator_t<Range>>::value_type::second_type, compare> ;

template<typename tkey, typename tvalue, typename compare, typename U>
splay_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* log = nullptr) -> splay_tree<tkey, tvalue, compare>;

// region implementation

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare>::splay_tree(
        const compare& comp,
        pp_allocator<value_type> alloc,
        logger *log)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare>::splay_tree(const compare& comp, pp_allocator<value_type> alloc, logger *log)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare>::splay_tree(
        pp_allocator<value_type> alloc,
        const compare& comp,
        logger *log)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare>::splay_tree(pp_allocator<value_type> alloc, const compare& comp, logger *log)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
template<input_iterator_for_pair<tkey, tvalue> iterator>
splay_tree<tkey, tvalue, compare>::splay_tree(
        iterator begin,
        iterator end,
        const compare& cmp,
        pp_allocator<value_type> alloc,
        logger* log)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> template<input_iterator_for_pair<tkey, tvalue> iterator>splay_tree<tkey, tvalue, compare>::splay_tree(iterator begin,iterator end,const compare& cmp,pp_allocator<value_type> alloc,logger* log)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
template<std::ranges::input_range Range>
splay_tree<tkey, tvalue, compare>::splay_tree(
        Range&& range,
        const compare& cmp,
        pp_allocator<value_type> alloc,
        logger* log)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> template<std::ranges::input_range Range> splay_tree<tkey, tvalue, compare>::splay_tree(Range&& range, const compare& cmp, pp_allocator<value_type> alloc, logger* log)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare>::splay_tree(
        std::initializer_list<std::pair<tkey, tvalue>> data,
        const compare& cmp,
        pp_allocator<value_type> alloc,
        logger* log)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare>::splay_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp, pp_allocator<value_type> alloc, logger* log)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare>::~splay_tree() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare>::~splay_tree() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare>::splay_tree(splay_tree const &other)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare>::splay_tree(splay_tree const &other)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare> &splay_tree<tkey, tvalue, compare>::operator=(splay_tree const &other)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare> &splay_tree<tkey, tvalue, compare>::operator=(splay_tree const &other)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare>::splay_tree(splay_tree &&other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare>::splay_tree(splay_tree &&other) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare>
splay_tree<tkey, tvalue, compare> &splay_tree<tkey, tvalue, compare>::operator=(splay_tree &&other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare> splay_tree<tkey, tvalue, compare> &splay_tree<tkey, tvalue, compare>::operator=(splay_tree &&other) noexcept", "your code should be here...");
}

// endregion implementation

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_SPLAY_TREE_H