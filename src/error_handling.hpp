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
//! Provides exception-handling support for TangoErrors.
/*! @file
    TangoException is provided as the primary exception for Tango API errors.
    It's built atop std::system_error, as a way to provide string translations
    for error values and to enable recovery of the original return code.

    To aid last-resort exception handling, typically within jni_interface.cc,
    SafeCall() provides a try/catch in which to call any functions that might
    throw exceptions.

    @note
    This assumes you're compiling with -std=c++11 and -fexceptions.  If not,
    add them to LOCAL_CFLAGS, in your Android.mk.
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BOLEO_ERROR_HANDLING_HPP_
#define BOLEO_ERROR_HANDLING_HPP_


#include <type_traits>
#include <system_error>

#include "tango_client_api.h"


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
void ThrowIfError(
    TangoErrorType ev,  //!< What error was encountered.
    const char *what    //!< Circumstances of the error.
);


    //! A distinct type for Tango Errors, in case callers want
    //!  to handle these, but not other system_errors.
class TangoException: public std::system_error
{
public:
    TangoException( TangoErrorType ev, const char *what );
    virtual ~TangoException();
};


    //! A wrapper used to call class member functions within a try/catch block.
    /*!
        This is intended for use in jni_interface.cc.  As you can see, it
        simply logs the exception and returns the value of Tango errors
        back to the caller.  For non-tango exceptions, the best we can do
        is log and return a generic error value.

        @note
        The params might be copied, when using this.  If you want to avoid
        that, the best way is probably to use std::ref() with std::bind() to
        compose a function object with the corresponding parameters bound as
        references.
    */
template< 
    typename ClassType,     //!< Type of object containing the member function.
    typename... ParamTypes  //!< Types of the various function parameters.
>
jint SafeCall(
    void log_fn( const char * ),    //!< Function for logging errors.
    ClassType &c,           //!< Object instance on which to call member fn.
    jint (ClassType::*f)( ParamTypes... ),  //!< Member function.
    ParamTypes... params    //!< Member function params.
)
{
    try
    {
        return (c.*f)( params... );
    }
    catch (TangoException &e)
    {
        log_fn( e.what() );
        return e.code().value();
    }
    catch (std::exception &e)
    {
        log_fn( e.what() );
    }
    catch (...)
    {
        log_fn( "Unknown exception" );
    }

    return TANGO_ERROR;
}


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


#endif // BOLEO_ERROR_HANDLING_HPP_

