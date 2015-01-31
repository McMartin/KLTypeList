// Copyright (c) 2014 Alain Martin

#ifndef KL_INTERNAL_TYPE_LIST
#define KL_INTERNAL_TYPE_LIST

#include <type_traits>

namespace KL
{

template <template <typename...> class List>
struct InternalTypeList
{
    using size_type = std::size_t;

    struct Null {};

protected:
    struct InternalAt
    {
        template <size_type Pos, typename, typename... Tail>
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

    struct InternalErase
    {
        template <size_type First, size_type Last, typename Head, typename... Tail>
        struct impl
        {
            static_assert(First <= Last, "'First' is out of range");

            using type = typename InternalConcat::template impl<
                List<Head>,
                typename impl<First - 1, Last - 1, Tail...>::type
            >::type;
        };

        template <size_type Last, typename Head, typename... Tail>
        struct impl<0, Last, Head, Tail...>
        {
            static_assert(sizeof...(Tail) + 1 > Last, "'Last' is out of range");

            using type = typename impl<0, Last - 1, Tail...>::type;
        };

        template <typename Head, typename... Tail>
        struct impl<0, 0, Head, Tail...>
        {
            using type = List<Tail...>;
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

    struct InternalInsert
    {
        template <size_type, typename, typename...>
        struct impl;

        template <size_type Pos, typename Element, typename Head, typename... Tail>
        struct impl<Pos, Element, Head, Tail...>
        {
            static_assert(Pos <= 1 + sizeof...(Tail), "ERROR: 'Pos' is out of range");

            using type = typename InternalConcat::template impl<
                List<Head>,
                typename impl<Pos - 1, Element, Tail...>::type
            >::type;
        };

        template <typename Element, typename Head, typename... Tail>
        struct impl<0, Element, Head, Tail...>
        {
            using type = List<Element, Head, Tail...>;
        };

        template <size_type Pos, typename Element>
        struct impl<Pos, Element>
        {
            static_assert(Pos == 0, "ERROR: 'Pos' is out of range");

            using type = List<Element>;
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

    struct InternalPopBack
    {
        template <typename Head, typename... Tail>
        struct impl
        {
            using type = typename InternalConcat::template impl<
                List<Head>,
                typename impl<Tail...>::type
            >::type;
        };

        template <typename Head>
        struct impl<Head>
        {
            using type = List<>;
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

    struct InternalRepeat
    {
        template <size_type Count, typename Element>
        struct impl
        {
            using type = typename InternalConcat::template impl<
                List<Element>,
                typename impl<Count - 1, Element>::type
            >::type;
        };

        template <typename Element>
        struct impl<0, Element>
        {
            using type = List<>;
        };
    };

    struct InternalResize
    {
        template <size_type Count, typename... Pack>
        struct impl_no_element;

        template <size_type Count, typename Head, typename... Tail>
        struct impl_no_element<Count, Head, Tail...>
        {
            static_assert(Count <= 1 + sizeof...(Tail), "ERROR: 'Count' is out of range");

            using type = typename InternalConcat::template impl<
                List<Head>,
                typename impl_no_element<Count - 1, Tail...>::type
            >::type;
        };

        template <typename Head, typename... Tail>
        struct impl_no_element<0, Head, Tail...>
        {
            using type = List<>;
        };

        template <size_type Count>
        struct impl_no_element<Count>
        {
            static_assert(Count == 0, "ERROR: 'Count' is out of range");

            using type = List<>;
        };

        template <typename ValueType, ValueType Value, ValueType Min, ValueType Max>
        struct clamp
        {
            static const ValueType value = Value < Min ? Min : Value > Max ? Max : Value;
        };

        template <size_type Count, typename Element, typename... Pack>
        struct impl
        {
            using type = typename std::conditional<
                Count <= sizeof...(Pack),
                typename impl_no_element<
                    clamp<size_type, Count, 0, sizeof...(Pack)>::value,
                    Pack...
                >::type,
                typename InternalConcat::template impl<
                    List<Pack...>,
                    typename InternalRepeat::template impl<
                        clamp<size_type, Count - sizeof...(Pack), 0, Count>::value,
                        Element
                    >::type
                >::type
            >::type;
        };

        template <size_type Count, typename... Pack>
        struct impl<Count, Null, Pack...>
        {
            using type = typename impl_no_element<Count, Pack...>::type;
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
