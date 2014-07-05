AGE2
====







`opt` vs `????`
---------------


`opt` is the value or null-state. Which can be compared to a `nullptr`.
`????` is the value or an error. This never goes to a null-state.

Null-state of `opt` is a normal state, and doesn't be treated as an error
state. If `????` has no proper value, that's treated as an error state,
and you can get the error object from the `????` object.

*	The name of `????` is not decided yet. And it will be defined later.








Test Files
----------
Test files are placed in same directory together with feature files.
Anyway, it doesn't mean they're intended to be publicly expose. Do not
include tests in release build, and must be used internal only.

These internal-only files all contains four underline characters (`____`)
in their names.



