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


#include "boleo/detail/common.hpp"

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

    for (uint32_t i = 0; i != cloud->num_points; ++i)
    {
        const PointType & BOLEO_RESTRICT tango_point = cloud->points[i];
        result[i] = converter( tango_point );
    }

    return result;
}


} // namespace boleo


#endif // BOLEO_PCL_HPP_

