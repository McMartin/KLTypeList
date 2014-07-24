// Copyright (c) 2014 Alain Martin

#ifndef KL_INTERNAL_TYPE_LIST
#define KL_INTERNAL_TYPE_LIST

namespace KL
{

template <template <typename...> class List>
class InternalTypeList
{

protected:
    struct InternalContains
    {
        template <typename, typename...>
        struct impl
        {
            static const bool value = false;
        };

        template <typename Element, typename Head, typename... Tail>
        struct impl<Element, Head, Tail...>
        {
            static const bool value = impl<Element, Tail...>::value;
        };

        template <typename Element, typename... Tail>
        struct impl<Element, Element, Tail...>
        {
            static const bool value = true;
        };
    };

    struct InternalCount
    {
        template <typename, typename...>
        struct impl
        {
            static const unsigned value = 0;
        };

        template <typename Element, typename Head, typename... Tail>
        struct impl<Element, Head, Tail...>
        {
            static const unsigned value = impl<Element, Tail...>::value;
        };

        template <typename Element, typename... Tail>
        struct impl<Element, Element, Tail...>
        {
            static const unsigned value = 1 + impl<Element, Tail...>::value;
        };
    };

    struct InternalEmpty
    {
        template <typename... Pack>
        struct impl
        {
            static const bool value = (sizeof...(Pack) == 0);
        };
    };

    struct InternalSize
    {
        template <typename... Pack>
        struct impl
        {
            static const unsigned value = sizeof...(Pack);
        };
    };

};

} // namespace KL

#endif // KL_INTERNAL_TYPE_LIST
