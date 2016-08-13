# Copyright (c) 2014-2016 Alain Martin

Empty -> Boolean

TypeList<>::Empty == true

TypeList<A>::Empty == false

TypeList<A, A>::Empty == false

TypeList<A, B>::Empty == false
