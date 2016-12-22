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
//! Provides conversion functions for use with PCL (Point Cloud Library).
/*! @file
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BOLEO_PCL_HPP_
#define BOLEO_PCL_HPP_


#include "common.hpp"

extern "C"
{
#   include "tango_client_api.h"
}

#include "pcl/point_types.h"
#include "pcl/point_cloud.h"


    //! Namespace for Boleo.
namespace boleo
{


    //! The type of TangoPointCloud::points[i].
typedef decltype (TangoPointCloud::points[0]) PointType;


    //! Internals.
namespace detail
{
        //! Copies points from a TangoPointCloud to a pcl::PointCloud< T >.
    template<
        typename point_type,    //!< Type of point cloud to create.
        typename converter_type //!< Type of point transfer function.
    >
    void CopyPoints(
        pcl::PointCloud< point_type > &dest,//!< Output cloud.
        const TangoPointCloud *src,         //!< Input cloud.
        const converter_type &converter     //!< Point transfer function inst.
    );
}


    //! A converter from TangoPoint to pcl::InterestPoint.
struct InterestPointConverter
{
    pcl::InterestPoint operator() ( const PointType &point ) const
    {
        pcl::InterestPoint result = { 0 };
        result.x        = point[0];
        result.y        = point[1];
        result.z        = point[2];
        result.strength = point[3];
        return result;
    }
};


    //! Creates a pcl::PointCloud< T > from a TangoPointCloud.
template<
    typename point_type,    //!< Type of point cloud to create.
    typename converter_type //!< Type of point transfer function.
>
pcl::PointCloud< point_type > PointCloud_toPcl(
    const TangoPointCloud *cloud,   //!< Input cloud.
    const converter_type &converter //!< Point transfer function instance.
)
{
    pcl::PointCloud< point_type > result;
    result.resize( cloud->num_points );
    detail::CopyPoints( result, cloud, converter );
    return result;
}


namespace detail
{


    // Generic implementation.
template< typename point_type, typename converter_type >
    void CopyPoints(
        pcl::PointCloud< point_type > &dest,
        const TangoPointCloud *src,
        const converter_type &converter )
{
    for (uint32_t i = 0; i != src->num_points; ++i)
    {
        const PointType & BOLEO_RESTRICT tango_point = src->points[i];
        dest[i] = converter( tango_point );
    }
}


    // Since g++ -O3 doesn't seem to inline ToInterestPoint(), here's a
    //  hard-coded specialization of PointCloud_toPcl< pcl::InterestPoint >().
template<>
    void CopyPoints<
        pcl::InterestPoint,
        InterestPointConverter
    >(
        pcl::PointCloud< pcl::InterestPoint > &dest,
        const TangoPointCloud *src,
        const InterestPointConverter &converter )
{
    for (uint32_t i = 0; i != src->num_points; ++i)
    {
        const PointType & BOLEO_RESTRICT tango_point = src->points[i];
        dest[i] = converter( tango_point );
    }
}


} // namespace detail


} // namespace boleo


#endif // BOLEO_PCL_HPP_

