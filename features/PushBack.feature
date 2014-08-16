PushBack<Type> -> TypeList

TypeList<>::PushBack<A> == TypeList<A>

TypeList<A>::PushBack<A> == TypeList<A, A>
TypeList<A>::PushBack<B> == TypeList<A, B>

TypeList<A, A>::PushBack<A> == TypeList<A, A, A>
TypeList<A, A>::PushBack<B> == TypeList<A, A, B>

TypeList<A, B>::PushBack<A> == TypeList<A, B, A>
TypeList<A, B>::PushBack<B> == TypeList<A, B, B>
TypeList<A, B>::PushBack<C> == TypeList<A, B, C>
