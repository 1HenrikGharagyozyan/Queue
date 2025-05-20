#pragma once
#include <deque>
#include <utility>
#include <stdexcept>
#include <type_traits>

template <typename _Ty, typename _Container = std::deque<_Ty>>
class Queue
{
public:
    using value_type = typename _Container::value_type;
    using reference = typename _Container::reference;
    using const_reference = typename _Container::const_reference;
    using size_type = typename _Container::size_type;
    using container_type = _Container;

    Queue();
    explicit Queue(const _Container& cont);
    explicit Queue(_Container&& cont) noexcept(std::is_nothrow_move_constructible<_Container>::value);
    Queue(const Queue&);
    Queue(Queue&&) noexcept(std::is_nothrow_move_constructible<_Container>::value);

    Queue& operator=(const Queue&);
    Queue& operator=(Queue&&) noexcept(std::is_nothrow_move_assignable<_Container>::value);

    // Элементы доступа
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // Ёмкость
    bool empty() const noexcept;
    size_type size() const noexcept;

    // Модификация
    void push(const value_type& value);
    void push(value_type&& value) noexcept(std::is_nothrow_move_constructible<value_type>::value);

    template <typename... Args>
    decltype(auto) emplace(Args&&... args);

    void pop();

    void swap(Queue& other) noexcept(noexcept(std::swap(c, other.c)));

    // Доступ к контейнеру (можно удалить, если не нужен)
    const _Container& container() const noexcept;
    _Container& container() noexcept;

    template<typename U, typename Cont>
    friend bool operator==(const Queue<U, Cont>& lhs, const Queue<U, Cont>& rhs);

    template<typename U, typename Cont>
    friend bool operator!=(const Queue<U, Cont>& lhs, const Queue<U, Cont>& rhs);

protected:
	_Container c{};
};

template<typename _Ty, typename _Container>
inline Queue<_Ty, _Container>::Queue() = default;

template<typename _Ty, typename _Container>
inline Queue<_Ty, _Container>::Queue(const _Container& cont)
    : c(cont) 
{
}

template<typename _Ty, typename _Container>
inline Queue<_Ty, _Container>::Queue(_Container&& cont) noexcept(std::is_nothrow_move_constructible<_Container>::value)
    : c(std::move(cont)) 
{
}

template<typename _Ty, typename _Container>
inline Queue<_Ty, _Container>::Queue(const Queue&) = default;

template<typename _Ty, typename _Container>
inline Queue<_Ty, _Container>::Queue(Queue&&) noexcept(std::is_nothrow_move_constructible<_Container>::value) = default;

template<typename _Ty, typename _Container>
inline Queue<_Ty, _Container>& Queue<_Ty, _Container>::operator=(const Queue&) = default;

template<typename _Ty, typename _Container>
inline Queue<_Ty, _Container>& Queue<_Ty, _Container>::operator=(Queue&&)
        noexcept(std::is_nothrow_move_assignable<_Container>::value) = default;

template<typename _Ty, typename _Container>
typename Queue<_Ty, _Container>::reference Queue<_Ty, _Container>::front()
{
    if (c.empty())
        throw std::out_of_range("queue::front(): empty queue");
    return c.front();
}

template<typename _Ty, typename _Container>
typename Queue<_Ty, _Container>::const_reference Queue<_Ty, _Container>::front() const
{
    if (c.empty())
        throw std::out_of_range("queue::front(): empty queue");
    return c.front();
}

template<typename _Ty, typename _Container>
typename Queue<_Ty, _Container>::reference Queue<_Ty, _Container>::back()
{
    if (c.empty())
        throw std::out_of_range("queue::back(): empty queue");
    return c.back();
}

template<typename _Ty, typename _Container>
typename Queue<_Ty, _Container>::const_reference Queue<_Ty, _Container>::back() const
{
    if (c.empty())
        throw std::out_of_range("queue::back(): empty queue");
    return c.back();
}

template<typename _Ty, typename _Container>
inline bool Queue<_Ty, _Container>::empty() const noexcept
{
    return c.empty();
}

template<typename _Ty, typename _Container>
typename Queue<_Ty, _Container>::size_type Queue<_Ty, _Container>::size() const noexcept
{
    return c.size();
}

template<typename _Ty, typename _Container>
inline void Queue<_Ty, _Container>::push(const value_type& value)
{
    c.push_back(value);
}

template<typename _Ty, typename _Container>
inline void Queue<_Ty, _Container>::push(value_type&& value) noexcept(std::is_nothrow_move_constructible<value_type>::value)
{
    c.push_back(std::move(value));
}

template<typename _Ty, typename _Container>
inline void Queue<_Ty, _Container>::pop()
{
    if (c.empty())
        throw std::out_of_range("queue::pop(): empty queue");
    c.pop_front();
}

template<typename _Ty, typename _Container>
inline void Queue<_Ty, _Container>::swap(Queue& other) noexcept(noexcept(std::swap(c, other.c)))
{
    using std::swap;
    swap(c, other.c);
}

template<typename _Ty, typename _Container>
inline const _Container& Queue<_Ty, _Container>::container() const noexcept
{
    return c;
}

template<typename _Ty, typename _Container>
inline _Container& Queue<_Ty, _Container>::container() noexcept
{
    return c;
}

template<typename _Ty, typename _Container>
template<typename ...Args>
inline decltype(auto) Queue<_Ty, _Container>::emplace(Args && ...args)
{
    return c.emplace_back(std::forward<Args>(args)...);
}


// Специализация std::swap для Queue
template <typename T, typename _Container>
void swap(Queue<T, _Container>& lhs, Queue<T, _Container>& rhs) noexcept(noexcept(lhs.swap(rhs))) 
{
    lhs.swap(rhs);
}

template<typename U, typename Cont>
inline bool operator==(const Queue<U, Cont>& lhs, const Queue<U, Cont>& rhs)
{
    return lhs.c == rhs.c;
}

template<typename U, typename Cont>
inline bool operator!=(const Queue<U, Cont>& lhs, const Queue<U, Cont>& rhs)
{
    return lhs.c != rhs.c;
}
