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
    Adds compile-time type safety and exception-based error handling.
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BOLEO_CONFIG_HPP_
#define BOLEO_CONFIG_HPP_


#include <string>

#include "tango_client_api.h"


    //! Namespace for Boleo.
namespace boleo
{


    //! See tango_client_api.h, for the current list.
    /*!
        @note
        This list can change between builds, so don't persist or make any
        assumptions about the numerical values.
    */
enum ConfigEntry
{
    config_color_mode_auto,                             //!< Writable.
    config_color_iso,                                   //!< Writable.
    config_color_exp,                                   //!< Writable.
    config_depth_mode,                                  //!< Writable.
    config_enable_auto_recovery,                        //!< Writable.
    config_enable_color_camera,                         //!< Writable.
    config_enable_depth,                                //!< Writable.
    config_enable_low_latency_imu_integration,          //!< Writable.
    config_enable_learning_mode,                        //!< Writable.
    config_enable_motion_tracking,                      //!< Writable.
    config_high_rate_pose,                              //!< Writable.
    config_smooth_pose,                                 //!< Writable.
    config_load_area_description_UUID,                  //!< Writable.
    config_enable_dataset_recording,                    //!< Writable.
    config_enable_drift_correction,                     //!< Writable.
    config_experimental_enable_scene_reconstruction,    //!< Writable.

    tango_service_library_version,                      //!< Read-only.
    depth_period_in_seconds,                            //!< Read-only.
    max_point_cloud_elements,                           //!< Read-only.

    config_runtime_depth_framerate                      //!< Runtime writable.
};


    //! Used internally, to enable compile-time checks.
enum Permissions
{
    inaccessible = 0,
    read = 1,
    write = 2,

    ro = read,
    wo = write,
    rw = read | write
};


    // Provides necessary details of each configuration entry.
template<
    ConfigEntry e
>
struct ConfigEntryTraits;


    //! Reads the value of a configuration entry, given the type.
template<
    typename T
>
T Config_get(
    TangoConfig config, //!< The config object to read.
    const char *name    //!< Name of the entry to read.
);


    //! Writes the value of a configuration entry of given type.
template<
    typename T
>
void Config_set(
    TangoConfig config, //!< The config object to write.
    const char *name,   //!< Name of the entry to write.
    const T &value      //!< The value to write.
);


    //! Reads the value of a configuration entry, specified at compile time.
template<
    ConfigEntry e
>
typename ConfigEntryTraits< e >::value_type Config_get(
    TangoConfig config  //!< The config object to read.
)
{
    typedef ConfigEntryTraits< e > traits_type;
    typedef typename traits_type::value_type return_type;

    static_assert( traits_type::is_readable, "Entry must be readable" );

    return Config_get< return_type >( config, traits_type::name );
}


    //! Writes the value of a configuration entry, specified at compile time.
template<
    ConfigEntry e
>
void Config_set(
    TangoConfig config, //!< The config object to write.
    const typename ConfigEntryTraits< e >::value_type &value //!< Value to write.
)
{
    typedef ConfigEntryTraits< e > traits_type;
    typedef typename traits_type::value_type value_type;

    static_assert( traits_type::is_writable, "Entry must be writable" );

    Config_set< value_type >( config, traits_type::name, value );
}

template<> bool         Config_get< bool        >( TangoConfig, const char * );
template<> int32_t      Config_get< int32_t     >( TangoConfig, const char * );
template<> int64_t      Config_get< int64_t     >( TangoConfig, const char * );
template<> double       Config_get< double      >( TangoConfig, const char * );
template<> std::string  Config_get< std::string >( TangoConfig, const char * );

template<> void Config_set< bool        >( TangoConfig, const char *, const bool & );
template<> void Config_set< int32_t     >( TangoConfig, const char *, const int32_t & );
template<> void Config_set< int64_t     >( TangoConfig, const char *, const int64_t & );
template<> void Config_set< double      >( TangoConfig, const char *, const double & );
template<> void Config_set< const char *>( TangoConfig, const char *, const char * const & );
template<> void Config_set< std::string >( TangoConfig, const char *, const std::string & );


    // Internal macro.
    /*
        Used to specialize ConfigEntryTraits<> for each value of ConfigEntry.
    */
#define BOLEOI_SPECIALIZE( p, t, e )                                    \
    template<> struct ConfigEntryTraits< e >                            \
    {                                                                   \
        typedef t value_type;                                           \
                                                                        \
        static std::integral_constant< Permissions, (p) >  permissions; \
        static std::integral_constant< bool, (p) & read >  is_readable; \
        static std::integral_constant< bool, (p) & write > is_writable; \
                                                                        \
        static constexpr char name[] = # e;                             \
    }


BOLEOI_SPECIALIZE( rw, bool,        config_color_mode_auto );
BOLEOI_SPECIALIZE( rw, int32_t,     config_color_iso );
BOLEOI_SPECIALIZE( rw, int32_t,     config_color_exp );
BOLEOI_SPECIALIZE( rw, int32_t,     config_depth_mode );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_auto_recovery );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_color_camera );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_depth );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_low_latency_imu_integration );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_learning_mode );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_motion_tracking );
BOLEOI_SPECIALIZE( rw, bool,        config_high_rate_pose );
BOLEOI_SPECIALIZE( rw, bool,        config_smooth_pose );
BOLEOI_SPECIALIZE( rw, std::string, config_load_area_description_UUID );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_dataset_recording );
BOLEOI_SPECIALIZE( rw, bool,        config_enable_drift_correction );
BOLEOI_SPECIALIZE( rw, bool,        config_experimental_enable_scene_reconstruction );
BOLEOI_SPECIALIZE( ro, std::string, tango_service_library_version );
BOLEOI_SPECIALIZE( ro, double,      depth_period_in_seconds );
BOLEOI_SPECIALIZE( ro, int32_t,     max_point_cloud_elements );
BOLEOI_SPECIALIZE( rw, int32_t,     config_runtime_depth_framerate );

#undef BOLEOI_SPECIALIZE


} // namespace boleo


#endif // BOLEO_CONFIG_HPP_

