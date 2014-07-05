README
======
2014/05/21
Hoon H.




NOT YET USABLE OR AVAILALBLE. STILL UNDER INTEGRATION...







Project is hand-crafted by following FreeType's INSTALL.ANY guide.

BZIP2 support stripped off.

Take care that some c files MUST BE EXCLUDED from compilation. See the FreeType's INSTALL.ANY for details.
There're more files which are not included in this project. They are required, but excluded from project
to prevent accidental inclusion in build process.






Issues and Solutions
--------------------

-	Symbol `border` duplicated.

	I don't knnow what's happening, but I renamed it to `ee_border` to be unique.
	And it works now.

-	Implicit 32/64-bit conversion.
	I think FreeType is designed only for 32-bit system. 
	I don't work to mess with them. I just suppressed warning with compiler flags.
	
-	Variable may be uninitialized.
	I don't know why this happens. Just suppressed warning. I believe the code author.
	
	
	
	
	
	
	
License and Credits
-------------------
Though FreeType also provides GPL, but I didn't included GPL stuff because
I am using FreeType under FreeType license.	(BSD-like)

Here's explicit credit requested by the license.
	
	Portions of this software are copyright © 2014 The FreeType
	Project (www.freetype.org).  All rights reserved.
	
FreeType is works of FreeType development team.
Here's a list of major authors which is copied from the [website](http://www.freetype.org/contact.html).

-	Original Authors

	David Turner (no longer active development but still spiritus rector of the project)
	Robert Wilhelm (no longer active)
	Werner Lemberg (current maintainer)

-	Core Developers

	Alexei Podtelezhnikov (Алексей Подтележников)
	Suzuki Toshiya (鈴木俊哉)

-	Major Contributors

	Oran Agra
	Graham Asher
	David Bevan
	Bradley Grainger
	Infinality
	Tom Kacvinsky
	Pavel Kaňkovský
	Antoine Leca
	Just van Rossum
	Wu Chia-I (吳佳一)

*	Last update: 2-Jul-2013















		
