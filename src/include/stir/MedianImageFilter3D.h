//
//
/*!

  \file
  \ingroup ImageProcessor
  \brief Declaration of class stir::MedianImageFilter3D.h

  \author Sanida Mustafovic
  \author Kris Thielemans
  
*/
/*
    Copyright (C) 2000- 2009, Hammersmith Imanet Ltd
    This file is part of STIR.

    SPDX-License-Identifier: Apache-2.0

    See STIR/LICENSE.txt for details
*/

#ifndef __stir_MedianImageFilter3D_H__
#define __stir_MedianImageFilter3D_H__


#include "stir/DataProcessor.h"
#include "stir/MedianArrayFilter3D.h"
#include "stir/DiscretisedDensity.h"
#include "stir/RegisteredParsingObject.h"

START_NAMESPACE_STIR

template <typename coordT> class CartesianCoordinate3D;



/*!
  \ingroup ImageProcessor
  \brief A class in the ImageProcessor hierarchy that implements median 
  filtering.
  
  As it is derived from RegisteredParsingObject, it implements all the 
  necessary things to parse parameter files etc.
 */
template <typename elemT>
class MedianImageFilter3D:
  public 
      RegisteredParsingObject<
	      MedianImageFilter3D<elemT>,
              DataProcessor<DiscretisedDensity<3,elemT> >,
              DataProcessor<DiscretisedDensity<3,elemT> >
	       >
{
 private:
  typedef
    RegisteredParsingObject<
	      MedianImageFilter3D<elemT>,
              DataProcessor<DiscretisedDensity<3,elemT> >,
              DataProcessor<DiscretisedDensity<3,elemT> >
	       >
    base_type;
public:
  static const char * const registered_name; 

  MedianImageFilter3D();

  MedianImageFilter3D(const CartesianCoordinate3D<int>& mask_radius);  
 
private:
  MedianArrayFilter3D<elemT> median_filter;
  int mask_radius_x;
  int mask_radius_y;
  int mask_radius_z;


  virtual void set_defaults();
  virtual void initialise_keymap();

  Succeeded virtual_set_up (const DiscretisedDensity< 3,elemT>& density);
  void virtual_apply(DiscretisedDensity<3,elemT>& density, const DiscretisedDensity<3,elemT>& in_density) const; 
  void virtual_apply(DiscretisedDensity<3,elemT>& density) const; 
};


END_NAMESPACE_STIR


#endif  // MedianImageFilter3D
