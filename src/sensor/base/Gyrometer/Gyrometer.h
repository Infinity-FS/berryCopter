#ifndef __GYROMETER_H_INCLUDED__
#define __GYROMETER_H_INCLUDED__

#include "../Vector/Vector3.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

class Gyrometer {
    public:
        Gyrometer(short t_GyrometerRange, short t_offsetRange_G, int t_calibrationMeanIterations, int t_calibrationMeanDelay, int t_calibrationMaxError);
        virtual ~Gyrometer() {}

        void calibrateGyrometer();
        void updateGyrometerMean();


        Vector3<short> getGyrometerVector3();
        short getGyrometerRange();

        virtual void readGyrometer() = 0;
        virtual void readGyrometerOffset(Vector3<short> &t_offset) = 0;
        virtual void writeGyrometerOffset (Vector3<short> &t_offset) = 0;

    protected:
        Vector3<short> gyrometerVector3;
        Vector3<double> meanGyrometerVector3;

        short GyrometerRange, GyrometerOffsetRange; // in G

    private:
        int calibrationMeanIterations, calibrationMeanDelay, calibrationMaxError;

        bool adjustGyrometerOffset(Vector3<short> &r_offset);
};

#endif //__GYROMETER_H_INCLUDED__
