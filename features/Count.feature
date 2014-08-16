Count<Type, ValueType> -> Integer

TypeList<>::Count<A> == 0

TypeList<A>::Count<A> == 1
TypeList<A>::Count<B> == 0

TypeList<A, A>::Count<A> == 2
TypeList<A, A>::Count<B> == 0

TypeList<A, B>::Count<A> == 1
TypeList<A, B>::Count<B> == 1
TypeList<A, B>::Count<C> == 0
