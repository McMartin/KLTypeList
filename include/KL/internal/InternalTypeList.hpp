// Copyright (c) 2014 Alain Martin

#ifndef KL_INTERNAL_TYPE_LIST
#define KL_INTERNAL_TYPE_LIST

#include <type_traits>

namespace KL
{

template <template <typename...> class List>
class InternalTypeList
{

protected:
    struct InternalAt
    {
        template <unsigned Pos, typename, typename... Tail>
        struct impl
        {
            static_assert(sizeof...(Tail) + 1 > Pos, "'Pos' is out of range");

            using type = typename impl<Pos - 1, Tail...>::type;
        };

        template <typename Head, typename... Tail>
        struct impl<0, Head, Tail...>
        {
            using type = Head;
        };
    };

    struct InternalBack
    {
        template <typename, typename... Tail>
        struct impl
        {
            using type = typename impl<Tail...>::type;
        };

        template <typename Head>
        struct impl<Head>
        {
            using type = Head;
        };
    };

    struct InternalConcat
    {
        template <typename, typename>
        struct impl;

        template <typename... LeftPack, typename... RightPack>
        struct impl<List<LeftPack...>, List<RightPack...>>
        {
            using type = List<LeftPack..., RightPack...>;
        };
    };

    struct InternalContains
    {
        template <typename, typename...>
        struct impl
        {
            using type = std::false_type;
        };

        template <typename Element, typename Head, typename... Tail>
        struct impl<Element, Head, Tail...>
        {
            using type = typename impl<Element, Tail...>::type;
        };

        template <typename Element, typename... Tail>
        struct impl<Element, Element, Tail...>
        {
            using type = std::true_type;
        };
    };

    struct InternalCount
    {
        template <typename ValueType, typename, typename...>
        struct impl
        {
            using type = std::integral_constant<ValueType, 0>;
        };

        template <typename ValueType, typename Element, typename Head, typename... Tail>
        struct impl<ValueType, Element, Head, Tail...>
        {
            using type = typename impl<ValueType, Element, Tail...>::type;
        };

        template <typename ValueType, typename Element, typename... Tail>
        struct impl<ValueType, Element, Element, Tail...>
        {
            using type = std::integral_constant<
                ValueType,
                1 + impl<ValueType, Element, Tail...>::type::value
            >;
        };
    };

    struct InternalEmpty
    {
        template <typename... Pack>
        struct impl
        {
            using type = std::integral_constant<bool, (sizeof...(Pack) == 0)>;
        };
    };

    struct InternalFront
    {
        template <typename Head, typename...>
        struct impl
        {
            using type = Head;
        };
    };

    struct InternalPopFront
    {
        template <typename Head, typename... Tail>
        struct impl
        {
            using type = List<Tail...>;
        };
    };

    struct InternalPushBack
    {
        template <typename Element, typename... Pack>
        struct impl
        {
            using type = List<Pack..., Element>;
        };
    };

    struct InternalPushFront
    {
        template <typename Element, typename... Pack>
        struct impl
        {
            using type = List<Element, Pack...>;
        };
    };

    struct InternalSize
    {
        template <typename ValueType, typename... Pack>
        struct impl
        {
            using type = std::integral_constant<ValueType, sizeof...(Pack)>;
        };
    };

};

} // namespace KL

#endif // KL_INTERNAL_TYPE_LIST
