////////////////////////////////////////////////////////////////////////////////
//
//  Copyright Matthew A. Gruenke 2017.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//   http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////////////////////
//
//! Defines feature-check macros.
/*! @file
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BOLEO_FEATURES_HPP_
#define BOLEO_FEATURES_HPP_


#ifndef __has_feature
#    define __has_feature(x) 0
#endif


#if defined( __GXX_RTTI ) || __has_feature( cxx_rtti )
#   define BOLEO_HAS_RTTI 1
#else
#   define BOLEO_HAS_RTTI 0
#endif


#endif // BOLEO_FEATURES_HPP_

