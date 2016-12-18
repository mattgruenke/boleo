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

    See error_handling.hpp for details.
*/
////////////////////////////////////////////////////////////////////////////////


#include "error_handling.hpp"


namespace boleo {


void ThrowError( TangoErrorType ev, const char *what )
{
    throw TangoException( ev, what );
}



// class TangoException:
TangoException::TangoException( TangoErrorType ev, const char *what )
: std::system_error( ev, TangoErrorCategory::get(), what )
{
}


TangoException::~TangoException()
{
}



// class TangoErrorCategory:
TangoErrorCategory::~TangoErrorCategory()
{
}


const char *TangoErrorCategory::name() const noexcept
{
        // This is consistent with the names of generic and system categories.
    return "tango";
}


std::string TangoErrorCategory::message( int condition ) const
{
    switch (condition)
    {
        case TANGO_NO_DATASET_PERMISSION:
            return "The user has not given permissions to read and write datasets.";

        case TANGO_NO_IMPORT_EXPORT_PERMISSION:
            return "The user has not given permission to export or import ADF files.";

        case TANGO_NO_CAMERA_PERMISSION:
            return "The user has not given permission to access the device's camera.";

        case TANGO_NO_ADF_PERMISSION:
            return "The user has not given permission to save or change ADF files.";

        case TANGO_NO_MOTION_TRACKING_PERMISSION:
            return "The user has not given permission to use Motion Tracking functionality.";

        case TANGO_INVALID:
            return "The input argument is invalid.";

        case TANGO_ERROR:
            return "Some sort of hard error occurred.";

        case TANGO_SUCCESS:
            return "Success.";
    }

    return "Unknown error.";
}


TangoErrorCategory &TangoErrorCategory::get()
{
    return inst;
}


TangoErrorCategory TangoErrorCategory::inst;


} // namespace boleo

