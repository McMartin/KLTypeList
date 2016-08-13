# Copyright (c) 2014-2016 Alain Martin

Contains<Type> -> Boolean

TypeList<>::Contains<A> == false

TypeList<A>::Contains<A> == true
TypeList<A>::Contains<B> == false

TypeList<A, A>::Contains<A> == true
TypeList<A, A>::Contains<B> == false

TypeList<A, B>::Contains<A> == true
TypeList<A, B>::Contains<B> == true
TypeList<A, B>::Contains<C> == false
