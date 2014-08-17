Erase<Integer> -> TypeList

TypeList<>::Erase<0, 0> NOT COMPILE

TypeList<A>::Erase<0, 0> == TypeList<>
TypeList<A>::Erase<0, 1> NOT COMPILE
TypeList<A>::Erase<1, 0> NOT COMPILE
TypeList<A>::Erase<1, 1> NOT COMPILE

TypeList<A, A>::Erase<0, 0> == TypeList<A>
TypeList<A, A>::Erase<0, 1> == TypeList<>
TypeList<A, A>::Erase<0, 2> NOT COMPILE

TypeList<A, A>::Erase<1, 0> NOT COMPILE
TypeList<A, A>::Erase<1, 1> == TypeList<A>
TypeList<A, A>::Erase<1, 2> NOT COMPILE

TypeList<A, A>::Erase<2, 0> NOT COMPILE
TypeList<A, A>::Erase<2, 1> NOT COMPILE
TypeList<A, A>::Erase<2, 2> NOT COMPILE

TypeList<A, B>::Erase<0, 0> == TypeList<B>
TypeList<A, B>::Erase<0, 1> == TypeList<>
TypeList<A, B>::Erase<0, 2> NOT COMPILE

TypeList<A, B>::Erase<1, 0> NOT COMPILE
TypeList<A, B>::Erase<1, 1> == TypeList<A>
TypeList<A, B>::Erase<1, 2> NOT COMPILE

TypeList<A, B>::Erase<2, 0> NOT COMPILE
TypeList<A, B>::Erase<2, 1> NOT COMPILE
TypeList<A, B>::Erase<2, 2> NOT COMPILE
