//
// $Id$
//
/*
    Copyright (C) 2000- $Date$, Hammersmith Imanet Ltd
    This file is part of STIR.

    This file is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This file is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    See STIR/LICENSE.txt for details
*/
/*!
  \file
  \ingroup buildblock

  \brief Declaration of class SinglesRates

  \author Kris Thielemans and Sanida Mustafovic
  $Date$
  $Revision$ 
*/

#ifndef __stir_SinglesRates_H__
#define __stir_SinglesRates_H__

//#include "stir/Array.h"
#include "stir/DetectionPosition.h"
#include "stir/RegisteredObject.h"
#include "stir/Scanner.h"
#include "stir/shared_ptr.h"

#include <vector>

#ifndef STIR_NO_NAMESPACES
using std::vector;
#endif



START_NAMESPACE_STIR






/*
 * A single frame of singles information.
 */
class FrameSinglesRates
{

 public:

    /*
     *! FrameSinglesRates constructor.
     */
    FrameSinglesRates(vector<float>& avg_singles_rates,
                      double start_time,
                      double end_time,
                      shared_ptr<Scanner> scanner);


    //! Get singles rate for a particular singles bin index.
    float get_singles_rate(int singles_bin_index) const;
    
    //! Get singles rate for a detection position.
    float get_singles_rate(const DetectionPosition<>& det_pos) const;

    //! Get the start time of the frame whose rates are recorded.
    double get_start_time() const;
    
    //! Get the end time of the frame whose rates are recorded.
    double get_end_time() const;

    //! Get the scanner information.
    inline const Scanner * get_scanner_ptr() const;

 private:
    
    double _start_time;
    double _end_time;
    vector<float> _singles;
    
    // Scanner specifics
    shared_ptr<Scanner> _scanner_sptr;
    
};







class SinglesRates : public RegisteredObject<SinglesRates>
{
public: 

  virtual ~SinglesRates () {};
  //! Virtual function that return singles rate given the detection positions and/or time or detection 
  virtual float get_singles_rate(const DetectionPosition<>& det_pos, 
				 const double start_time,
				 const double end_time) const =0;
  
  //! Get the scanner pointer
  inline const Scanner * get_scanner_ptr() const;
  

  //! Generate a FramesSinglesRate - containing the average rates
  //  for a frame begining at start_time and ending at end_time.
  //virtual FrameSinglesRates get_rates_for_frame(double start_time,
  //                                              double end_time) const = 0;
  
  
protected:
  shared_ptr<Scanner> scanner_sptr;

};






//
// A set of singles rates for a set of discrete frames.
//
/*
class SinglesFrameRates : public SinglesRates
{

 public:

    // The SinglesRates class constitues the public interface of SinglesFrameRates.
    


 private:

    // The actual array of singles rates. Indexed by frame and singles bin.
    Array<2, float> _singles;
    
    // Time frame definitions.
    vector< pair<double, double> > _frame_times;
    
    // Method to get the start frame index for a start and end time.
    int start_frame(double start_time, double end_time);

    // Method to get the end frame index for a start and end time.
    int end_frame(double start_time, double end_time);
    
};
*/


END_NAMESPACE_STIR

#include "local/stir/SinglesRates.inl"
#endif

