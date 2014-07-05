README
======
Hoon H.



A collection of classes which contains algorithms that are useful to real-time game code.




**WARNING** API IS UNSTABLE!!!












Design Policy
-------------

-	This library provides *strong exception safety** for all specific classes and methods. For the generic template classes, this
	guarantee is provided conditionally by the parameter type classes. Each requirements are noted in each class comments.

-	Assertions are all conditionally removeable. If you're sure that your program is fully bug-free (...), then removing of exception
	will make no difference on program execution.




Namespaces
----------

-	`FlatContainers` 

	Provides classes to *store* objects.
	Usually uses plain generic template pattern because recusive type referencing is not 
	required.

-	`DataStructures`

	Provides classes to *make relationships* between object to organize some structure.
	Classes does not care about storing related objects. Users are responsible to store
	the objects. Usually uses CRTP due to need for recursive type referencing.






