# Copyright (c) 2014-2016 Alain Martin

At<Integer> -> Type

TypeList<>::At<0> NOT COMPILE

TypeList<A>::At<0> == A
TypeList<A>::At<1> NOT COMPILE

TypeList<A, A>::At<0> == A
TypeList<A, A>::At<1> == A
TypeList<A, A>::At<2> NOT COMPILE

TypeList<A, B>::At<0> == A
TypeList<A, B>::At<1> == B
TypeList<A, B>::At<2> NOT COMPILE
