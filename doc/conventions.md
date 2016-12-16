# Coding Conventions #

My C++ style is something of a hybrid between the boost and Google conventions.


## Filenames ##

### Headers ###

* C++ header files should be easily distinguishable from C.  So, unless a header
  file is designed to be usable from C files, it should have a .hpp extension.


### Compilation Units ###

* Compiled C++ source files should use a .cpp extension.


## Namespaces ##

* Avoid nested namespaces that match well-known top-level namespaces.  Straight from Google.
* Prefer unnamed namespaces to static scope specifiers, in .cpp files?


## Classes ##

* Interface classes should use the Interface suffix
* Declaration order (within each scope):

        Using-declarations
        Constants & Enums
        Nested types & typedefs
        Static methods
        Constructors and assignment operators
        Destructor
        Non-static methods
        Static data members
        Non-static Data Members

## R-value References ##

* use only to define move constructors/assignment or for perfect fwd'ing
* Forwarding should use std::forward
* May use std::move


## constexpr ##

* Use it on constants
* Use it on functions, as needed.  Be sensible & don't get carried away.


## Integer Types ##

* use int for fast & easy integral values.
* use cstdint types, when a fixed size is needed.
* prefer to avoid unsigned
* define numeric constants of non-'int' type using INTn_C() and UINTn_C()


## Naming ##

* names at file & namespace scope are Capitalized.
* Variable names are all lower-case.
* Member functions & nested types start with lower-case.  They may be
  all-lowercase, if needed for compatibility with STL.
* class data members end in '_', except for struct members and class-scoped
  statics.
* The jury is out on k-prefixing constants, but capitalization should follow
  scoping rules.
* Namespace names are lowercase.  Main argument is to reduce clashes with class
  names.  Also, saves typing.


## Whitespace ##

### Indentation ###

* Use an indentation increment of 4.


### TABs ###

* Set TAB size to 8.
* Never indent with tabs.
* Avoid tabs, in general.


### Line Length ###

* Header files are firmly limited to 80 columns.  Exceptions are possible, when
  line-wrapping would obscure patterns in the code, such as a slight variation
  between lines.
* soft limit for implementation file whitespace at 96 columns.
  Firm limit at 120.
  Hard limit at 132.


### Curly Braces ###

* Curly braces start a new line, at the same indentation of the line above.
* Curly braces may only be omitted if the entire statement can fit on the same line.


### Horizontal Whitespace ###

* In function parameter lists '('s should be followed by a space, since they're
  semantically different from expressions.
* Everywhere else they're required by the language, '(' should be preceded by a
  space.
* In expressions, '(' should have no space, on either side.
* Template parameter lists should have a space after/before '<' and '>',
  respectively.  Sometimes necessary for C++98, it's now just a habit.
* for brace initialization involving the type, put a space in between to help
  distinguish it from ()'s.  For example:

        vector< int > v( 100, 1 );   // A vector of 100 1s.
        vector< int > v { 100, 1 };  // A vector of 100, 1.

