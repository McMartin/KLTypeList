// Copyright (c) 2014-2016 Alain Martin

#ifndef KL_TYPE_LIST
#define KL_TYPE_LIST

#include "internal/InternalTypeList.hpp"

namespace KL
{

template <typename... Pack>
struct TypeList : public InternalTypeList<TypeList>
{
    template <typename ValueType = size_type>
    using Size = typename InternalSize::impl<ValueType, Pack...>::type;

    using Empty = typename InternalEmpty::impl<Pack...>::type;

    template <typename Element>
    using Contains = typename InternalContains::impl<Element, Pack...>::type;

    template <typename Element, typename ValueType = size_type>
    using Count = typename InternalCount::impl<ValueType, Element, Pack...>::type;

    template <size_type Pos>
    using At = typename InternalAt::impl<Pos, Pack...>::type;

    using Front = typename InternalFront::impl<Pack...>::type;

    using Back = typename InternalBack::impl<Pack...>::type;

    template <typename Element>
    using PushFront = typename InternalPushFront::impl<Element, Pack...>::type;

    template <typename Element>
    using PushBack = typename InternalPushBack::impl<Element, Pack...>::type;

    using PopFront = typename InternalPopFront::impl<Pack...>::type;

    using PopBack = typename InternalPopBack::impl<Pack...>::type;

    template <size_type First, size_type Last = First + 1>
    using Erase = typename InternalErase::impl<First, Last, Pack...>::type;

    template <size_type Pos, typename Element>
    using Insert = typename InternalInsert::impl<Pos, Element, Pack...>::type;

    using Clear = TypeList<>;

    template <size_type Count, typename Element = Null>
    using Resize = typename InternalResize::impl<Count, Element, Pack...>::type;

    using Reverse = typename InternalReverse::impl<Pack...>::type;
};

template <>
struct TypeList<> : public InternalTypeList<TypeList>
{
    template <typename ValueType = size_type>
    using Size = std::integral_constant<ValueType, 0>;

    using Empty = std::true_type;

    template <typename Element>
    using Contains = std::false_type;

    template <typename Element, typename ValueType = size_type>
    using Count = std::integral_constant<ValueType, 0>;

    template <typename Element>
    using PushFront = TypeList<Element>;

    template <typename Element>
    using PushBack = TypeList<Element>;

    template <size_type First, size_type Last = First + 1>
    using Erase = typename InternalErase::impl<First, Last>::type;

    template <size_type Pos, typename Element>
    using Insert = typename InternalInsert::impl<Pos, Element>::type;

    using Clear = TypeList<>;

    template <size_type Count, typename Element = Null>
    using Resize = typename InternalResize::impl<Count, Element>::type;

    using Reverse = TypeList<>;
};

} // namespace KL

#endif // KL_TYPE_LIST
