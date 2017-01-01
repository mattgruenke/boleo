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
//! Provides exception-handling support for JNI methods.
/*! @file

    To aid last-resort exception handling, typically within jni_interface.cc,
    SafeCall() provides a try/catch in which to call any functions that might
    throw exceptions.

    @note
    This assumes you're compiling with -std=c++11 and -fexceptions.  If not,
    add them to LOCAL_CFLAGS, in your Android.mk.
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BOLEO_SAFE_CALL_HPP_
#define BOLEO_SAFE_CALL_HPP_


#include "boleo/exceptions.hpp"

#include <type_traits>



    //! Namespace for Boleo.
namespace boleo {


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
        log_fn( e.what() );     // TO_DO: get more info, here
    }
    catch (...)
    {
        log_fn( "Unknown exception" );
    }

    return TANGO_ERROR;
}


} // namespace boleo


#endif // BOLEO_SAFE_CALL_HPP_

