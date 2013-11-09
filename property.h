#ifndef __PROPERTY_H__INCLUDED__
#define __PROPERTY_H__INCLUDED__

#include "vfunc.h"


template <class T>
using getter_function = const T&(void);

template <class T>
using setter_function = void(const T&);

template <class T, class C>
using setter_method = void (C::*) (const T&);

template <class T, class C>
using getter_method = const T& (C::*) () const;


template <class T>
class property
{

    VirtualFunction<getter_function<T>> _get;
    VirtualFunction<setter_function<T>> _set;

public:
    property() = delete;

    template <class G, class S>
    property(G get, S set)
        : _get(get)
        , _set(set)
    {
    }

    template <class C>
    property(C* const obj, getter_method<T, C> get, setter_method<T, C> set)
        : _get([obj, get]() -> const T& { return (obj->*get)(); })
        , _set([obj, set](const T& v) { (obj->*set)(v); })
    {
    }

    const T* operator->() const
    {
        return &_get();
    }

    const T& operator*() const
    {
        return _get();
    }

    property& operator=(const T& value)
    {
        _set(value);
        return *this;
    }
};

template <class T, class C,
          getter_method<T, C> get,
          setter_method<T, C>... set>
class std_property;

template <class T, class C,
          getter_method<T, C> get,
          setter_method<T, C> set>
class std_property<T, C, get, set>
{
    C* _owner;
public:
    std_property() = delete;

    std_property(C* owner)
        : _owner(owner)
    {
    }

    const T* operator->() const
    {
        return &(_owner->*get)();
    }

    const T& operator*() const
    {
        return (_owner->*get)();
    }

    std_property& operator=(const T& value)
    {
        (_owner->*set)(value);
        return *this;
    }
};

//----------------------------------------
// template <class T, class C,
//           setter_method<T, C> set>
// class std_property<T, C, set>
// {
//     C* _owner;
// public:
//     std_property() = delete;
// 
//     std_property(C* owner)
//         : _owner(owner)
//     {
//     }
// 
//     std_property& operator=(const T& value)
//     {
//         (_owner->*set)(value);
//         return *this;
//     }
// };
//----------------------------------------

template <class T, class C,
          getter_method<T, C> get>
class std_property<T, C, get>
{
    C* _owner;
public:
    std_property() = delete;

    std_property(C* owner)
        : _owner(owner)
    {
    }

    const T* operator->() const
    {
        return &(_owner->*get)();
    }

    const T& operator*() const
    {
        return (_owner->*get)();
    }
};


#endif // include guard
