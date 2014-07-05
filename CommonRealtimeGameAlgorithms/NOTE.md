






Exceptions vs Assertions
------------------------

-	Assertions and exceptions are different.
	Don't be fooled by wording similarity.

	Major difference is **oppotunity of choice**. Exceptions provide you an oppotunity of recovery, but assertions are not. This 
	difference makes exceptions *testable*, and this is very huge.

	Assertions are debugging aid. It means *no will to recover*. Assertions usually checks **already corrupted state**, so they
	cannot be recovered. Consequently, they always crash program immediately on corrupted execution state to prevent further damage.
	If program is fully bug-free, removing of assertions should make no difference on execution and result.

	Exceptions are regular flow control. It means *willing to recover*. Main purpose of exception is providing **choice of recovery**
	to users. (assertions has no choice due to forced crash) This is very useful on test code.
	It requires program state is clean and not corrupted. If some operation is going to corrupt state, user check check it, and except 
	the situation by throwing an exception.
	Because it's a part of regular program, removing exception will break program logics.

-	An uncaught exception means is a bug of omitting regular handling structure.

-	Exceptions are very expensive in most modern C++ compilers. Because it's literally *exceptional* flow, so it's better to make
	other parts faster.
	
-	Generalization of exception is CPS.











Alignment
---------

In ARM processors, memory alignment is very sensitive issue because
access to unaligned memory will cause an `EXC_ARM_DA_ALIGN` exception.

In most cases, this won't be an issue because compiler handles alignment
correctly. Compiler basically tries to align every structures to machine's
native word size by padding empty space. If user specified explicit size 
(such as `char`), compiler will emit special instructions to access unaligned
memory location. This costs more, but at least, the code will work correctly.

The problem comes from direct memory accessing tricks. If compiler cannot 
determine the type of the object at compile-time, it's impossible to pad or
mit special instructions. Unaligned memory access is very likely to happen
in this case. In this case, programmers are responsible to ensure the alignment
because it's the programmers who hid the type information to compilers!

It's hard to handle alignment manually and correctly. It's far better to let
the compiler do the job. The point is exposing the type to the compiler rather
than erasing it.
