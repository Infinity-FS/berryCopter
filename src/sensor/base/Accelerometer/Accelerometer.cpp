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
    this->meanAccelerometerVector3.X = (this->accelerometerVector3.X + this->meanAccelerometerVector3.X) / 2;
    this->meanAccelerometerVector3.Y = (this->accelerometerVector3.Y + this->meanAccelerometerVector3.Y) / 2;
    this->meanAccelerometerVector3.Z = (this->accelerometerVector3.Z + this->meanAccelerometerVector3.Z) / 2;
}

// ----------
// calibration
void Accelerometer::calibrateAccelerometer() {
    Vector3<short> offset;

    int trial = 0;
    while (true) {
        std::cout << "calibrateAccelerometer trail: " << trial << " x: " << offset.X << " y: " << offset.Y << " z: " << offset.Z << " ";
        trial++;

        this->writeAccelerometerOffset(offset);

        this->meanAccelerometerVector3.X = 0;
        this->meanAccelerometerVector3.Y = 0;
        this->meanAccelerometerVector3.Z = 0;

        // read data within x ms time interval
        unsigned int i;
        for (i = 0; i < (unsigned int) this->calibrationMeanIterations; i++) {
            // reads data and updates accelVector3
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



bool Accelerometer::adjustAccelerometerOffset(Vector3<short> &r_offset) {
    int axisComplete = 0;

    double scaleFactor = ((double) this->AccelerometerRange_G) / ((double) this->AccelerometerOffsetRange_G); // If the offset has another range as the measured data
    // X
    if (abs(this->meanAccelerometerVector3.X) > this->calibrationMaxError) {
        r_offset.X -= (int) ( ((double) (this->meanAccelerometerVector3).X) * scaleFactor);
        std::cout << "| new accel.X " << r_offset.X << " (" << (this->meanAccelerometerVector3).X << ") |";
    } else {
        std::cout << "| accel.X OK at " << r_offset.X << " (" << (this->meanAccelerometerVector3).X << ") |";
        axisComplete++;
    }
    // Y
    if (abs(this->meanAccelerometerVector3.Y) > this->calibrationMaxError) {
        r_offset.Y -= (int) ( ((double) (this->meanAccelerometerVector3).Y) * scaleFactor);
        std::cout << "| new accel.Y " << r_offset.Y << " (" << (this->meanAccelerometerVector3).Y << ") |";
    } else {
        std::cout << "| accel.Y OK at " << r_offset.Y << " (" << (this->meanAccelerometerVector3).Y << ") |";
        axisComplete++;
    }
    // Z
    int oneG_offsetRange = (pow(2, 15) / this->AccelerometerOffsetRange_G);
    int oneG = (pow(2, 15) / this->AccelerometerRange_G);
    if (abs(this->meanAccelerometerVector3.Z - oneG) > this->calibrationMaxError) {
        r_offset.Z -= - oneG_offsetRange + ( ((double) (this->meanAccelerometerVector3).Z) * scaleFactor) ;
        std::cout << "| new accel.Z " << r_offset.Z << " (" << (this->meanAccelerometerVector3).Z << " @ " << (oneG - (this->meanAccelerometerVector3).Z) <<") |";
    } else {
        std::cout << "| accel.Z OK at " << r_offset.Z << " (" << (this->meanAccelerometerVector3).Z << ") |";
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
Vector3<short> Accelerometer::getAccelerometerVector3() {
    return this->accelerometerVector3;
}

short Accelerometer::getAccelerometerRange_G() {
    return this->AccelerometerRange_G;
}