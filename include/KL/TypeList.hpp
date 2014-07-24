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

    template <unsigned Pos>
    using At = typename InternalAt::impl<Pos, Pack...>::type;

    using Front = typename InternalFront::impl<Pack...>::type;

    using Back = typename InternalBack::impl<Pack...>::type;

    template <typename Element>
    using PushFront = typename InternalPushFront::impl<Element, Pack...>::type;

};

template <>
class TypeList<> : public InternalTypeList<TypeList>
{

public:
    template <typename ValueType = unsigned>
    using Size = std::integral_constant<ValueType, 0>;

    using Empty = std::true_type;

    template <typename Element>
    using Contains = std::false_type;

    template <typename Element, typename ValueType = unsigned>
    using Count = std::integral_constant<ValueType, 0>;

    template <typename Element>
    using PushFront = TypeList<Element>;

};

} // namespace KL

#endif // KL_TYPE_LIST
