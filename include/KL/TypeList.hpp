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

    using Empty = typename InternalEmpty::impl<Pack...>::type;

    template <typename Element>
    using Contains = typename InternalContains::impl<Element, Pack...>::type;

    template <typename Element>
    static constexpr unsigned Count()
    {
        return InternalCount::impl<Element, Pack...>::value;
    }

};

} // namespace KL

#endif // KL_TYPE_LIST
