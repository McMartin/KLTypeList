Resize<Integer, Type> -> TypeList

TypeList<>::Resize<0, A> == TypeList<>
TypeList<A>::Resize<0, A> == TypeList<>
TypeList<A>::Resize<0, B> == TypeList<>
TypeList<A, A>::Resize<0, A> == TypeList<>
TypeList<A, A>::Resize<0, B> == TypeList<>
TypeList<A, B>::Resize<0, A> == TypeList<>
TypeList<A, B>::Resize<0, B> == TypeList<>
TypeList<A, B>::Resize<0, C> == TypeList<>

TypeList<>::Resize<1, A> == TypeList<A>
TypeList<A>::Resize<1, A> == TypeList<A>
TypeList<A>::Resize<1, B> == TypeList<A>
TypeList<A, A>::Resize<1, A> == TypeList<A>
TypeList<A, A>::Resize<1, B> == TypeList<A>
TypeList<A, B>::Resize<1, A> == TypeList<A>
TypeList<A, B>::Resize<1, B> == TypeList<A>
TypeList<A, B>::Resize<1, C> == TypeList<A>

TypeList<>::Resize<2, A> == TypeList<A, A>
TypeList<A>::Resize<2, A> == TypeList<A, A>
TypeList<A>::Resize<2, B> == TypeList<A, B>
TypeList<A, A>::Resize<2, A> == TypeList<A, A>
TypeList<A, A>::Resize<2, B> == TypeList<A, A>
TypeList<A, B>::Resize<2, A> == TypeList<A, B>
TypeList<A, B>::Resize<2, B> == TypeList<A, B>
TypeList<A, B>::Resize<2, C> == TypeList<A, B>

TypeList<>::Resize<3, A> == TypeList<A, A, A>
TypeList<A>::Resize<3, A> == TypeList<A, A, A>
TypeList<A>::Resize<3, B> == TypeList<A, B, B>
TypeList<A, A>::Resize<3, A> == TypeList<A, A, A>
TypeList<A, A>::Resize<3, B> == TypeList<A, A, B>
TypeList<A, B>::Resize<3, A> == TypeList<A, B, A>
TypeList<A, B>::Resize<3, B> == TypeList<A, B, B>
TypeList<A, B>::Resize<3, C> == TypeList<A, B, C>
