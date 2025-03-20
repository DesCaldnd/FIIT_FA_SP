#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H

#include <list>
#include <stack>
#include <vector>
#include <memory>
#include <logger.h>
#include <logger_guardant.h>
#include <not_implemented.h>
#include <search_tree.h>
#include <stack>
#include <ranges>
#include <pp_allocator.h>
#include <concepts>

namespace __detail
{
    template<typename tkey, typename tvalue, typename compare, typename tag>
    class bst_impl;

    class BST_TAG;
}


template<typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, typename tag = __detail::BST_TAG>
class binary_search_tree : private compare
{
public:

    using value_type = std::pair<const tkey, tvalue>;

    friend class __detail::bst_impl<tkey, tvalue, compare, tag>;

protected:
    
    struct node
    {
    
    public:
        
        value_type data;

        node* parent;
        node* left_subtree;
        node* right_subtree;

        template<class ...Args>
        explicit node(node* parent, Args&& ...args);


        virtual ~node() =default;
    };

    inline bool compare_keys(const tkey& lhs, const tkey& rhs) const;

    inline bool compare_pairs(const value_type & lhs, const value_type & rhs) const;

public:


    // region iterators definition

    class prefix_iterator;
    class prefix_const_iterator;
    class prefix_reverse_iterator;
    class prefix_const_reverse_iterator;

    class infix_iterator;
    class infix_const_iterator;
    class infix_reverse_iterator;
    class infix_const_reverse_iterator;

    class postfix_iterator;
    class postfix_const_iterator;
    class postfix_reverse_iterator;
    class postfix_const_reverse_iterator;

    /** @brief Watch about behavior of reverse iterators.
     *
     * @example Arrow is common iterator
     *  1 2 3 -> 4 5 6 7
     *  *it == 4.
     *
     *  @example But reverse:
     *  1 2 3 \<- 4 5 6 7
     *  *rit == 3
     */

    class prefix_iterator
    {
    protected:

        node* _data;

        /** If iterator == end or before_begin _data points to nullptr, _backup to last node
         *
         */
        node* _backup;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        
        explicit prefix_iterator(node* data = nullptr);

        virtual ~prefix_iterator() =default;

        bool operator==(
            prefix_iterator const &other) const noexcept;
        
        bool operator!=(
            prefix_iterator const &other) const noexcept;
        
        prefix_iterator &operator++() & noexcept;
        
        prefix_iterator operator++(int not_used) noexcept;

        prefix_iterator &operator--() & noexcept;

        prefix_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;
        
    };
    
    class prefix_const_iterator
    {
    protected:

        prefix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit prefix_const_iterator(const node* data = nullptr);

        prefix_const_iterator(const prefix_iterator&) noexcept;

        virtual ~prefix_const_iterator() =default;

        bool operator==(
                prefix_iterator const &other) const noexcept;

        bool operator!=(
                prefix_iterator const &other) const noexcept;

        prefix_const_iterator &operator++() & noexcept;

        prefix_const_iterator operator++(int not_used) noexcept;

        prefix_const_iterator &operator--() & noexcept;

        prefix_const_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;
        
    };
    
    class prefix_reverse_iterator
    {
    protected:

        prefix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit prefix_reverse_iterator(node* data = nullptr);

        prefix_reverse_iterator(const prefix_iterator&) noexcept;
        operator prefix_iterator() const noexcept;

        prefix_iterator base() const noexcept;

        virtual ~prefix_reverse_iterator() =default;

        bool operator==(prefix_reverse_iterator const &other) const noexcept;

        bool operator!=(prefix_reverse_iterator const &other) const noexcept;

        prefix_reverse_iterator &operator++() & noexcept;

        prefix_reverse_iterator operator++(int not_used) noexcept;

        prefix_reverse_iterator &operator--() & noexcept;

        prefix_reverse_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;
        
    };
    
    class prefix_const_reverse_iterator
    {
    protected:

        prefix_const_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit prefix_const_reverse_iterator(const node* data = nullptr);

        prefix_const_reverse_iterator(const prefix_const_iterator&) noexcept;

        operator prefix_const_iterator() const noexcept;
        prefix_const_iterator base() const noexcept;

        virtual ~prefix_const_reverse_iterator() =default;

        bool operator==(prefix_const_reverse_iterator const &other) const noexcept;

        bool operator!=(prefix_const_reverse_iterator const &other) const noexcept;

        prefix_const_reverse_iterator &operator++() & noexcept;

        prefix_const_reverse_iterator operator++(int not_used) noexcept;

        prefix_const_reverse_iterator &operator--() & noexcept;

        prefix_const_reverse_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;
        
    };


    class infix_iterator
    {
    protected:

        node* _data;

        /** If iterator == end or before_begin _data points to nullptr, _backup to last node
         *
         */
        node* _backup;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit infix_iterator(node* data = nullptr);

        virtual ~infix_iterator() =default;

        bool operator==(
                infix_iterator const &other) const noexcept;

        bool operator!=(
                infix_iterator const &other) const noexcept;

        infix_iterator &operator++() & noexcept;

        infix_iterator operator++(int not_used) noexcept;

        infix_iterator &operator--() & noexcept;

        infix_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };

    class infix_const_iterator
    {
    protected:

        infix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit infix_const_iterator(const node* data = nullptr);

        infix_const_iterator(const infix_iterator&) noexcept;

        virtual ~infix_const_iterator() =default;

        bool operator==(
                infix_iterator const &other) const noexcept;

        bool operator!=(
                infix_iterator const &other) const noexcept;

        infix_const_iterator &operator++() & noexcept;

        infix_const_iterator operator++(int not_used) noexcept;

        infix_const_iterator &operator--() & noexcept;

        infix_const_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };

    class infix_reverse_iterator
    {
    protected:

        infix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit infix_reverse_iterator(node* data = nullptr);

        infix_reverse_iterator(const infix_iterator&) noexcept;
        operator infix_iterator() const noexcept;

        infix_iterator base() const noexcept;

        virtual ~infix_reverse_iterator() =default;

        bool operator==(infix_reverse_iterator const &other) const noexcept;

        bool operator!=(infix_reverse_iterator const &other) const noexcept;

        infix_reverse_iterator &operator++() & noexcept;

        infix_reverse_iterator operator++(int not_used) noexcept;

        infix_reverse_iterator &operator--() & noexcept;

        infix_reverse_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };

    class infix_const_reverse_iterator
    {
    protected:

        infix_const_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit infix_const_reverse_iterator(const node* data = nullptr);

        infix_const_reverse_iterator(const infix_const_iterator&) noexcept;

        operator infix_const_iterator() const noexcept;
        infix_const_iterator base() const noexcept;

        virtual ~infix_const_reverse_iterator() =default;

        bool operator==(infix_const_reverse_iterator const &other) const noexcept;

        bool operator!=(infix_const_reverse_iterator const &other) const noexcept;

        infix_const_reverse_iterator &operator++() & noexcept;

        infix_const_reverse_iterator operator++(int not_used) noexcept;

        infix_const_reverse_iterator &operator--() & noexcept;

        infix_const_reverse_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };


    class postfix_iterator
    {
    protected:

        node* _data;

        /** If iterator == end or before_begin _data points to nullptr, _backup to last node
         *
         */
        node* _backup;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit postfix_iterator(node* data = nullptr);

        virtual ~postfix_iterator() =default;

        bool operator==(
                postfix_iterator const &other) const noexcept;

        bool operator!=(
                postfix_iterator const &other) const noexcept;

        postfix_iterator &operator++() & noexcept;

        postfix_iterator operator++(int not_used) noexcept;

        postfix_iterator &operator--() & noexcept;

        postfix_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };

    class postfix_const_iterator
    {
    protected:

        postfix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit postfix_const_iterator(const node* data = nullptr);

        postfix_const_iterator(const postfix_iterator&) noexcept;

        virtual ~postfix_const_iterator() =default;

        bool operator==(
                postfix_iterator const &other) const noexcept;

        bool operator!=(
                postfix_iterator const &other) const noexcept;

        postfix_const_iterator &operator++() & noexcept;

        postfix_const_iterator operator++(int not_used) noexcept;

        postfix_const_iterator &operator--() & noexcept;

        postfix_const_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };

    class postfix_reverse_iterator
    {
    protected:

        postfix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit postfix_reverse_iterator(node* data = nullptr);

        postfix_reverse_iterator(const postfix_iterator&) noexcept;
        operator postfix_iterator() const noexcept;

        postfix_iterator base() const noexcept;

        virtual ~postfix_reverse_iterator() =default;

        bool operator==(postfix_reverse_iterator const &other) const noexcept;

        bool operator!=(postfix_reverse_iterator const &other) const noexcept;

        postfix_reverse_iterator &operator++() & noexcept;

        postfix_reverse_iterator operator++(int not_used) noexcept;

        postfix_reverse_iterator &operator--() & noexcept;

        postfix_reverse_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };

    class postfix_const_reverse_iterator
    {
    protected:

        postfix_const_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference_type = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit postfix_const_reverse_iterator(const node* data = nullptr);

        postfix_const_reverse_iterator(const postfix_const_iterator&) noexcept;

        operator postfix_const_iterator() const noexcept;
        postfix_const_iterator base() const noexcept;

        virtual ~postfix_const_reverse_iterator() =default;

        bool operator==(postfix_const_reverse_iterator const &other) const noexcept;

        bool operator!=(postfix_const_reverse_iterator const &other) const noexcept;

        postfix_const_reverse_iterator &operator++() & noexcept;

        postfix_const_reverse_iterator operator++(int not_used) noexcept;

        postfix_const_reverse_iterator &operator--() & noexcept;

        postfix_const_reverse_iterator const operator--(int not_used) const noexcept;

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;

    };



    friend class prefix_iterator;
    friend class prefix_const_iterator;
    friend class prefix_reverse_iterator;
    friend class prefix_const_reverse_iterator;

    friend class postfix_iterator;
    friend class postfix_const_iterator;
    friend class postfix_reverse_iterator;
    friend class postfix_const_reverse_iterator;

    friend class infix_iterator;
    friend class infix_const_iterator;
    friend class infix_reverse_iterator;
    friend class infix_const_reverse_iterator;

    // endregion iterators definition


protected:
    
    node *_root;
    logger* _logger;
    size_t _size;
    
    /** You should use coercion ctor or template methods of allocator
     */
    pp_allocator<value_type> _allocator;

public:
    explicit binary_search_tree(
            const compare& comp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger *logger = nullptr);

    explicit binary_search_tree(
            pp_allocator<value_type> alloc,
            const compare& comp = compare(),
            logger *logger = nullptr);


    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit binary_search_tree(iterator begin, iterator end, const compare& cmp = compare(), 
                                pp_allocator<value_type> alloc = pp_allocator<value_type>(), 
                                logger* logger = nullptr);

    template<std::ranges::input_range Range>
    explicit binary_search_tree(Range&& range, const compare& cmp = compare(),
                                pp_allocator<value_type> alloc = pp_allocator<value_type>(),
                                logger* logger = nullptr);


    binary_search_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(),
                       pp_allocator<value_type> alloc = pp_allocator<value_type>(), 
                       logger* logger = nullptr);

public:
    
    binary_search_tree(const binary_search_tree &other);
    
    binary_search_tree(binary_search_tree &&other) noexcept;
    
    binary_search_tree &operator=(const binary_search_tree &other);
    
    binary_search_tree &operator=(binary_search_tree &&other) noexcept;
    
    virtual ~binary_search_tree();

public:

    tvalue& at(const tkey& key);
    const tvalue& at(const tkey& key) const;

    tvalue& operator[](const tkey& key);
    tvalue& operator[](tkey&& key);

    bool empty() const noexcept;

    size_t size() const noexcept;

    void clear() noexcept;

    std::pair<infix_iterator, bool> insert(const value_type&);
    std::pair<infix_iterator, bool> insert(value_type&&);

    template<std::input_iterator InputIt>
    void insert(InputIt first, InputIt last);

    template<std::ranges::input_range R>
    void insert_range( R&& rg );

    template<class ...Args>
    std::pair<infix_iterator, bool> emplace(Args&&...args);

    infix_iterator insert_or_assign(const value_type&);
    infix_iterator insert_or_assign(value_type&&);

    template<std::input_iterator InputIt >
    void insert_or_assign(InputIt first, InputIt last);


    template<class ...Args>
    infix_iterator emplace_or_assign(Args&&...args);

    virtual void swap(binary_search_tree& other) noexcept;

    bool contains(const tkey& key) const;

    infix_iterator find(const tkey&);
    infix_const_iterator find(const tkey&) const;


    infix_iterator lower_bound(const tkey&);
    infix_const_iterator lower_bound(const tkey&) const;

    infix_iterator upper_bound(const tkey&);
    infix_const_iterator upper_bound(const tkey&) const;

    infix_iterator erase(infix_iterator pos);
    infix_iterator erase(infix_const_iterator pos);

    infix_iterator erase(infix_iterator first, infix_iterator last);
    infix_iterator erase(infix_const_iterator first, infix_const_iterator last);

    size_t erase(const tkey& key);

public:
    
    // region iterators requests definition

    infix_iterator begin() noexcept;

    infix_iterator end() noexcept;

    infix_const_iterator begin() const noexcept;

    infix_const_iterator end() const noexcept;

    infix_const_iterator cbegin() const noexcept;

    infix_const_iterator cend() const noexcept;

    infix_reverse_iterator rbegin() noexcept;

    infix_reverse_iterator rend() noexcept;

    infix_const_reverse_iterator rbegin() const noexcept;

    infix_const_reverse_iterator rend() const noexcept;

    infix_const_reverse_iterator crbegin() const noexcept;

    infix_const_reverse_iterator crend() const noexcept;

    
    prefix_iterator begin_prefix() noexcept;
    
    prefix_iterator end_prefix() noexcept;

    prefix_const_iterator begin_prefix() const noexcept;

    prefix_const_iterator end_prefix() const noexcept;
    
    prefix_const_iterator cbegin_prefix() const noexcept;
    
    prefix_const_iterator cend_prefix() const noexcept;
    
    prefix_reverse_iterator rbegin_prefix() noexcept;
    
    prefix_reverse_iterator rend_prefix() noexcept;

    prefix_const_reverse_iterator rbegin_prefix() const noexcept;

    prefix_const_reverse_iterator rend_prefix() const noexcept;
    
    prefix_const_reverse_iterator crbegin_prefix() const noexcept;
    
    prefix_const_reverse_iterator crend_prefix() const noexcept;

    
    infix_iterator begin_infix() noexcept;
    
    infix_iterator end_infix() noexcept;

    infix_const_iterator begin_infix() const noexcept;

    infix_const_iterator end_infix() const noexcept;
    
    infix_const_iterator cbegin_infix() const noexcept;
    
    infix_const_iterator cend_infix() const noexcept;
    
    infix_reverse_iterator rbegin_infix() noexcept;
    
    infix_reverse_iterator rend_infix() noexcept;

    infix_const_reverse_iterator rbegin_infix() const noexcept;

    infix_const_reverse_iterator rend_infix() const noexcept;
    
    infix_const_reverse_iterator crbegin_infix() const noexcept;
    
    infix_const_reverse_iterator crend_infix() const noexcept;

    
    postfix_iterator begin_postfix() noexcept;
    
    postfix_iterator end_postfix() noexcept;

    postfix_const_iterator begin_postfix() const noexcept;

    postfix_const_iterator end_postfix() const noexcept;
    
    postfix_const_iterator cbegin_postfix() const noexcept;
    
    postfix_const_iterator cend_postfix() const noexcept;
    
    postfix_reverse_iterator rbegin_postfix() noexcept;
    
    postfix_reverse_iterator rend_postfix() noexcept;

    postfix_const_reverse_iterator rbegin_postfix() const noexcept;

    postfix_const_reverse_iterator rend_postfix() const noexcept;
    
    postfix_const_reverse_iterator crbegin_postfix() const noexcept;
    
    postfix_const_reverse_iterator crend_postfix() const noexcept;
    
    // endregion iterators requests definition

protected:



    // region subtree rotations definition
    
    static void small_left_rotation(node *&subtree_root) noexcept;

    static void small_right_rotation(node *&subtree_root) noexcept;

    static void big_left_rotation(node *&subtree_root) noexcept;

    static void big_right_rotation(node *&subtree_root) noexcept;

    static void double_left_rotation(node *&subtree_root) noexcept;

    static void double_right_rotation(node *&subtree_root) noexcept;
    
    // endregion subtree rotations definition
    
};

namespace __detail
{
    template<typename tkey, typename tvalue, typename compare, typename tag>
    class bst_impl
    {
        template<class ...Args>
        static binary_search_tree<tkey, tvalue, compare, tag>::node* create_node(binary_search_tree<tkey, tvalue, compare, tag>& cont, Args&& ...args);

        static void delete_node(binary_search_tree<tkey, tvalue, compare, tag>& cont);

        //Does not invalidate node*, needed for splay tree
        static void post_search(binary_search_tree<tkey, tvalue, compare, tag>::node**){}

        //Does not invalidate node*
        static void post_insert(binary_search_tree<tkey, tvalue, compare, tag>& cont, binary_search_tree<tkey, tvalue, compare, tag>::node**){}

        static void erase(binary_search_tree<tkey, tvalue, compare, tag>& cont, binary_search_tree<tkey, tvalue, compare, tag>::node**);

        static void swap(binary_search_tree<tkey, tvalue, compare, tag>& lhs, binary_search_tree<tkey, tvalue, compare, tag>& rhs) noexcept;
    };
}

template<typename tkey, typename tvalue, typename compare, typename tag>
void __detail::bst_impl<tkey, tvalue, compare, tag>::swap(binary_search_tree<tkey, tvalue, compare, tag> &lhs,
                                                binary_search_tree<tkey, tvalue, compare, tag> &rhs) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, typename compare, typename tag>\n"
                          "void __detail::bst_impl<tkey, tvalue, compare, tag>::swap(binary_search_tree<tkey, tvalue, compare, tag> &lhs,\n"
                          "binary_search_tree<tkey, tvalue, compare, tag> &rhs)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<input_iterator_for_pair<tkey, tvalue> iterator>
binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(iterator begin, iterator end, const compare &cmp,
                                                                   pp_allocator<typename binary_search_tree<tkey, tvalue, compare, tag>::value_type> alloc, logger *logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>\n"
                          "template<input_iterator_for_pair<tkey, tvalue> iterator>\n"
                          "binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(iterator , iterator , const compare &,\n"
                          "pp_allocator<typename binary_search_tree<tkey, tvalue, compare, tag>::value_type> , logger *)", "your code should be here...");
}


template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::compare_pairs(const binary_search_tree::value_type &lhs,
                                                              const binary_search_tree::value_type &rhs) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>\n"
                          "bool binary_search_tree<tkey, tvalue, compare, tag>::compare_pairs(const binary_search_tree::value_type &,\n"
                          "const binary_search_tree::value_type &) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::compare_keys(const tkey &lhs, const tkey &rhs) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>\n"
                          "bool binary_search_tree<tkey, tvalue, compare, tag>::compare_keys(const tkey &, const tkey &) const", "your code should be here...");
}

template<typename compare, typename U, typename iterator>
explicit binary_search_tree(iterator begin, iterator end, const compare& cmp = compare(),
                            pp_allocator<U> alloc = pp_allocator<U>(),
                            logger* logger = nullptr) -> binary_search_tree<const typename std::iterator_traits<iterator>::value_type::first_type, typename std::iterator_traits<iterator>::value_type::second_type, compare>;

template<typename compare, typename U, std::ranges::forward_range Range>
explicit binary_search_tree(Range&& range, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* logger = nullptr) -> binary_search_tree<const typename std::iterator_traits<typename std::ranges::iterator_t<Range>>::value_type::first_type, typename std::iterator_traits<typename std::ranges::iterator_t<Range>>::value_type::second_type, compare> ;

template<typename tkey, typename tvalue, typename compare, typename U>
binary_search_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* logger = nullptr) -> binary_search_tree<tkey, tvalue, compare>;


// region node implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<class ...Args>
binary_search_tree<tkey, tvalue, compare, tag>::node::node(node* parent, Args&& ...args)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> template<class ...Args> binary_search_tree<tkey, tvalue, compare, tag>::node::node(node* , Args&& ...args)", "your code should be here...");
}

// endregion node implementation

// region prefix_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::prefix_iterator(node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::prefix_iterator(node* )", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator==(
        prefix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator==(prefix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator!=(
        prefix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator!=(prefix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator &\n"
"binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator & binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator::depth() const noexcept", "your code should be here...");
}

// endregion prefix_iterator implementation

// region prefix_const_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::prefix_const_iterator(const node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::prefix_const_iterator(const node* data)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::prefix_const_iterator(const prefix_iterator& other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::prefix_const_iterator(const prefix_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator==(
        prefix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator==(prefix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator!=(
        prefix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator!=(prefix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator & binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator & binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator::depth() const noexcept", "your code should be here...");
}

// endregion prefix_const_iterator implementation

// region prefix_reverse_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::prefix_reverse_iterator(node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::prefix_reverse_iterator(node* data)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::prefix_reverse_iterator(const prefix_iterator& it) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::prefix_reverse_iterator(const prefix_iterator& it) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator prefix_iterator() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::base() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::base() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator==(prefix_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator==(prefix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator!=(prefix_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator!=(prefix_reverse_iterator const &other) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator::depth() const noexcept", "your code should be here...");
}

// endregion prefix_reverse_iterator implementation

// region prefix_const_reverse_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(const node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(const node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(const prefix_const_iterator& it) noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::prefix_const_reverse_iterator(const prefix_const_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator() const noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator prefix_const_iterator() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::base() const noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::base() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator==(prefix_const_reverse_iterator const &other) const noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator==(prefix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator!=(prefix_const_reverse_iterator const &other) const noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator!=(prefix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator++() & noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator++(int not_used) noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator--() & noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator--(int not_used) const noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator->() noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::depth() const noexcept
{
throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator::depth() const noexcept", "your code should be here...");
}

// endregion prefix_const_reverse_iterator implementation

// region infix_iterator implementation
template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::infix_iterator(node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::infix_iterator(node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator==(infix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator==(infix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator!=(infix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator!=(infix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator::depth() const noexcept", "your code should be here...");
}

// endregion infix_iterator implementation

// region infix_const_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::infix_const_iterator(const node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::infix_const_iterator(const node* data)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::infix_const_iterator(const infix_iterator& it) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::infix_const_iterator(const infix_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator==(infix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator==(infix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator!=(infix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator!=(infix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator::depth() const noexcept", "your code should be here...");
}

// endregion infix_const_iterator implementation

// region infix_reverse_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::infix_reverse_iterator(node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::infix_reverse_iterator(node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::infix_reverse_iterator(const infix_iterator& it) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::infix_reverse_iterator(const infix_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator infix_iterator() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::base() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::base() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator==(infix_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator==(infix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator!=(infix_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator!=(infix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator::depth() const noexcept", "your code should be here...");
}

// endregion infix_reverse_iterator implementation

// region infix_const_reverse_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::infix_const_reverse_iterator(const node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::infix_const_reverse_iterator(const node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::infix_const_reverse_iterator(const infix_const_iterator& it) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::infix_const_reverse_iterator(const infix_const_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator infix_const_iterator() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::base() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::base() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator==(infix_const_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator==(infix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator!=(infix_const_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator!=(infix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator::depth() const noexcept", "your code should be here...");
}

// endregion infix_const_reverse_iterator implementation

// region postfix_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::postfix_iterator(node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::postfix_iterator(node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator==(postfix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator==(postfix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator!=(postfix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator!=(postfix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator::depth() const noexcept", "your code should be here...");
}

// endregion postfix_iterator implementation

// region postfix_const_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::postfix_const_iterator(const node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::postfix_const_iterator(const node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::postfix_const_iterator(const postfix_iterator& it) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::postfix_const_iterator(const postfix_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator==(postfix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator==(postfix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator!=(postfix_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator!=(postfix_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator::depth() const noexcept", "your code should be here...");
}

// endregion postfix_const_iterator implementation

// region postfix_reverse_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::postfix_reverse_iterator(node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::postfix_reverse_iterator(node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::postfix_reverse_iterator(const postfix_iterator& it) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::postfix_reverse_iterator(const postfix_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator postfix_iterator() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::base() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::base() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator==(postfix_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator==(postfix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator!=(postfix_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator!=(postfix_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator::depth() const noexcept", "your code should be here...");
}

// endregion postfix_reverse_iterator implementation

// region postfix_const_reverse_iterator implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(const node* data)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(const node*)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(const postfix_const_iterator& it) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::postfix_const_reverse_iterator(const postfix_const_iterator&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator postfix_const_iterator() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::base() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::base() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator==(postfix_const_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator==(postfix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator!=(postfix_const_reverse_iterator const &other) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator!=(postfix_const_reverse_iterator const &) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator++() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator++() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator++(int not_used) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator++(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator &
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator--() & noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator & binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator--() & noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator const
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator--(int not_used) const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator const binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator--(int not_used) const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::reference
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator*()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::reference binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator*()", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::pointer
binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator->() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::pointer binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::operator->() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::depth() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator::depth() const noexcept", "your code should be here...");
}

// endregion postfix_const_reverse_iterator implementation

// region binary_search_tree implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(
        const compare& comp,
        pp_allocator<value_type> alloc,
        logger *logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(const compare& ,pp_allocator<value_type> ,logger *)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(
        pp_allocator<value_type> alloc,
        const compare& comp,
        logger *logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(pp_allocator<value_type> , const compare& , logger *)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<std::ranges::input_range Range>
binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(
        Range&& range,
        const compare& cmp,
        pp_allocator<value_type> alloc,
        logger* logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> template<std::ranges::input_range Range> binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(Range&& ,const compare& ,pp_allocator<value_type> ,logger* )", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(
        std::initializer_list<std::pair<tkey, tvalue>> data,
        const compare& cmp,
        pp_allocator<value_type> alloc,
        logger* logger)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(std::initializer_list<std::pair<tkey, tvalue>> ,const compare& ,pp_allocator<value_type> ,logger* )", "your code should be here...");
}

// endregion binary_search_tree implementation

// region binary_search_tree 5_rules implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(const binary_search_tree &other)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(const binary_search_tree &)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(binary_search_tree &&other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::binary_search_tree(binary_search_tree &&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>&
binary_search_tree<tkey, tvalue, compare, tag>::operator=(const binary_search_tree &other)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>& binary_search_tree<tkey, tvalue, compare, tag>::operator=(const binary_search_tree &)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>&
binary_search_tree<tkey, tvalue, compare, tag>::operator=(binary_search_tree &&other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>& binary_search_tree<tkey, tvalue, compare, tag>::operator=(binary_search_tree &&) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
binary_search_tree<tkey, tvalue, compare, tag>::~binary_search_tree()
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> binary_search_tree<tkey, tvalue, compare, tag>::~binary_search_tree()", "your code should be here...");
}

// endregion binary_search_tree 5_rules implementation

// region binary_search_tree methods_access implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
tvalue& binary_search_tree<tkey, tvalue, compare, tag>::at(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> tvalue& binary_search_tree<tkey, tvalue, compare, tag>::at(const tkey&)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
const tvalue& binary_search_tree<tkey, tvalue, compare, tag>::at(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> const tvalue& binary_search_tree<tkey, tvalue, compare, tag>::at(const tkey&) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
tvalue& binary_search_tree<tkey, tvalue, compare, tag>::operator[](const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> tvalue& binary_search_tree<tkey, tvalue, compare, tag>::operator[](const tkey&)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
tvalue& binary_search_tree<tkey, tvalue, compare, tag>::operator[](tkey&& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> tvalue& binary_search_tree<tkey, tvalue, compare, tag>::operator[](tkey&&)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::empty() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::empty() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::size() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::size() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::clear() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::clear() noexcept", "your code should be here...");
}

// endregion binary_search_tree methods_access implementation

// region binary_search_tree methods_insert and methods_emplace implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
std::pair<typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator, bool>
binary_search_tree<tkey, tvalue, compare, tag>::insert(const value_type& value)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> std::pair<typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator, bool> binary_search_tree<tkey, tvalue, compare, tag>::insert(const value_type&)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
std::pair<typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator, bool>
binary_search_tree<tkey, tvalue, compare, tag>::insert(value_type&& value)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> std::pair<typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator, bool> binary_search_tree<tkey, tvalue, compare, tag>::insert(value_type&&)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<std::input_iterator InputIt>
void binary_search_tree<tkey, tvalue, compare, tag>::insert(InputIt first, InputIt last)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> template<std::input_iterator InputIt> void binary_search_tree<tkey, tvalue, compare, tag>::insert(InputIt, InputIt)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<std::ranges::input_range R>
void binary_search_tree<tkey, tvalue, compare, tag>::insert_range(R&& rg)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> template<std::ranges::input_range R> void binary_search_tree<tkey, tvalue, compare, tag>::insert_range(R&&)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<class ...Args>
std::pair<typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator, bool>
binary_search_tree<tkey, tvalue, compare, tag>::emplace(Args&&... args)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> template<class ...Args> std::pair<typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator, bool> binary_search_tree<tkey, tvalue, compare, tag>::emplace(Args&&... args)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::insert_or_assign(const value_type& value)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::insert_or_assign(const value_type& value)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::insert_or_assign(value_type&& value)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::insert_or_assign(value_type&& value)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<std::input_iterator InputIt>
void binary_search_tree<tkey, tvalue, compare, tag>::insert_or_assign(InputIt first, InputIt last)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> template<std::input_iterator InputIt> void binary_search_tree<tkey, tvalue, compare, tag>::insert_or_assign(InputIt first, InputIt last)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
template<class ...Args>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::emplace_or_assign(Args&&... args)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> template<class ...Args> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::emplace_or_assign(Args&&... args)", "your code should be here...");
}

// endregion binary_search_tree methods_insert and methods_emplace implementation

// region binary_search_tree swap_method implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::swap(binary_search_tree& other) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::swap(binary_search_tree&) noexcept", "your code should be here...");
}

// endregion binary_search_tree swap_method implementation

// region binary_search_tree methods_search and methods_erase implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
bool binary_search_tree<tkey, tvalue, compare, tag>::contains(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> bool binary_search_tree<tkey, tvalue, compare, tag>::contains(const tkey&) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::find(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::find(const tkey& )", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::find(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::find(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::lower_bound(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::lower_bound(const tkey& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::lower_bound(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::lower_bound(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::upper_bound(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::upper_bound(const tkey& key)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::upper_bound(const tkey& key) const
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::upper_bound(const tkey& key) const", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_iterator pos)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_iterator pos)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_const_iterator pos)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_const_iterator pos)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_iterator first, infix_iterator last)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_iterator first, infix_iterator last)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_const_iterator first, infix_const_iterator last)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::erase(infix_const_iterator first, infix_const_iterator last)", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
size_t binary_search_tree<tkey, tvalue, compare, tag>::erase(const tkey& key)
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> size_t binary_search_tree<tkey, tvalue, compare, tag>::erase(const tkey& key)", "your code should be here...");
}

// endregion binary_search_tree methods_search and methods_erase implementation

// region infix_iterators requests implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::end() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::end() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cbegin() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cbegin() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cend() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cend() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crbegin() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crbegin() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crend() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crend() const noexcept", "your code should be here...");
}

// endregion infix_iterators requests implementation

// region prefix_iterators requests implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin_prefix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin_prefix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end_prefix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_iterator binary_search_tree<tkey, tvalue, compare, tag>::end_prefix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin_prefix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::end_prefix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cbegin_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cbegin_prefix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cend_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cend_prefix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin_prefix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin_prefix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend_prefix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend_prefix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin_prefix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend_prefix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crbegin_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crbegin_prefix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crend_prefix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::prefix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crend_prefix() const noexcept", "your code should be here...");
}

// endregion prefix_iterators requests implementation

// region infix_iterators methods implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin_infix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin_infix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end_infix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_iterator binary_search_tree<tkey, tvalue, compare, tag>::end_infix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin_infix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::end_infix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cbegin_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cbegin_infix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cend_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cend_infix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin_infix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin_infix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend_infix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend_infix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin_infix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend_infix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crbegin_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crbegin_infix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crend_infix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::infix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crend_infix() const noexcept", "your code should be here...");
}

// endregion infix_iterators methods implementation

// region postfix_iterators requests implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin_postfix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin_postfix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end_postfix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_iterator binary_search_tree<tkey, tvalue, compare, tag>::end_postfix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::begin_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::begin_postfix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::end_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::end_postfix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cbegin_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cbegin_postfix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator
binary_search_tree<tkey, tvalue, compare, tag>::cend_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_iterator binary_search_tree<tkey, tvalue, compare, tag>::cend_postfix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin_postfix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin_postfix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend_postfix() noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend_postfix() noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rbegin_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rbegin_postfix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::rend_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::rend_postfix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crbegin_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crbegin_postfix() const noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator
binary_search_tree<tkey, tvalue, compare, tag>::crend_postfix() const noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> typename binary_search_tree<tkey, tvalue, compare, tag>::postfix_const_reverse_iterator binary_search_tree<tkey, tvalue, compare, tag>::crend_postfix() const noexcept", "your code should be here...");
}

// endregion postfix_iterators requests implementation

// endregion iterators requests implementation

//region subtree rotations implementation

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::small_left_rotation(node *&subtree_root) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::small_left_rotation(node *&subtree_root) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::small_right_rotation(node *&subtree_root) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::small_right_rotation(node *&subtree_root) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::big_left_rotation(node *&subtree_root) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::big_left_rotation(node *&subtree_root) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::big_right_rotation(node *&subtree_root) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::big_right_rotation(node *&subtree_root) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::double_left_rotation(node *&subtree_root) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::double_left_rotation(node *&subtree_root) noexcept", "your code should be here...");
}

template<typename tkey, typename tvalue, compator<tkey> compare, typename tag>
void binary_search_tree<tkey, tvalue, compare, tag>::double_right_rotation(node *&subtree_root) noexcept
{
    throw not_implemented("template<typename tkey, typename tvalue, compator<tkey> compare, typename tag> void binary_search_tree<tkey, tvalue, compare, tag>::double_right_rotation(node *&subtree_root) noexcept", "your code should be here...");
}

//endregion subtree rotations implementation

namespace __detail {
    template<typename tkey, typename tvalue, typename compare, typename tag>
    template<typename ...Args>
    typename binary_search_tree<tkey, tvalue, compare, tag>::node*
    bst_impl<tkey, tvalue, compare, tag>::create_node(binary_search_tree<tkey, tvalue, compare, tag>& cont, Args&& ...args)
    {
        throw not_implemented("template<typename tkey, typename tvalue, typename compare, typename tag>\n"
                              " template<typename ...Args>\n"
                              "typename binary_search_tree<tkey, tvalue, compare, tag>::node*\n"
                              "bst_impl<tkey, tvalue, compare, tag>::create_node(binary_search_tree<tkey, tvalue, compare, tag>& cont, Args&& ...args)", "your code should be here...");
    }

    template<typename tkey, typename tvalue, typename compare, typename tag>
    void bst_impl<tkey, tvalue, compare, tag>::delete_node(binary_search_tree<tkey, tvalue, compare, tag>& cont)
    {
        throw not_implemented("template<typename tkey, typename tvalue, typename compare, typename tag> void bst_impl<tkey, tvalue, compare, tag>::delete_node(binary_search_tree<tkey, tvalue, compare, tag>& cont)", "your code should be here...");
    }

    template<typename tkey, typename tvalue, typename compare, typename tag>
    void bst_impl<tkey, tvalue, compare, tag>::erase(binary_search_tree<tkey, tvalue, compare, tag>& cont, typename binary_search_tree<tkey, tvalue, compare, tag>::node** node_ptr)
    {
        throw not_implemented("template<typename tkey, typename tvalue, typename compare, typename tag> void bst_impl<tkey, tvalue, compare, tag>::erase(binary_search_tree<tkey, tvalue, compare, tag>& cont, typename binary_search_tree<tkey, tvalue, compare, tag>::node** node_ptr)", "your code should be here...");
    }
}

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H