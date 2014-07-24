// Copyright (c) 2014 Alain Martin

#ifndef KL_TYPE_LIST
#define KL_TYPE_LIST

#include "internal/InternalTypeList.hpp"

namespace KL
{

template <typename... Pack>
class TypeList : public InternalTypeList<TypeList>
{

public:
    static const unsigned Size = InternalSize::impl<Pack...>::value;

    static const bool Empty = InternalEmpty::impl<Pack...>::value;

    template <typename Element>
    static constexpr bool Contains()
    {
        return InternalContains::impl<Element, Pack...>::value;
    }

};

} // namespace KL

#endif // KL_TYPE_LIST
