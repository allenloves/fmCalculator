//
//  FM.h
//  FMCalculator
//
//  Created by Shu-Cheng Allen Wu on 8/14/14.
//
//

#ifndef __FMCalculator__FM__
#define __FMCalculator__FM__

#include <iostream>
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"

class FM
{
private:
		double _carrier;
		double _cmRatio;
		double _index;
		Array<double> _spectrum;
		
public:
		FM(double carrier, double cmratio, double index);
		void setCarrier(double freq);
		double getCarrier();
		void setCMRatio(double ratio);
		double getModulator();
		void setIndex(double index);
		double getIndex();
		Array<double> getSpectrum();
		void runFM();
};

#endif /* defined(__FMCalculator__FM__) */
