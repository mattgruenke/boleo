////////////////////////////////////////////////////////////////////////////////
//
//  Copyright Matthew A. Gruenke 2016.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//   http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////////////////////
//
//! Provides exception class for TangoErrors, derived from std::sytem_error.
/*! @file

    TangoException is provided as the primary exception for Tango API errors.
    It's built atop std::system_error, as a way to provide string translations
    for error values and to enable recovery of the original return code.

    @note
    This assumes you're compiling with -std=c++11 and -fexceptions.  If not,
    add them to LOCAL_CFLAGS, in your Android.mk.
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BOLEO_EXCEPTIONS_HPP_
#define BOLEO_EXCEPTIONS_HPP_


#include <system_error>

extern "C"
{
#   include "tango_client_api.h"
}


    //! Inspired by assert(), this uses the contained expression
    //!  as the string to indicate what triggered the exception.
    /*!
        If you want to provide more information, consider
        using ThrowIfError(), instead.

        @param expr - this expression should evaluate to a TangoErrorType.
    */
#define BOLEO_THROW_IF_ERROR( expr ) \
    boleo::ThrowIfError( expr, # expr )



    //! Namespace for Boleo.
namespace boleo {


    //! Throws a TangoException.
void ThrowError(
    TangoErrorType ev,  //!< What error was encountered.
    const char *what    //!< Circumstances of the error.
);


    //! Conditionally throws a TangoException.
inline void ThrowIfError(
    TangoErrorType ev,  //!< What error was encountered.
    const char *what    //!< Circumstances of the error.
)
{
    if (ev) ThrowError( ev, what );
}


    //! A distinct type for Tango Errors, in case callers want
    //!  to handle these, but not other system_errors.
class TangoException: public std::system_error
{
public:
    TangoException( TangoErrorType ev, const char *what );
    virtual ~TangoException();
};


    // Tell system_error that this is an enum.
template< TangoErrorType >
    struct is_error_code_enum:
        public std::integral_constant< bool, true >
{
};


    // Tell system_error that this is an enum.
template< TangoErrorType >
    struct is_error_condition_enum:
        public std::integral_constant< bool, true >
{
};


    //! Error category for Tango Errors.
class TangoErrorCategory: public std::error_category
{
public:
    virtual ~TangoErrorCategory();

    virtual const char *name() const noexcept;
    virtual std::string message( int condition ) const;

    static TangoErrorCategory &get();

private:
    static TangoErrorCategory inst;
};


} // namespace boleo


#endif // BOLEO_EXCEPTIONS_HPP_

