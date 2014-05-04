#pragma once

#include <memory>
#include <llvm/ADT/OwningPtr.h>
#include <llvm/ADT/IntrusiveRefCntPtr.h>

namespace std
{
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}

template<typename T, typename ...Args>
llvm::OwningPtr<T> make_owning(Args&& ...args)
{
    return llvm::OwningPtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T, typename ...Args>
llvm::IntrusiveRefCntPtr<T> make_intrusive(Args&& ...args)
{
    return llvm::IntrusiveRefCntPtr<T>(new T(std::forward<Args>(args)...));
}
