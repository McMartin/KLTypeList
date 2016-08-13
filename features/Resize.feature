# Copyright (c) 2015-2016 Alain Martin

Resize<Integer> -> TypeList

TypeList<>::Resize<0> == TypeList<>
TypeList<>::Resize<1> NOT COMPILE

TypeList<A>::Resize<0> == TypeList<>
TypeList<A>::Resize<1> == TypeList<A>
TypeList<A>::Resize<2> NOT COMPILE

TypeList<A, A>::Resize<0> == TypeList<>
TypeList<A, A>::Resize<1> == TypeList<A>
TypeList<A, A>::Resize<2> == TypeList<A, A>
TypeList<A, A>::Resize<3> NOT COMPILE

TypeList<A, B>::Resize<0> == TypeList<>
TypeList<A, B>::Resize<1> == TypeList<A>
TypeList<A, B>::Resize<2> == TypeList<A, B>
TypeList<A, B>::Resize<3> NOT COMPILE
