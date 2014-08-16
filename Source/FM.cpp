//
//  FM.cpp
//  FMCalculator
//
//  Created by Shu-Cheng Allen Wu on 8/14/14.
//
//

#include "FM.h"

class MyArraySorter
{
public:
    static int compareElements(double a, double b)
    {
        if (a < b)
            return -1;
        else if (a > b)
            return 1;
        else // if a == b
            return 0;
    }
};


FM::FM(double carrier, double cmratio, double index)
{
		_carrier = carrier;
		_cmRatio = cmratio;
		_index = index;
		runFM();
}

void FM::setCarrier(double freq)
{
		_carrier = freq;
}

double FM::getCarrier()
{
		return _carrier;
}

void FM::setCMRatio(double ratio)
{
		_cmRatio = ratio;
}

double FM::getModulator()
{
		return _cmRatio;
}

void FM::setIndex(double index)
{
		_index = index;
}

double FM::getIndex()
{
		return _index;
}

Array<double> FM::getSpectrum()
{
		return _spectrum;
}

void FM::runFM()
{
		MyArraySorter sorter;
		for(int i=0; std::abs(jn(i, _index)) > 0.1 || std::abs(jn(i+1, _index)) > 0.1 || std::abs(jn(i+2, _index)) > 0.1 ; i++)
		{
				double upperSideBand, lowerSideBand;
				upperSideBand = _carrier + ( i * _cmRatio * _carrier);
				lowerSideBand = _carrier - ( i * _cmRatio * _carrier);
				
				if (upperSideBand < 4187) {
						_spectrum.addIfNotAlreadyThere(upperSideBand);
				};
				
				if (std::abs(lowerSideBand) > 20 && std::abs(lowerSideBand) < 4187){
						_spectrum.addIfNotAlreadyThere(abs(lowerSideBand));
				};
		}
		_spectrum.sort(sorter);
}

