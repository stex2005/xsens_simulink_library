/***************************************************************************
 *
 * xsens.h
 *
 * TU Berlin -- Fachgebiet Regelungssysteme
 *  -> Dateibeschreibung:  Xsens implementation
 *  -> Author:             Dorn
 *
 * SVN revision information:
 * @version $Revision: 165 $:
 * @Author  $Author: dorn $:
 * @date    $Date: 2015-12-09 09:39:51 +0100 (Mi, 09 Dez 2015) $:
 * @url     $HeadURL: https://files.control.tu-berlin.de/svn/Matlab/simulink_libraries/Libraries/Lib_Xsens/inc/xsens.h $:
 *
 */

#ifndef XSENS_H_
#define XSENS_H_

#include <boost/circular_buffer.hpp>
#include "config.h"

#include <math.h>

class XsensDriver
{
    public:
        XsensDriver();
        virtual ~XsensDriver();

        int setSensors(unsigned int anzahl, unsigned long int *sensors);
        int setSampleFrequency(unsigned int frequency);
        unsigned long int getBufferedDataAmount(int sensor);
        void getBufferedData(int sensor, double* sensordata);
        void getNewestData(int sensor, double* sensordata);
        void calcGyroAccData(int sensor);
        bool getInitSuccess();
        void setWirelessMasterName(char * devicename);
        void setWiredPortName(unsigned int index, char * devicename);
        void setCalibratedValues(bool onoff);

        int initXs();
        int runXs();
        int endXs();

        typedef struct
        {
            double vel_inc_x;
            double vel_inc_y;
            double vel_inc_z;
            double ori_inc_w;
            double ori_inc_x;
            double ori_inc_y;
            double ori_inc_z;
            double ori_w;
            double ori_x;
            double ori_y;
            double ori_z;
            double mag_x;
            double mag_y;
            double mag_z;
            double acc_x;
            double acc_y;
            double acc_z;
            double gyro_x;
            double gyro_y;
            double gyro_z;                                    
            int first;
            int last;
            int count;
            unsigned int sensorIndex;
            const char *deviceName;
            int signal;
        } sensor_data;

        sensor_data sensorData[SENSORS_MAX];
        sensor_data previousData[SENSORS_MAX];
        sensor_data interpolatedData;
        unsigned int sensorDeviceIds[SENSORS_MAX];
        bool sensorAccepted[SENSORS_MAX];

        unsigned int sensorsToWaitFor;
        unsigned int desiredUpdateRate;

        unsigned int connectedWirelessMasterCount;
        unsigned int connectedMTXCount;
        unsigned int connectedMTWCount;
        unsigned int connectedMTCount;        

private:
        char *wirelessMasterName;
        char *wiredPortName[SENSORS_MAX];
        bool useCalibratedValues;
        bool initSuccess;
        boost::circular_buffer<sensor_data> sensorDataBuffer[SENSORS_MAX];
        pthread_mutex_t circularMutex;
};

#endif // XSENS_H_

