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
    template <typename ValueType = unsigned>
    using Size = typename InternalSize::impl<ValueType, Pack...>::type;

    using Empty = typename InternalEmpty::impl<Pack...>::type;

    template <typename Element>
    using Contains = typename InternalContains::impl<Element, Pack...>::type;

    template <typename Element, typename ValueType = unsigned>
    using Count = typename InternalCount::impl<ValueType, Element, Pack...>::type;

};

} // namespace KL

#endif // KL_TYPE_LIST
