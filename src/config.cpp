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
//! Wrapper for TangoConfig.
/*! @file

    See config.hpp, for details.
*/
////////////////////////////////////////////////////////////////////////////////


#include "config.hpp"
#include "error_handling.hpp"

#include <sstream>


    //! Namespace for Boleo.
namespace boleo
{


static void ThrowIfAccessError( TangoErrorType ev, const char *access, const char *name )
{
    if (!ev) return;

    std::ostringstream oss;
    oss << "Failed to " << access << " configuration parameter '" << name << "'";
    ThrowError( ev, oss.str().c_str() );
}


static void ThrowIfGetError( TangoErrorType ev, const char *name )
{
    ThrowIfAccessError( ev, "get", name );
}


static void ThrowIfSetError( TangoErrorType ev, const char *name )
{
    ThrowIfAccessError( ev, "set", name );
}


std::string Config_toString( TangoConfig config )
{
    char *str = TangoConfig_toString( config );
    if (!str) throw std::runtime_error( "Config_toString() failed" );

    std::string result( str );
    free( str );

    return result;
}


template<> bool Config_get< bool >( TangoConfig config, const char *name )
{
    bool value = false;
    ThrowIfGetError( TangoConfig_getBool( config, name, &value ), name );
    return value;
}


template<> int32_t Config_get< int32_t >( TangoConfig config, const char *name )
{
    int32_t value = 0;
    ThrowIfGetError( TangoConfig_getInt32( config, name, &value ), name );
    return value;
}


template<> int64_t Config_get< int64_t >( TangoConfig config, const char *name )
{
    int64_t value = 0;
    ThrowIfGetError( TangoConfig_getInt64( config, name, &value ), name );
    return value;
}


template<> double Config_get< double >( TangoConfig config, const char *name )
{
    double value = 0.0;
    ThrowIfGetError( TangoConfig_getDouble( config, name, &value ), name );
    return value;
}


template<> std::string Config_get< std::string >( TangoConfig config, const char *name )
{
        // It's unfortunate the API provides no better option...
    constexpr size_t MaxStringSize = 4000;
    char value[MaxStringSize + 1] = { '\0' };
    ThrowIfGetError( TangoConfig_getString( config, name, value, MaxStringSize ), name );
    value[MaxStringSize] = '\0';
    return value;
}


template<> void Config_set< bool >( TangoConfig config, const char *name, const bool &value )
{
    ThrowIfSetError( TangoConfig_setBool( config, name, value ), name );
}


template<> void Config_set< int32_t >( TangoConfig config, const char *name, const int32_t &value )
{
    ThrowIfSetError( TangoConfig_setInt32( config, name, value ), name );
}


template<> void Config_set< int64_t >( TangoConfig config, const char *name, const int64_t &value )
{
    ThrowIfSetError( TangoConfig_setInt64( config, name, value ), name );
}


template<> void Config_set< double >( TangoConfig config, const char *name, const double &value )
{
    ThrowIfSetError( TangoConfig_setDouble( config, name, value ), name );
}


template<> void Config_set< const char * >( TangoConfig config, const char *name, const char * const &value )
{
    ThrowIfSetError( TangoConfig_setString( config, name, value ), name );
}


template<> void Config_set< std::string >( TangoConfig config, const char *name, const std::string &value )
{
    ThrowIfSetError( TangoConfig_setString( config, name, value.c_str() ), name );
}


} // namespace boleo

