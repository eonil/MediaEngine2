README - AppKitSanitizer
========================
2014/06/28





The problem of current AppKit is insufficient assertions.
Some assertions are exists, but still insufficient, and a lot of
bugs comes from the lack of assertions.

We can prevent a lot of bugs just by providing proper assertions.
This framework is an effort to provide those assertions. This 
performs heavy dynamic state validation, then it must be stripped
off in release version.

Not only for dynamic assertions, but we also can add some valuable 
attributes such as unavailability to `-[NSCopying copyWithZone]` 
method.


Though this limits the acceptable range of values, this does not 
change any existing core behaviors of Cocoa classes. If you want
such behavior overriding, do it yourself by subclassing this.