PopFront -> TypeList

TypeList<>::PopFront NOT COMPILE

TypeList<A>::PopFront == TypeList<>

TypeList<A, A>::PopFront == TypeList<A>
TypeList<A, B>::PopFront == TypeList<B>

TypeList<A, A, A>::PopFront == TypeList<A, A>
TypeList<A, A, B>::PopFront == TypeList<A, B>
TypeList<A, B, A>::PopFront == TypeList<B, A>
TypeList<A, B, B>::PopFront == TypeList<B, B>
TypeList<A, B, C>::PopFront == TypeList<B, C>
