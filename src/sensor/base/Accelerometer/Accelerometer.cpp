#include "Accelerometer.h"

Accelerometer::Accelerometer(short t_AccelerometerRange_G, short t_AccelerometerOffsetRange_G, int t_calibrationMeanIterations, int t_calibrationMeanDelay, int t_calibrationMaxError) :
        AccelerometerRange_G(t_AccelerometerRange_G),
        AccelerometerOffsetRange_G(t_AccelerometerOffsetRange_G),
        calibrationMeanIterations(t_calibrationMeanIterations),
        calibrationMeanDelay(t_calibrationMeanDelay),
        calibrationMaxError(t_calibrationMaxError)
{
}

// ---------
// updateMean
void Accelerometer::updateAccelerometerMean() {
    this->meanAccelerometerAxisData.X = (this->accelerometerAxisData.X + this->meanAccelerometerAxisData.X) / 2;
    this->meanAccelerometerAxisData.Y = (this->accelerometerAxisData.Y + this->meanAccelerometerAxisData.Y) / 2;
    this->meanAccelerometerAxisData.Z = (this->accelerometerAxisData.Z + this->meanAccelerometerAxisData.Z) / 2;
}

// ----------
// calibration
void Accelerometer::calibrateAccelerometer() {
    axisData<short> offset;

    int trial = 0;
    while (true) {
        std::cout << "calibrateAccelerometer trail: " << trial << " x: " << offset.X << " y: " << offset.Y << " z: " << offset.Z << "\n";
        trial++;

        this->writeAccelerometerOffset(offset);

        // read data within x ms time interval
        unsigned int i;
        for (i = 0; i < (unsigned int) this->calibrationMeanIterations; i++) {
            // reads data and updates accelAxisData
            this->readAccelerometer();
            this->updateAccelerometerMean();

            usleep(this->calibrationMaxError);
        }

        if (!this->adjustAccelerometerOffset(offset)) {
            // no adjustment necessary
            break;
        }
    }
}



bool Accelerometer::adjustAccelerometerOffset(axisData<short> &r_offset) {
    int axisComplete = 0;

    double scaleFactor = this->AccelerometerRange_G / this->AccelerometerOffsetRange_G; // If the offset has another range as the measured data
    // X
    if (abs(this->meanAccelerometerAxisData.X) > this->calibrationMaxError) {
        r_offset.X -= (int) ((this->meanAccelerometerAxisData).X * scaleFactor);
        std::cout << "| new accel.X " << r_offset.X << " (" << (this->meanAccelerometerAxisData).X << ") |";
    } else {
        std::cout << "| accel.X OK at " << r_offset.X << " (" << (this->meanAccelerometerAxisData).X << ") |";
        axisComplete++;
    }
    // Y
    if (abs(this->meanAccelerometerAxisData.Y) > this->calibrationMaxError) {
        r_offset.Y -= (int) ((this->meanAccelerometerAxisData).Y * scaleFactor);
        std::cout << "| new accel.Y " << r_offset.Y << " (" << (this->meanAccelerometerAxisData).Y << ") |";
    } else {
        std::cout << "| accel.Y OK at " << r_offset.Y << " (" << (this->meanAccelerometerAxisData).Y << ") |";
        axisComplete++;
    }
    // Z
    int oneG_offsetRange = (pow(2, 15) / this->AccelerometerOffsetRange_G);
    if (abs(this->meanAccelerometerAxisData.Z - oneG_offsetRange) > this->calibrationMaxError) {
        r_offset.Z -= - oneG_offsetRange + ((this->meanAccelerometerAxisData).Z * scaleFactor) ;
        std::cout << "| new accel.Z " << r_offset.Z << " (" << (this->meanAccelerometerAxisData).Z << " @ " << (oneG_offsetRange - (this->meanAccelerometerAxisData).Z) <<") |";
    } else {
        std::cout << "| accel.Z OK at " << r_offset.Z << " (" << (this->meanAccelerometerAxisData).Z << ") |";
        axisComplete++;
    }
    std::cout << "\n";

    if(axisComplete == 3){
        return false;
    } else {
        return true;
    }
}

// ----------
// getters
axisData<short> Accelerometer::getAccelerometerAxisData() {
    return this->accelerometerAxisData;
}

short Accelerometer::getAccelerometerRange_G() {
    return this->AccelerometerRange_G;
}