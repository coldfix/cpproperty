#ifndef __VFUNC_H__INCLUDED__
#define __VFUNC_H__INCLUDED__

#include <memory>


template <class Sig>
class VirtualFunctionBase;

template <class R, class... P>
class VirtualFunctionBase<R(P...)>
{
public:
    virtual R operator() (P...) const = 0;
};

template <class Fn, class R, class... P>
class VirtualFunctionImpl
    : public VirtualFunctionBase<R(P...)>
{
    Fn fn;
public:
    VirtualFunctionImpl(Fn fn)
        : fn(fn)
    {
    }

    virtual R operator() (P... p) const
    {
        return fn(p...);
    }
};


// convenience layer using the PIMPL idiom:

template <class Sig>
class VirtualFunction;

template <class R, class... P>
class VirtualFunction<R(P...)>
{
    std::shared_ptr<VirtualFunctionBase<R(P...)>> pimpl;
public:

    template <class Fn>
    VirtualFunction(Fn fn)
        : pimpl(new VirtualFunctionImpl<Fn, R, P...>(fn))
    {
    }

    R operator() (P... p) const
    {
        return (*pimpl)(p...);
    }
};

#endif // include guard
