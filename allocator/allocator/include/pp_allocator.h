//
// Created by Des Caldnd on 6/29/2024.
//

#ifndef SYS_PROG_PP_ALLOCATOR_H
#define SYS_PROG_PP_ALLOCATOR_H

#include <memory_resource>
#include <memory>

struct smart_mem_resource : public std::pmr::memory_resource
{
private:
    virtual void do_deallocate_sm(void*) =0;

    void do_deallocate(void* p, size_t, size_t) final;

    virtual void* do_allocate_sm(size_t) =0;

    void * do_allocate(size_t _Bytes, size_t _Align) final;
};



struct test_mem_resource : public smart_mem_resource
{
private:

    void* do_allocate_sm(size_t n) override;
    void do_deallocate_sm(void* p) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

// propagating_polymorphic_allocator
template <typename T>
struct pp_allocator
{
private:
    std::pmr::memory_resource* _mem;

public:

    using propagate_on_container_swap = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using value_type = T;

    pp_allocator(const pp_allocator& other) noexcept =default;
    pp_allocator(std::pmr::memory_resource* mem = std::pmr::get_default_resource()) noexcept;

    template<class U>
    pp_allocator(const pp_allocator<U>& other) noexcept;

    pp_allocator& operator=(const pp_allocator&) =default;
    pp_allocator& operator=(pp_allocator&&) noexcept =default;
    ~pp_allocator() =default;

    [[nodiscard]] T* allocate(size_t n);
    void deallocate(T* p, size_t n = 1);

    template<class U, class... Args>
    void construct(U* p, Args&&... args);

    template<class U>
    void destroy(U* p);

    [[nodiscard]] void* allocate_bytes(size_t nbytes, size_t alignment = alignof(std::max_align_t));

    void deallocate_bytes(void* p, size_t bytes = 1, size_t alignment = alignof(std::max_align_t));

    template< class U >
    [[nodiscard]] U* allocate_object( std::size_t n = 1 );

    template< class U >
    void deallocate_object( U* p, std::size_t n = 1 );

    template< class U, class... CtorArgs >
    [[nodiscard]] U* new_object( CtorArgs&&... ctor_args );

    template< class U >
    void delete_object( U* p );

    pp_allocator select_on_container_copy_construction() const;

    std::pmr::memory_resource* resource() const;


};

template<typename T>
bool operator==(const pp_allocator<T>& lhs, const pp_allocator<T>& rhs) noexcept
{
    return *lhs.resource() == *rhs.resource();
}

template<typename T>
bool operator!=(const pp_allocator<T>& lhs, const pp_allocator<T>& rhs) noexcept
{
    return !(lhs == rhs);
}

template<typename T>
pp_allocator<T>::pp_allocator(std::pmr::memory_resource *mem) noexcept : _mem(mem == nullptr ? std::pmr::get_default_resource() : mem) {}

template<typename T>
std::pmr::memory_resource *pp_allocator<T>::resource() const
{
    return _mem;
}

template<typename T>
pp_allocator<T> pp_allocator<T>::select_on_container_copy_construction() const
{
    return pp_allocator(resource());
}

template<typename T>
template<class U>
void pp_allocator<T>::delete_object(U *p)
{
    destroy(p);
    deallocate_object(p);
}

template<typename T>
template<class U, class... CtorArgs>
U *pp_allocator<T>::new_object(CtorArgs &&... ctor_args)
{
    U* p = allocate_object<U>();
    try
    {
        construct(p, std::forward<CtorArgs>(ctor_args)...);
    }
    catch (...)
    {
        deallocate_object(p);
        throw;
    }
    return p;
}

template<typename T>
template<class U>
void pp_allocator<T>::deallocate_object(U *p, std::size_t n)
{
    deallocate_bytes(p, n * sizeof(U), alignof(U));
}

template<typename T>
template<class U>
U *pp_allocator<T>::allocate_object(std::size_t n)
{
    if ((std::numeric_limits<size_t>::max() / sizeof(U)) < n)
        throw std::bad_array_new_length();
    return reinterpret_cast<U*>(allocate_bytes(n * sizeof(U), alignof(U)));
}

template<typename T>
void pp_allocator<T>::deallocate_bytes(void *p, size_t bytes, size_t alignment)
{
    resource()->deallocate(p, bytes, alignment);
}

template<typename T>
void *pp_allocator<T>::allocate_bytes(size_t nbytes, size_t alignment)
{
    return resource()->allocate(nbytes, alignment);
}

template<typename T>
template<class U>
void pp_allocator<T>::destroy(U *p)
{
    p->~U();
}

template<typename T>
template<class U, class... Args>
void pp_allocator<T>::construct(U *p, Args &&... args)
{
    std::uninitialized_construct_using_allocator(p, *this, std::forward<Args>(args)...);
}

template<typename T>
void pp_allocator<T>::deallocate(T *p, size_t n)
{
    _mem->deallocate(p, n * sizeof(T), alignof(T));
}

template<typename T>
T *pp_allocator<T>::allocate(size_t n)
{
    return reinterpret_cast<T*>(_mem->allocate(n * sizeof(T), alignof(T)));
}

template <typename T>
template <typename U>
pp_allocator<T>::pp_allocator(const pp_allocator<U>& other) noexcept : _mem(other.resource())
{}



#endif //SYS_PROG_PP_ALLOCATOR_H
