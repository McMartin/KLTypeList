// Copyright (c) 2014 Alain Martin

#ifndef KL_INTERNAL_TYPE_LIST
#define KL_INTERNAL_TYPE_LIST

namespace KL
{

template <template <typename...> class List>
class InternalTypeList
{

protected:
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
