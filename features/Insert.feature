# Copyright (c) 2014-2016 Alain Martin

Insert<Integer, Type> -> TypeList

TypeList<>::Insert<0, A> == TypeList<A>
TypeList<>::Insert<1, A> NOT COMPILE

TypeList<A>::Insert<0, A> == TypeList<A, A>
TypeList<A>::Insert<1, A> == TypeList<A, A>
TypeList<A>::Insert<2, A> NOT COMPILE

TypeList<A>::Insert<0, B> == TypeList<B, A>
TypeList<A>::Insert<1, B> == TypeList<A, B>
TypeList<A>::Insert<2, B> NOT COMPILE

TypeList<A, A>::Insert<0, A> == TypeList<A, A, A>
TypeList<A, A>::Insert<1, A> == TypeList<A, A, A>
TypeList<A, A>::Insert<2, A> == TypeList<A, A, A>
TypeList<A, A>::Insert<3, A> NOT COMPILE

TypeList<A, A>::Insert<0, B> == TypeList<B, A, A>
TypeList<A, A>::Insert<1, B> == TypeList<A, B, A>
TypeList<A, A>::Insert<2, B> == TypeList<A, A, B>
TypeList<A, A>::Insert<3, B> NOT COMPILE

TypeList<A, B>::Insert<0, A> == TypeList<A, A, B>
TypeList<A, B>::Insert<1, A> == TypeList<A, A, B>
TypeList<A, B>::Insert<2, A> == TypeList<A, B, A>
TypeList<A, B>::Insert<3, A> NOT COMPILE

TypeList<A, B>::Insert<0, B> == TypeList<B, A, B>
TypeList<A, B>::Insert<1, B> == TypeList<A, B, B>
TypeList<A, B>::Insert<2, B> == TypeList<A, B, B>
TypeList<A, B>::Insert<3, B> NOT COMPILE

TypeList<A, B>::Insert<0, C> == TypeList<C, A, B>
TypeList<A, B>::Insert<1, C> == TypeList<A, C, B>
TypeList<A, B>::Insert<2, C> == TypeList<A, B, C>
TypeList<A, B>::Insert<3, C> NOT COMPILE
