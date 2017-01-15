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


#include "boleo/config.hpp"
#include "boleo/exceptions.hpp"

#include <sstream>


    //! Namespace for Boleo.
namespace boleo
{


UniqueConfig NullConfig()
{
    return UniqueConfig( nullptr, &TangoConfig_free );
}


UniqueConfig WrapConfig( TangoConfig cfg )
{
    return UniqueConfig( cfg, &TangoConfig_free );
}


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


namespace detail
{

    // The name strings need to be instantiated.
    constexpr char ConfigEntryTraits< config_color_mode_auto >::name[];
    constexpr char ConfigEntryTraits< config_color_iso >::name[];
    constexpr char ConfigEntryTraits< config_color_exp >::name[];
    constexpr char ConfigEntryTraits< config_depth_mode >::name[];
    constexpr char ConfigEntryTraits< config_enable_auto_recovery >::name[];
    constexpr char ConfigEntryTraits< config_enable_color_camera >::name[];
    constexpr char ConfigEntryTraits< config_enable_depth >::name[];
    constexpr char ConfigEntryTraits< config_enable_low_latency_imu_integration >::name[];
    constexpr char ConfigEntryTraits< config_enable_learning_mode >::name[];
    constexpr char ConfigEntryTraits< config_enable_motion_tracking >::name[];
    constexpr char ConfigEntryTraits< config_high_rate_pose >::name[];
    constexpr char ConfigEntryTraits< config_smooth_pose >::name[];
    constexpr char ConfigEntryTraits< config_load_area_description_UUID >::name[];
    constexpr char ConfigEntryTraits< config_enable_dataset_recording >::name[];
    constexpr char ConfigEntryTraits< config_enable_drift_correction >::name[];
    constexpr char ConfigEntryTraits< config_experimental_enable_scene_reconstruction >::name[];
    constexpr char ConfigEntryTraits< tango_service_library_version >::name[];
    constexpr char ConfigEntryTraits< depth_period_in_seconds >::name[];
    constexpr char ConfigEntryTraits< max_point_cloud_elements >::name[];
    constexpr char ConfigEntryTraits< config_runtime_depth_framerate >::name[];

}


} // namespace boleo

