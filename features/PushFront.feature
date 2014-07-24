PushFront<Type> -> TypeList

TypeList<>::PushFront<A> == TypeList<A>

TypeList<A>::PushFront<A> == TypeList<A, A>
TypeList<A>::PushFront<B> == TypeList<B, A>

TypeList<A, A>::PushFront<A> == TypeList<A, A, A>
TypeList<A, A>::PushFront<B> == TypeList<B, A, A>

TypeList<A, B>::PushFront<A> == TypeList<A, A, B>
TypeList<A, B>::PushFront<B> == TypeList<B, A, B>
TypeList<A, B>::PushFront<C> == TypeList<C, A, B>
