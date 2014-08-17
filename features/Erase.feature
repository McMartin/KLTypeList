Erase<Integer> -> TypeList

TypeList<>::Erase<0> NOT COMPILE

TypeList<A>::Erase<0> == TypeList<>
TypeList<A>::Erase<1> NOT COMPILE

TypeList<A, A>::Erase<0> == TypeList<A>
TypeList<A, A>::Erase<1> == TypeList<A>
TypeList<A, A>::Erase<2> NOT COMPILE

TypeList<A, B>::Erase<0> == TypeList<B>
TypeList<A, B>::Erase<1> == TypeList<A>
TypeList<A, B>::Erase<2> NOT COMPILE

TypeList<A, A, A>::Erase<0> == TypeList<A, A>
TypeList<A, A, A>::Erase<1> == TypeList<A, A>
TypeList<A, A, A>::Erase<2> == TypeList<A, A>
TypeList<A, A, A>::Erase<3> NOT COMPILE

TypeList<A, A, B>::Erase<0> == TypeList<A, B>
TypeList<A, A, B>::Erase<1> == TypeList<A, B>
TypeList<A, A, B>::Erase<2> == TypeList<A, A>
TypeList<A, A, B>::Erase<3> NOT COMPILE

TypeList<A, B, A>::Erase<0> == TypeList<B, A>
TypeList<A, B, A>::Erase<1> == TypeList<A, A>
TypeList<A, B, A>::Erase<2> == TypeList<A, B>
TypeList<A, B, A>::Erase<3> NOT COMPILE

TypeList<A, B, B>::Erase<0> == TypeList<B, B>
TypeList<A, B, B>::Erase<1> == TypeList<A, B>
TypeList<A, B, B>::Erase<2> == TypeList<A, B>
TypeList<A, B, B>::Erase<3> NOT COMPILE

TypeList<A, B, C>::Erase<0> == TypeList<B, C>
TypeList<A, B, C>::Erase<1> == TypeList<A, C>
TypeList<A, B, C>::Erase<2> == TypeList<A, B>
TypeList<A, B, C>::Erase<3> NOT COMPILE
