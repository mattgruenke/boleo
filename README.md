# ![Boleo](img/Boleo_logo.png)

A library of C++ utilities for use with the C interface of Google's Project
Tango.


## Features ##

Function templates are provided for accessing TangoConfig entries, featuring:

* Compile-time type safety
* Exception-based error handling


Error handling utilities:

* TangoException is derived from std::system_error, in order to facilitate 
  propagation of API errors via exceptions.
* TangoErrorCategory facilitates error message lookup, within the context of
  exception handling.
* SafeCall() trampoline functions provide convenient last-resort exception
  handling.


## Documentation ##

API documentation is provided via doxygen.  If you have it installed, build the
'doc' target.


## License ##

Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or <http://boost.org/LICENSE_1_0.txt>


## API Stability ##

Everything prior to v1.0 is subject to change.  After that, only a recompile
should be needed to upgrade user code to new releases with the same major
revision.

Since this is intended to be distributed with your app, no guarantees are made
about binary compatibility, between any two releases.


## More Information ##

The current home of this library is <https://github.com/mattgruenke/boleo>

For more on Google's Project Tango, see <https://developers.google.com/tango/>

