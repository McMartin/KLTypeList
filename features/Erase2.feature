Erase<Integer, Integer> -> TypeList

TypeList<>::Erase<0, 0> == TypeList<>
TypeList<>::Erase<0, 1> NOT COMPILE

TypeList<A>::Erase<0, 0> == TypeList<A>
TypeList<A>::Erase<0, 1> == TypeList<>
TypeList<A>::Erase<1, 0> NOT COMPILE
TypeList<A>::Erase<1, 1> == TypeList<A>
TypeList<A>::Erase<0, 2> NOT COMPILE

TypeList<A, A>::Erase<0, 0> == TypeList<A, A>
TypeList<A, A>::Erase<0, 1> == TypeList<A>
TypeList<A, A>::Erase<0, 2> == TypeList<>
TypeList<A, A>::Erase<0, 3> NOT COMPILE

TypeList<A, A>::Erase<1, 0> NOT COMPILE
TypeList<A, A>::Erase<1, 1> == TypeList<A, A>
TypeList<A, A>::Erase<1, 2> == TypeList<A>
TypeList<A, A>::Erase<1, 3> NOT COMPILE

TypeList<A, A>::Erase<2, 0> NOT COMPILE
TypeList<A, A>::Erase<2, 1> NOT COMPILE
TypeList<A, A>::Erase<2, 2> == TypeList<A, A>
TypeList<A, A>::Erase<2, 3> NOT COMPILE

TypeList<A, B>::Erase<0, 0> == TypeList<A, B>
TypeList<A, B>::Erase<0, 1> == TypeList<B>
TypeList<A, B>::Erase<0, 2> == TypeList<>
TypeList<A, B>::Erase<0, 3> NOT COMPILE

TypeList<A, B>::Erase<1, 0> NOT COMPILE
TypeList<A, B>::Erase<1, 1> == TypeList<A, B>
TypeList<A, B>::Erase<1, 2> == TypeList<A>
TypeList<A, B>::Erase<1, 3> NOT COMPILE

TypeList<A, B>::Erase<2, 0> NOT COMPILE
TypeList<A, B>::Erase<2, 1> NOT COMPILE
TypeList<A, B>::Erase<2, 2> == TypeList<A, B>
TypeList<A, B>::Erase<2, 3> NOT COMPILE
