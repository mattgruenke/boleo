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
//! Provides type-safe wrappers for accessing entries in TangoConfig objects.
/*! @file

    This file provides two sets of TangoConfig accessor functions.  One of
    which enables compile-time type safety, while both provide exception-based
    error handling.

    When the config entry is known at compile time, prefer the single-parameter
    and two-parameter forms of Config_get() and Config_set(), respectively.
    The template parameter indicates both the entry to access, and the type of
    the return value.

    @code

        UniqueConfig config =
            WrapConfig( TangoService_getConfig( TANGO_CONFIG_RUNTIME ) );

        int depth_mode = Config_get< config_depth_mode >( config.get() );
        Config_set< config_enable_color_camera >( config.get(), false );

    @endcode

    When the config entry accessed is known only at runtime, then the form used
    accepts the value type as the template parameter.

    @code

        Config_set< int >( config.get(), name.c_str(), value );

    @endcode    
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BOLEO_CONFIG_HPP_
#define BOLEO_CONFIG_HPP_


#include <string>
#include <memory>
#include <type_traits>

extern "C" {
#   include "tango_client_api.h"
}


    //! Namespace for Boleo.
namespace boleo
{


    //! Wraps TangoConfig in a std::unique_ptr<>.
    /*!
        Use with NullConfig() and WrapConfig(), or as follows:
        @code

            UniqueConfig cfg(
                TangoService_getConfig( TANGO_CONFIG_DEFAULT ),
                &TangoConfig_free );

                // Even if setting to nullptr, use TangoConfig_free().
            cfg = UniqueConfig( nullptr, &TangoConfig_free );

                // ...because, when resetting, only TangoConfig is replaced.
            cfg.reset( TangoService_getConfig( TANGO_CONFIG_DEFAULT ) );

        @endcode
    */
typedef std::unique_ptr<
    std::remove_pointer< TangoConfig >::type, 
    void (*)( TangoConfig ) > UniqueConfig;


    //! Returns a NULL UniqueConfig instance.
UniqueConfig NullConfig();


    //! Wraps a TangoConfig instance in UniqueConfig.
UniqueConfig WrapConfig(
    TangoConfig cfg
);


    //! Raw pointer accessor function, supporting Config function templates.
TangoConfig GetConfig(
    UniqueConfig &cfg   //!< Instance to access.
);


    // Overload for TangoConfig.
constexpr TangoConfig GetConfig( TangoConfig );


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


    //! Internal details.
namespace detail
{

        // Provides necessary details of each configuration entry.
    template< ConfigEntry e > struct ConfigEntryTraits;

}


    //! Wraps TangoConfig_toString().
    /*!
        @throws std::runtime_error in case of failure.

        This can't throw TangoError, since TangoConfig_toString() returns no
        error code.
    */
std::string Config_toString(
    TangoConfig config  //!< The config object to read.
);


    //! Reads the value of a configuration entry, given the type.
    /*!
        @throws TangoError in case of errors.
    */
template<
    typename T
>
T Config_get(
    TangoConfig config, //!< The config object to read.
    const char *name    //!< Name of the entry to read.
);


    //! Writes the value of a configuration entry of given type.
    /*!
        @throws TangoError in case of errors.
    */
template<
    typename T
>
void Config_set(
    TangoConfig config, //!< The config object to write.
    const char *name,   //!< Name of the entry to write.
    const T &value      //!< The value to write.
);


    //! Reads the value of a configuration entry, specified at compile time.
    /*!
        @throws TangoError in case of errors.
    */
template<
    ConfigEntry e
>
typename detail::ConfigEntryTraits< e >::value_type Config_get(
    TangoConfig config  //!< The config object to read.
)
{
    typedef detail::ConfigEntryTraits< e > traits_type;
    typedef typename traits_type::value_type return_type;

    static_assert( traits_type::is_readable, "Entry must be readable" );

    return Config_get< return_type >( config, traits_type::name );
}


    //! Writes the value of a configuration entry, specified at compile time.
    /*!
        @throws TangoError in case of errors.
    */
template<
    ConfigEntry e
>
void Config_set(
    TangoConfig config, //!< The config object to write.
    const typename detail::ConfigEntryTraits< e >::value_type &value //!< Value.
)
{
    typedef detail::ConfigEntryTraits< e > traits_type;
    typedef typename traits_type::value_type value_type;

    static_assert( traits_type::is_writable, "Entry must be writable" );

    Config_set< value_type >( config, traits_type::name, value );
}



////////////////////////////////////////////////////////////
// Specializations
////////////////////////////////////////////////////////////

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



////////////////////////////////////////////////////////////
// Internal Details
////////////////////////////////////////////////////////////

constexpr TangoConfig GetConfig( TangoConfig cfg )
{
    return cfg;
}


inline TangoConfig GetConfig( UniqueConfig &cfg )
{
    return cfg.get();
}


namespace detail
{


    // Used internally, to enable compile-time checks.
enum Permissions
{
    inaccessible = 0,
    read = 1,
    write = 2,

    ro = read,
    wo = write,
    rw = read | write
};


    // Primarily to avoid a narrowing warning, in std::integral_constant<>.
constexpr bool IsReadable( Permissions p )
{
    return (p & read) != 0;
}


    // Primarily to avoid a narrowing warning, in std::integral_constant<>.
constexpr bool IsWritable( Permissions p )
{
    return (p & write) != 0;
}


    // Internal macro.
    /*
        Used to specialize ConfigEntryTraits<> for each value of ConfigEntry.
    */
#define BOLEOI_SPECIALIZE( p, t, e )                                        \
    template<> struct ConfigEntryTraits< e >                                \
    {                                                                       \
        typedef t value_type;                                               \
                                                                            \
        static std::integral_constant< Permissions, (p) >       permissions;\
        static std::integral_constant< bool, IsReadable( p ) >  is_readable;\
        static std::integral_constant< bool, IsWritable( p ) >  is_writable;\
                                                                            \
        static constexpr char name[] = # e;                                 \
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


} // namespace detail


} // namespace boleo


#endif // BOLEO_CONFIG_HPP_

