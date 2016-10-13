#include "Gyrometer.h"

Gyrometer::Gyrometer(short t_GyrometerRange, short t_GyrometerOffsetRange, int t_calibrationMeanIterations, int t_calibrationMeanDelay, int t_calibrationMaxError) :
        GyrometerRange(t_GyrometerRange),
        GyrometerOffsetRange(t_GyrometerOffsetRange),
        calibrationMeanIterations(t_calibrationMeanIterations),
        calibrationMeanDelay(t_calibrationMeanDelay),
        calibrationMaxError(t_calibrationMaxError)
{
}

// ---------
// updateMean
void Gyrometer::updateGyrometerMean() {
    this->meanGyrometerVector3.X = (this->gyrometerVector3.X + this->meanGyrometerVector3.X) / 2;
    this->meanGyrometerVector3.Y = (this->gyrometerVector3.Y + this->meanGyrometerVector3.Y) / 2;
    this->meanGyrometerVector3.Z = (this->gyrometerVector3.Z + this->meanGyrometerVector3.Z) / 2;
}

// ----------
// calibration
void Gyrometer::calibrateGyrometer() {
    Vector3<short> offset;

    int trial = 0;
    while (true) {
        std::cout << "calibrateGyrometer trail: " << trial << " x: " << offset.X << " y: " << offset.Y << " z: " << offset.Z << " ";
        trial++;

        this->writeGyrometerOffset(offset);

        this->meanGyrometerVector3.X = 0;
        this->meanGyrometerVector3.Y = 0;
        this->meanGyrometerVector3.Z = 0;

        // read data within x ms time interval
        unsigned int i;
        for (i = 0; i < (unsigned int) this->calibrationMeanIterations; i++) {
            // reads data and updates gyroVector3
            this->readGyrometer();
            this->updateGyrometerMean();

            usleep(this->calibrationMaxError);
        }

        if (!this->adjustGyrometerOffset(offset)) {
            // no adjustment necessary
            break;
        }
    }
}



bool Gyrometer::adjustGyrometerOffset(Vector3<short> &r_offset) {
    int axisComplete = 0;

    double scaleFactor = ((double) this->GyrometerRange) / ((double) this->GyrometerOffsetRange); // If the offset has another range as the measured data
    // X
    if (abs(this->meanGyrometerVector3.X) > this->calibrationMaxError) {
        r_offset.X -= (int) ( ((double) (this->meanGyrometerVector3).X) * scaleFactor);
        std::cout << "| new gyro.X " << r_offset.X << " (" << (this->meanGyrometerVector3).X << ") |";
    } else {
        std::cout << "| gyro.X OK at " << r_offset.X << " (" << (this->meanGyrometerVector3).X << ") |";
        axisComplete++;
    }
    // Y
    if (abs(this->meanGyrometerVector3.Y) > this->calibrationMaxError) {
        r_offset.Y -= (int) ( ((double) (this->meanGyrometerVector3).Y) * scaleFactor);
        std::cout << "| new gyro.Y " << r_offset.Y << " (" << (this->meanGyrometerVector3).Y << ") |";
    } else {
        std::cout << "| gyro.Y OK at " << r_offset.Y << " (" << (this->meanGyrometerVector3).Y << ") |";
        axisComplete++;
    }
    // Z
    if (abs(this->meanGyrometerVector3.Z) > this->calibrationMaxError) {
        r_offset.Z -= (int) ( ((double) (this->meanGyrometerVector3).Z) * scaleFactor);
        std::cout << "| new gyro.Z " << r_offset.Z << " (" << (this->meanGyrometerVector3).Z << ") |";
    } else {
        std::cout << "| gyro.Z OK at " << r_offset.Z << " (" << (this->meanGyrometerVector3).Z << ") |";
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
Vector3<short> Gyrometer::getGyrometerVector3() {
    return this->gyrometerVector3;
}

short Gyrometer::getGyrometerRange() {
    return this->GyrometerRange;
}

// ---------
// setters