#include <iterator>
#include <utility>
#include <vector>
#include <boost/container/static_vector.hpp>
#include <concepts>
#include <stack>
#include <pp_allocator.h>
#include <search_tree.h>
#include <initializer_list>
#include <logger_guardant.h>

#ifndef MP_OS_BS_TREE_H
#define MP_OS_BS_TREE_H

template <typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5>
class BS_tree final : private logger_guardant, private compare
{
public:

    using tree_data_type = std::pair<tkey, tvalue>;
    using tree_data_type_const = std::pair<const tkey, tvalue>;
    using value_type = tree_data_type_const;

private:

    // TODO: Another restrictions
    static constexpr const size_t minimum_keys_in_node = t - 1;
    static constexpr const size_t maximum_keys_in_node = 2 * t - 1;

    // region comparators declaration

    inline bool compare_keys(const tkey& lhs, const tkey& rhs) const;
    inline bool compare_pairs(const tree_data_type& lhs, const tree_data_type& rhs) const;

    // endregion comparators declaration

    struct bstree_node
    {
        boost::container::static_vector<tree_data_type, maximum_keys_in_node + 1> _keys;
        boost::container::static_vector<bstree_node*, maximum_keys_in_node + 2> _pointers;
        bstree_node() noexcept;
//        std::vector<tree_data_type, pp_allocator<tree_data_type>> _keys;
//        std::vector<bstree_node*, pp_allocator<bstree_node*>> _pointers;
//
//        bstree_node(pp_allocator<bstree_node*> al);
    };

    pp_allocator<value_type> _allocator;
    logger* _logger;
    bstree_node* _root;
    size_t _size;

    logger* get_logger() const noexcept override;
    pp_allocator<value_type> get_allocator() const noexcept;

public:

    // region constructors declaration

    explicit BS_tree(const compare& cmp = compare(), pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    explicit BS_tree(pp_allocator<value_type> alloc, const compare& comp = compare(), logger *logger = nullptr);

    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit BS_tree(iterator begin, iterator end, const compare& cmp = compare(), pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    BS_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(), pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    // endregion constructors declaration

    // region five declaration

    BS_tree(const BS_tree& other);

    BS_tree(BS_tree&& other) noexcept;

    BS_tree& operator=(const BS_tree& other);

    BS_tree& operator=(BS_tree&& other) noexcept;

    ~BS_tree() noexcept override;

    // endregion five declaration

    // region iterators declaration

    class bstree_iterator;
    class bstree_reverse_iterator;
    class bstree_const_iterator;
    class bstree_const_reverse_iterator;

    class bstree_iterator final
    {
        std::stack<std::pair<bstree_node**, size_t>> _path;
        size_t _index;

    public:
        using value_type = tree_data_type_const;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;
        using self = bstree_iterator;

        friend class B_tree;
        friend class bstree_reverse_iterator;
        friend class bstree_const_iterator;
        friend class bstree_const_reverse_iterator;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;
        size_t current_node_keys_count() const noexcept;
        bool is_terminate_node() const noexcept;
        size_t index() const noexcept;

        explicit bstree_iterator(const std::stack<std::pair<bstree_node**, size_t>>& path = std::stack<std::pair<bstree_node**, size_t>>(), size_t index = 0);

    };

    class bstree_const_iterator final
    {
        std::stack<std::pair<bstree_node* const*, size_t>> _path;
        size_t _index;

    public:

        using value_type = tree_data_type_const;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;
        using self = bstree_const_iterator;

        friend class B_tree;
        friend class bstree_reverse_iterator;
        friend class bstree_iterator;
        friend class bstree_const_reverse_iterator;

        bstree_const_iterator(const bstree_iterator& it) noexcept;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;
        size_t current_node_keys_count() const noexcept;
        bool is_terminate_node() const noexcept;
        size_t index() const noexcept;

        explicit bstree_const_iterator(const std::stack<std::pair<bstree_node* const*, size_t>>& path = std::stack<std::pair<bstree_node* const*, size_t>>(), size_t index = 0);
    };

    class bstree_reverse_iterator final
    {
        std::stack<std::pair<bstree_node**, size_t>> _path;
        size_t _index;

    public:

        using value_type = tree_data_type_const;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;
        using self = bstree_reverse_iterator;

        friend class B_tree;
        friend class bstree_iterator;
        friend class bstree_const_iterator;
        friend class bstree_const_reverse_iterator;

        bstree_reverse_iterator(const bstree_iterator& it) noexcept;
        operator bstree_iterator() const noexcept;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;
        size_t current_node_keys_count() const noexcept;
        bool is_terminate_node() const noexcept;
        size_t index() const noexcept;

        explicit bstree_reverse_iterator(const std::stack<std::pair<bstree_node**, size_t>>& path = std::stack<std::pair<bstree_node**, size_t>>(), size_t index = 0);
    };

    class bstree_const_reverse_iterator final
    {
        std::stack<std::pair<bstree_node* const*, size_t>> _path;
        size_t _index;

    public:

        using value_type = tree_data_type_const;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;
        using self = bstree_const_reverse_iterator;

        friend class B_tree;
        friend class bstree_reverse_iterator;
        friend class bstree_const_iterator;
        friend class bstree_iterator;

        bstree_const_reverse_iterator(const bstree_reverse_iterator& it) noexcept;
        operator bstree_const_iterator() const noexcept;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;
        size_t current_node_keys_count() const noexcept;
        bool is_terminate_node() const noexcept;
        size_t index() const noexcept;

        explicit bstree_const_reverse_iterator(const std::stack<std::pair<bstree_node* const*, size_t>>& path = std::stack<std::pair<bstree_node* const*, size_t>>(), size_t index = 0);
    };

    friend class bstree_iterator;
    friend class bstree_const_iterator;
    friend class bstree_reverse_iterator;
    friend class bstree_const_reverse_iterator;

    // endregion iterators declaration

    // region element access declaration

    /*
     * Returns a reference to the mapped value of the element with specified key. If no such element exists, an exception of type std::out_of_range is thrown.
     */
    tvalue& at(const tkey&);
    const tvalue& at(const tkey&) const;

    /*
     * If key not exists, makes default initialization of value
     */
    tvalue& operator[](const tkey& key);
    tvalue& operator[](tkey&& key);

    // endregion element access declaration
    // region iterator begins declaration

    bstree_iterator begin();
    bstree_iterator end();

    bstree_const_iterator begin() const;
    bstree_const_iterator end() const;

    bstree_const_iterator cbegin() const;
    bstree_const_iterator cend() const;

    bstree_reverse_iterator rbegin();
    bstree_reverse_iterator rend();

    bstree_const_reverse_iterator rbegin() const;
    bstree_const_reverse_iterator rend() const;

    bstree_const_reverse_iterator crbegin() const;
    bstree_const_reverse_iterator crend() const;

    // endregion iterator begins declaration

    // region lookup declaration

    size_t size() const noexcept;
    bool empty() const noexcept;

    /*
     * Returns end() if not exist
     */

    bstree_iterator find(const tkey& key);
    bstree_const_iterator find(const tkey& key) const;

    bstree_iterator lower_bound(const tkey& key);
    bstree_const_iterator lower_bound(const tkey& key) const;

    bstree_iterator upper_bound(const tkey& key);
    bstree_const_iterator upper_bound(const tkey& key) const;

    bool contains(const tkey& key) const;

    // endregion lookup declaration

    // region modifiers declaration

    void clear() noexcept;

    /*
     * Does nothing if key exists, delegates to emplace.
     * Second return value is true, when inserted
     */
    std::pair<bstree_iterator, bool> insert(const tree_data_type& data);
    std::pair<bstree_iterator, bool> insert(tree_data_type&& data);

    template <typename ...Args>
    std::pair<bstree_iterator, bool> emplace(Args&&... args);

    /*
     * Updates value if key exists, delegates to emplace.
     */
    bstree_iterator insert_or_assign(const tree_data_type& data);
    bstree_iterator insert_or_assign(tree_data_type&& data);

    template <typename ...Args>
    bstree_iterator emplace_or_assign(Args&&... args);

    /*
     * Return iterator to node next ro removed or end() if key not exists
     */
    bstree_iterator erase(bstree_iterator pos);
    bstree_iterator erase(bstree_const_iterator pos);

    bstree_iterator erase(bstree_iterator beg, bstree_iterator en);
    bstree_iterator erase(bstree_const_iterator beg, bstree_const_iterator en);


    bstree_iterator erase(const tkey& key);

    // endregion modifiers declaration
};

template<std::input_iterator iterator, compator<typename std::iterator_traits<iterator>::value_type::first_type> compare = std::less<typename std::iterator_traits<iterator>::value_type::first_type>,
        std::size_t t = 5, typename U>
BS_tree(iterator begin, iterator end, const compare &cmp = compare(), pp_allocator<U> = pp_allocator<U>(),
        logger *logger = nullptr) -> BS_tree<typename std::iterator_traits<iterator>::value_type::first_type, typename std::iterator_traits<iterator>::value_type::second_type, compare, t>;

template<typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5, typename U>
BS_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare &cmp = compare(), pp_allocator<U> = pp_allocator<U>(),
        logger *logger = nullptr) -> BS_tree<tkey, tvalue, compare, t>;

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::compare_pairs(const BS_tree::tree_data_type &lhs,
                                                     const BS_tree::tree_data_type &rhs) const
{
    return compare_keys(lhs.first, rhs.first);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_node::bstree_node() noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
logger * BS_tree<tkey, tvalue, compare, t>::get_logger() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
pp_allocator<typename BS_tree<tkey, tvalue, compare, t>::value_type> BS_tree<tkey, tvalue, compare, t>::
get_allocator() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator::reference BS_tree<tkey, tvalue, compare, t>::
bstree_iterator::operator*() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator::pointer BS_tree<tkey, tvalue, compare, t>::bstree_iterator
::operator->() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator::self & BS_tree<tkey, tvalue, compare, t>::bstree_iterator::
operator++()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator::self BS_tree<tkey, tvalue, compare, t>::bstree_iterator::
operator++(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator::self & BS_tree<tkey, tvalue, compare, t>::bstree_iterator::
operator--()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator::self BS_tree<tkey, tvalue, compare, t>::bstree_iterator::
operator--(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_iterator::operator==(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_iterator::operator!=(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_iterator::depth() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_iterator::current_node_keys_count() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_iterator::is_terminate_node() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_iterator::index() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_iterator::bstree_iterator(
    const std::stack<std::pair<bstree_node **, size_t>> &path, size_t index)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::bstree_const_iterator(const bstree_iterator &it) noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::reference BS_tree<tkey, tvalue, compare, t>::
bstree_const_iterator::operator*() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::pointer BS_tree<tkey, tvalue, compare, t>::
bstree_const_iterator::operator->() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::self & BS_tree<tkey, tvalue, compare, t>::
bstree_const_iterator::operator++()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::self BS_tree<tkey, tvalue, compare, t>::
bstree_const_iterator::operator++(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::self & BS_tree<tkey, tvalue, compare, t>::
bstree_const_iterator::operator--()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::self BS_tree<tkey, tvalue, compare, t>::
bstree_const_iterator::operator--(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::operator==(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::operator!=(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::depth() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::current_node_keys_count() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::is_terminate_node() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::index() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator::bstree_const_iterator(
    const std::stack<std::pair<bstree_node * const*, size_t>> &path, size_t index)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::bstree_reverse_iterator(const bstree_iterator &it) noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::operator BS_tree<tkey, tvalue, compare, t>::bstree_iterator() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::reference BS_tree<tkey, tvalue, compare, t>::
bstree_reverse_iterator::operator*() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::pointer BS_tree<tkey, tvalue, compare, t>::
bstree_reverse_iterator::operator->() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::self & BS_tree<tkey, tvalue, compare, t>::
bstree_reverse_iterator::operator++()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::self BS_tree<tkey, tvalue, compare, t>::
bstree_reverse_iterator::operator++(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::self & BS_tree<tkey, tvalue, compare, t>::
bstree_reverse_iterator::operator--()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::self BS_tree<tkey, tvalue, compare, t>::
bstree_reverse_iterator::operator--(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::operator==(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::operator!=(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::depth() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::current_node_keys_count() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::is_terminate_node() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::index() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator::bstree_reverse_iterator(
    const std::stack<std::pair<bstree_node **, size_t>> &path, size_t index)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::bstree_const_reverse_iterator(
    const bstree_reverse_iterator &it) noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::operator BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::reference BS_tree<tkey, tvalue, compare, t>::
bstree_const_reverse_iterator::operator*() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::pointer BS_tree<tkey, tvalue, compare, t>::
bstree_const_reverse_iterator::operator->() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::self & BS_tree<tkey, tvalue, compare, t>::
bstree_const_reverse_iterator::operator++()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::self BS_tree<tkey, tvalue, compare, t>::
bstree_const_reverse_iterator::operator++(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::self & BS_tree<tkey, tvalue, compare, t>::
bstree_const_reverse_iterator::operator--()
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::self BS_tree<tkey, tvalue, compare, t>::
bstree_const_reverse_iterator::operator--(int)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::operator==(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::operator!=(const self &other) const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::depth() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::current_node_keys_count() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::is_terminate_node() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::index() const noexcept
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator::bstree_const_reverse_iterator(
    const std::stack<std::pair<bstree_node * const*, size_t>> &path, size_t index)
{
    throw not_implemented("too laazyy", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::compare_keys(const tkey &lhs, const tkey &rhs) const
{
    return compare::operator()(lhs, rhs);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::BS_tree(const compare& cmp, pp_allocator<value_type> alloc, logger* logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>::BS_tree(const compare& cmp, pp_allocator<value_type> alloc, logger* logger)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::BS_tree(pp_allocator<value_type> alloc, const compare& comp, logger* logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>::BS_tree(pp_allocator<value_type> alloc, const compare& comp, logger* logger)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
template<input_iterator_for_pair<tkey, tvalue> iterator>
BS_tree<tkey, tvalue, compare, t>::BS_tree(iterator begin, iterator end, const compare& cmp, pp_allocator<value_type> alloc, logger* logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> template<input_iterator_for_pair<tkey, tvalue> iterator> BS_tree<tkey, tvalue, compare, t>::BS_tree(iterator begin, iterator end, const compare& cmp, pp_allocator<value_type> alloc, logger* logger)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::BS_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp, pp_allocator<value_type> alloc, logger* logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>::BS_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp, pp_allocator<value_type> alloc, logger* logger)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::BS_tree(const BS_tree& other)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>::BS_tree(const BS_tree& other)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::BS_tree(BS_tree&& other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>::BS_tree(BS_tree&& other) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>& BS_tree<tkey, tvalue, compare, t>::operator=(const BS_tree& other)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>& BS_tree<tkey, tvalue, compare, t>::operator=(const BS_tree& other)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>& BS_tree<tkey, tvalue, compare, t>::operator=(BS_tree&& other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>& BS_tree<tkey, tvalue, compare, t>::operator=(BS_tree&& other) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
BS_tree<tkey, tvalue, compare, t>::~BS_tree() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> BS_tree<tkey, tvalue, compare, t>::~BS_tree() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
tvalue& BS_tree<tkey, tvalue, compare, t>::at(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> tvalue& BS_tree<tkey, tvalue, compare, t>::at(const tkey& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
const tvalue& BS_tree<tkey, tvalue, compare, t>::at(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> const tvalue& BS_tree<tkey, tvalue, compare, t>::at(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
tvalue& BS_tree<tkey, tvalue, compare, t>::operator[](const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> tvalue& BS_tree<tkey, tvalue, compare, t>::operator[](const tkey& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
tvalue& BS_tree<tkey, tvalue, compare, t>::operator[](tkey&& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> tvalue& BS_tree<tkey, tvalue, compare, t>::operator[](tkey&& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::begin()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::begin()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::end()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::end()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::begin() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::begin() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::end() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::end() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::cbegin() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::cbegin() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::cend() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::cend() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rbegin()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rbegin()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rend()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rend()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rbegin() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rbegin() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rend() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::rend() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::crbegin() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::crbegin() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::crend() const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_reverse_iterator BS_tree<tkey, tvalue, compare, t>::crend() const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t BS_tree<tkey, tvalue, compare, t>::size() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> size_t BS_tree<tkey, tvalue, compare, t>::size() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::empty() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> bool BS_tree<tkey, tvalue, compare, t>::empty() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::find(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::find(const tkey& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::find(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::find(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::lower_bound(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::lower_bound(const tkey& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::lower_bound(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::lower_bound(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::upper_bound(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::upper_bound(const tkey& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::upper_bound(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_const_iterator BS_tree<tkey, tvalue, compare, t>::upper_bound(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BS_tree<tkey, tvalue, compare, t>::contains(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> bool BS_tree<tkey, tvalue, compare, t>::contains(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
void BS_tree<tkey, tvalue, compare, t>::clear() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> void BS_tree<tkey, tvalue, compare, t>::clear() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
std::pair<typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator, bool> BS_tree<tkey, tvalue, compare, t>::insert(const tree_data_type& data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> std::pair<typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator, bool> BS_tree<tkey, tvalue, compare, t>::insert(const tree_data_type& data)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
std::pair<typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator, bool> BS_tree<tkey, tvalue, compare, t>::insert(tree_data_type&& data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> std::pair<typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator, bool> BS_tree<tkey, tvalue, compare, t>::insert(tree_data_type&& data)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
template <typename ...Args>
std::pair<typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator, bool> BS_tree<tkey, tvalue, compare, t>::emplace(Args&&... args)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> template <typename ...Args> std::pair<typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator, bool> BS_tree<tkey, tvalue, compare, t>::emplace(Args&&... args)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::insert_or_assign(const tree_data_type& data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::insert_or_assign(const tree_data_type& data)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::insert_or_assign(tree_data_type&& data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::insert_or_assign(tree_data_type&& data)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
template <typename ...Args>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::emplace_or_assign(Args&&... args)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> template <typename ...Args> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::emplace_or_assign(Args&&... args)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_iterator pos)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_iterator pos)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_const_iterator pos)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_const_iterator pos)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_iterator beg, bstree_iterator en)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_iterator beg, bstree_iterator en)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_const_iterator beg, bstree_const_iterator en)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(bstree_const_iterator beg, bstree_const_iterator en)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(const tkey& key)
{
    throw not_implemented(
            "template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t> typename BS_tree<tkey, tvalue, compare, t>::bstree_iterator BS_tree<tkey, tvalue, compare, t>::erase(const tkey& key)",
            "your code should be here...");
}

#endif