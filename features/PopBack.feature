PopBack -> TypeList

TypeList<>::PopBack NOT COMPILE

TypeList<A>::PopBack == TypeList<>

TypeList<A, A>::PopBack == TypeList<A>
TypeList<A, B>::PopBack == TypeList<A>

TypeList<A, A, A>::PopBack == TypeList<A, A>
TypeList<A, A, B>::PopBack == TypeList<A, A>
TypeList<A, B, A>::PopBack == TypeList<A, B>
TypeList<A, B, B>::PopBack == TypeList<A, B>
TypeList<A, B, C>::PopBack == TypeList<A, B>
