/***************************************************************************
 *
 * xsens.cpp
 *
 * TU Berlin -- Fachgebiet Regelungssysteme
 *  -> Dateibeschreibung:  Xsens implementation
 *  -> Author:             Dorn
 *
 * SVN revision information:
 * @version $Revision: 169 $:
 * @Author  $Author: dorn $:
 * @date    $Date: 2015-12-09 12:47:57 +0100 (Mi, 09 Dez 2015) $:
 * @url     $HeadURL: https://files.control.tu-berlin.de/svn/Matlab/simulink_libraries/Libraries/Lib_Xsens/src/xsens.cpp $:
 *
 */

#include "xsens.h"
#include "helperclasses.h"
#include <math.h>

XsensDriver::XsensDriver()
{
   //Create circular buffers for additionally connected sensors
   for (int i = 0; i < SENSORS_MAX; i++)
   {
       sensorDataBuffer[i].set_capacity(SAMPLERATE_MAX);
       previousData[i].last = -1;
   }
   sensorsToWaitFor = 0;
   
   connectedWirelessMasterCount = 0;
   connectedMTXCount = 0;
   connectedMTWCount = 0;
   connectedMTCount = 0;  
   
   initSuccess = false;
   
   useCalibratedValues = false;
}

XsensDriver::~XsensDriver()
{
    //delete sensorData;
    //delete previousData;
    //delete interpolatedData;
    //delete sensorDeviceIds;
    //delete sensorAccepted;
    //delete sensorsToWaitFor;
    //delete desiredUpdateRate;
    //delete sensorDataBuffer;
    //delete circularMutex;
}

void XsensDriver::setWirelessMasterName(char * port)
{
    wirelessMasterName = port;
    printf("setWirelessMasterName %s\n", wirelessMasterName);
}

void XsensDriver::setWiredPortName(unsigned int index, char * port)
{
    wiredPortName[index] = port;
    printf("setWiredPortName[%i] %s\n", index, wiredPortName[index]);
}

void XsensDriver::setCalibratedValues(bool onoff)
{
    useCalibratedValues = onoff;
}

int XsensDriver::setSampleFrequency(unsigned int frequency)
{
    if (sensorsToWaitFor == 0)
        printf("Sensoren noch nicht gesetzt. Keine Ueberpruefung der Samplingrate moeglich\n");

    if ( (frequency < 5) || (frequency > 150) )
    {
        printf("Frequency out of range...setting frequency to 50Hz\n");
        desiredUpdateRate = 50;
    }
    else
    {
        desiredUpdateRate = frequency;	// Use this update rate for MTWs

        if ((sensorsToWaitFor == 1) && (frequency > 150))
        {
            printf("Setze empfohlene maximale SamplingFrequenz von 150 Hz\n");
            desiredUpdateRate = 150;	// Use this update rate for MTWs
        }
        if ((sensorsToWaitFor == 2) && (frequency > 120))
        {
            printf("Setze empfohlene maximale SamplingFrequenz von 120 Hz\n");
            desiredUpdateRate = 120;	// Use this update rate for MTWs
        }
        if (((sensorsToWaitFor >= 3) && (sensorsToWaitFor <= 4)) && (frequency > 100))
        {
            printf("Setze empfohlene maximale SamplingFrequenz von 100 Hz\n");
            desiredUpdateRate = 100;	// Use this update rate for MTWs
        }
        if (((sensorsToWaitFor >= 5) && (sensorsToWaitFor <= 7)) && (frequency > 75))
        {
            printf("Setze empfohlene maximale SamplingFrequenz von 75 Hz\n");
            desiredUpdateRate = 75;	// Use this update rate for MTWs
        }
        if (((sensorsToWaitFor >= 8) && (sensorsToWaitFor <= 12)) && (frequency > 50))
        {
            printf("Setze empfohlene maximale SamplingFrequenz von 50 Hz\n");
            desiredUpdateRate = 50;	// Use this update rate for MTWs
        }
        if (((sensorsToWaitFor >= 13) && (sensorsToWaitFor <= 18)) && (frequency > 40))
        {
            printf("Setze empfohlene maximale SamplingFrequenz von 40 Hz\n");
            desiredUpdateRate = 40;	// Use this update rate for MTWs
        }
    }
}

int XsensDriver::setSensors(unsigned int anzahl, unsigned long int *sensors)
{
    sensorsToWaitFor = anzahl; // If we found this no of sensors attached to the wireless master we're done with init()
    printf("Sensors to wait for: %d\n", sensorsToWaitFor);

    for (int i = 0; i < anzahl; i++)
    {
        sensorDeviceIds[i] = sensors[i];
        sensorAccepted[i] = false;
        printf("Konfigurierter Sensor[%i] %i \n", i, sensorDeviceIds[i] );
    }
}

bool XsensDriver::getInitSuccess()
{
    return initSuccess;
}

void XsensDriver::calcGyroAccData(int sensor)
{
    float samplerate = 1.0f / desiredUpdateRate;

///************************************************************************************************************
    sensorData[sensor].gyro_x = 2 * acos(sensorData[sensor].ori_inc_w) * sensorData[sensor].ori_inc_x /
                                sqrt(1 - sensorData[sensor].ori_inc_w * sensorData[sensor].ori_inc_w) / samplerate;

    if (__builtin_isnan(sensorData[sensor].gyro_x))
        sensorData[sensor].gyro_x = 0;

    sensorData[sensor].acc_x = sensorData[sensor].vel_inc_x / samplerate;

    if (__builtin_isnan(sensorData[sensor].acc_x))
        sensorData[sensor].acc_x = 0;
///************************************************************************************************************
    sensorData[sensor].gyro_y = 2 * acos(sensorData[sensor].ori_inc_w) * sensorData[sensor].ori_inc_y /
                                sqrt(1 - sensorData[sensor].ori_inc_w * sensorData[sensor].ori_inc_w) / samplerate;

    if (__builtin_isnan(sensorData[sensor].gyro_y))
        sensorData[sensor].gyro_y = 0;

    sensorData[sensor].acc_y = sensorData[sensor].vel_inc_y / samplerate;

    if (__builtin_isnan(sensorData[sensor].acc_y))
        sensorData[sensor].acc_y = 0;
///************************************************************************************************************
    sensorData[sensor].gyro_z = 2 * acos(sensorData[sensor].ori_inc_w) * sensorData[sensor].ori_inc_z /
                                sqrt(1 - sensorData[sensor].ori_inc_w * sensorData[sensor].ori_inc_w) / samplerate;

    if (__builtin_isnan(sensorData[sensor].gyro_z))
        sensorData[sensor].gyro_z = 0;

    sensorData[sensor].acc_z = sensorData[sensor].vel_inc_z / samplerate;

    if (__builtin_isnan(sensorData[sensor].acc_z))
        sensorData[sensor].acc_z = 0;
///************************************************************************************************************
}

unsigned long int XsensDriver::getBufferedDataAmount(int sensor)
{
    return (unsigned long int)sensorDataBuffer[sensor].size();
}

void XsensDriver::getBufferedData(int sensor, double *mySensorData)
{   
    //printf("Es befinden sich %lu Elemente im Buffer fuer Sensor %i.\n", (unsigned long int)sensorDataBuffer[sensor].size(), sensor);

    //pthread_mutex_lock(&circularMutex);

    int elements = (int)sensorDataBuffer[sensor].size();

    while (elements > 10)
    {
        sensorDataBuffer[sensor].pop_front();
        elements--;
    }

    // Vermeide Exception!! Outputbuffer ist 10 Datensaetze x 16 Byte = 160 Byte
    if (elements <= 10)
    { // ToDo: Wenn buffer not empty sonst Nullen schreiben!!!
        for (int i = 0; i < elements; i++)
        {
            if (sensor >= sensorsToWaitFor)
            {
                mySensorData[0 + 16 * i] = 0;
                mySensorData[1 + 16 * i] = 0;
                mySensorData[2 + 16 * i] = 0;
                mySensorData[3 + 16 * i] = 0;
                mySensorData[4 + 16 * i] = 0;
                mySensorData[5 + 16 * i] = 0;
                mySensorData[6 + 16 * i] = 0;
                mySensorData[7 + 16 * i] = 0;
                mySensorData[8 + 16 * i] = 0;
                mySensorData[9 + 16 * i] = 0;
                mySensorData[10 + 16 * i] = 0;
                mySensorData[11 + 16 * i] = 0;
                mySensorData[12 + 16 * i] = 0;
                mySensorData[13 + 16 * i] = 0;
                mySensorData[14 + 16 * i] = 0;
                mySensorData[15 + 16 * i] = 0;
            }
            else
            {
                sensor_data Data = sensorDataBuffer[sensor].back();

                mySensorData[0 + 16 * i] = Data.last;
                mySensorData[1 + 16 * i] = Data.acc_x;
                mySensorData[2 + 16 * i] = Data.acc_y;
                mySensorData[3 + 16 * i] = Data.acc_z;
                mySensorData[4 + 16 * i] = Data.gyro_x;
                mySensorData[5 + 16 * i] = Data.gyro_y;
                mySensorData[6 + 16 * i] = Data.gyro_z;
                mySensorData[7 + 16 * i] = Data.mag_x;
                mySensorData[8 + 16 * i] = Data.mag_y;
                mySensorData[9 + 16 * i] = Data.mag_z;
                mySensorData[10 + 16 * i] = Data.ori_w;
                mySensorData[11 + 16 * i] = Data.ori_x;
                mySensorData[12 + 16 * i] = Data.ori_y;
                mySensorData[13 + 16 * i] = Data.ori_z;
                mySensorData[14 + 16 * i] = Data.signal;
                mySensorData[15 + 16 * i] = 0;

                sensorDataBuffer[sensor].pop_back();

                //printf("Index %i: Hole Daten aus Buffer fuer Sensor %i, Last ist %i. Es verbleiben %lu Elemente.\n", i, sensor, Data.last, (unsigned long int)sensorDataBuffer[sensor].size());
            }
        }
    }
    //pthread_mutex_unlock(&circularMutex);
}

void XsensDriver::getNewestData(int sensor, double *mySensorData)
{        
    mySensorData[0] = sensorData[sensor].last;
    mySensorData[1] = sensorData[sensor].acc_x;
    mySensorData[2] = sensorData[sensor].acc_y;
    mySensorData[3] = sensorData[sensor].acc_z;
    mySensorData[4] = sensorData[sensor].gyro_x;
    mySensorData[5] = sensorData[sensor].gyro_y;
    mySensorData[6] = sensorData[sensor].gyro_z;
    mySensorData[7] = sensorData[sensor].mag_x;
    mySensorData[8] = sensorData[sensor].mag_y;
    mySensorData[9] = sensorData[sensor].mag_z;
    mySensorData[10] = sensorData[sensor].ori_w;
    mySensorData[11] = sensorData[sensor].ori_x;
    mySensorData[12] = sensorData[sensor].ori_y;
    mySensorData[13] = sensorData[sensor].ori_z;
    mySensorData[14] = sensorData[sensor].signal;
    mySensorData[15] = 0;

//     printf("Get newest data from Sensor %i. Time = %d.\n", sensor, (unsigned int)mySensorData[0]);
}

int XsensDriver::initXs()
{
    int desiredRadioChannel = RADIO_CHANNEL;	// Use this radio channel for wireless master.

    std::cout << "Verifying serial key..." << std::endl;
    if (!setSerialKey()) {
        std::cout << "Invalid serial key." << std::endl;
        return EXIT_FAILURE;
    }

    initSuccess = true;

    std::cout << "Constructing XsControl..." << std::endl;

    control = XsControl::construct();

    if (control == 0) {
        std::cout << "Failed to construct XsControl instance." << std::endl;
        initSuccess = false;
    }

    try
    {   
        std::cout << "Scanning ports..." << std::endl;
		XsPortInfoArray detectedDevices = XsScanner::scanPorts();

		std::cout << "Finding wireless master..." << std::endl;
		XsPortInfoArray::const_iterator wirelessMasterPort = detectedDevices.begin();
		while (wirelessMasterPort != detectedDevices.end() && !wirelessMasterPort->deviceId().isWirelessMaster()) {
			++wirelessMasterPort;
		}
		if (wirelessMasterPort == detectedDevices.end()) {
			throw std::runtime_error("No wireless masters found");
		}
		std::cout << "Wireless master found @ " << *wirelessMasterPort << std::endl;

		std::cout << "Opening port..." << std::endl;
		if (!control->openPort(wirelessMasterPort->portName().toStdString(), wirelessMasterPort->baudrate())) {
			std::ostringstream error;
			error << "Failed to open port " << *wirelessMasterPort;
			throw std::runtime_error(error.str());
		}
        /*
        std::cout << "Scanning desired port for wireless master..." << std::endl;
        wirelessMasterName = "/dev/Xsens";
        wirelessMasterPort = XsScanner::scanPort(wirelessMasterName);
        XsPortInfoArray detectedDevices = XsScanner::scanPorts();
        */        
       
//***************************************************************************************************************

        if (wirelessMasterPort->deviceId().isWirelessMaster())
        {
            std::cout << "Wireless master found. Serialnumber: " << wirelessMasterPort->deviceId().toString() << std::endl;
            std::cout << "Opening port..." << std::endl;

            if (!control->openPort(wirelessMasterPort->portName().toStdString(), wirelessMasterPort->baudrate()))
            {
                std::ostringstream error;
                error << "Failed to open port " << *wirelessMasterPort;
                throw std::runtime_error(error.str());
            }
            else
            {
                connectedWirelessMasterCount++;
        
                std::cout << "Getting XsDevice instance for wireless master..." << std::endl;
                wirelessMasterDevice = control->device(wirelessMasterPort->deviceId());
                if (wirelessMasterDevice == 0)
                {
                    std::ostringstream error;
                    error << "Failed to construct XsDevice instance: " << *wirelessMasterPort;
                    throw std::runtime_error(error.str());
                }

                std::cout << "XsDevice instance created @ " << *wirelessMasterDevice << std::endl;

                std::cout << "Setting config mode..." << std::endl;
                if (!wirelessMasterDevice->gotoConfig()) {
                    std::ostringstream error;
                    error << "Failed to goto config mode: " << *wirelessMasterDevice;
                    throw std::runtime_error(error.str());
                }

                std::cout << "Attaching callback handler..." << std::endl;
                wirelessMasterDevice->addCallbackHandler(&wirelessMasterCallback);

                std::cout << "Setting update rate to " << desiredUpdateRate << " Hz..." << std::endl;
                if (!wirelessMasterDevice->setUpdateRate(desiredUpdateRate))
                {
                    std::ostringstream error;
                    error << "Failed to set update rate: " << *wirelessMasterDevice;
                    throw std::runtime_error(error.str());
                }

                std::cout << "Setting radio channel to " << desiredRadioChannel << " and enabling radio..." << std::endl;
                if (!wirelessMasterDevice->enableRadio(desiredRadioChannel))
                {
                    std::ostringstream error;
                    error << "Failed to set radio channel: " << *wirelessMasterDevice;
                    throw std::runtime_error(error.str());
                }
            }
        }
        else
            std::cout << "No wireless master found @ " << wirelessMasterName << std::endl;

//***************************************************************************************************************

        // Find an MTi / MTx / MTmk4 device
        std::cout << "Finding wired sensors..." << std::endl;
        std::cout << "Scanning desired ports for wired sensors..." << std::endl;

        XsDevice* device;

        for (int mtPort = 0; mtPort < sensorsToWaitFor; mtPort++)
        {
            if (sensorDeviceIds[mtPort] == 0) // reserviert fuer Kabelsensor
            {
                printf("Pruefe Sensor an Port %s\n", wiredPortName[mtPort]);
                wiredSensorPort = XsScanner::scanPort(wiredPortName[mtPort]);

                if (wiredSensorPort.deviceId().isMtx() || wiredSensorPort.deviceId().isMtMk4())
                {
                    std::cout << "Mtx or MtMk4 found..." << std::endl;
                    std::cout << "Found a device with id: " << wiredSensorPort.deviceId().toString().toStdString() << " @ port: " << wiredSensorPort.portName().toStdString() << ", baudrate: " << wiredSensorPort.baudrate() << std::endl;
                    std::cout << "Opening port..." << std::endl;

                    if (!control->openPort(wiredSensorPort.portName().toStdString(), wiredSensorPort.baudrate()))
                    {
                        std::ostringstream error;
                        error << "Failed to open port " << wiredSensorPort;
                        throw std::runtime_error(error.str());
                    }
                    else
                    {
                        connectedMTXCount++;

                        // Get the device object
                        device = control->device(wiredSensorPort.deviceId());
                        assert(device != 0);

                        // Create and attach callback handler to device
                        //MtxCallback callback;
                        //device->addCallbackHandler(&callback);

                        // Enter sensor serial number at the previously reserved location
                        sensorDeviceIds[mtPort] = strtoul(wiredSensorPort.deviceId().toString().toStdString().c_str(), NULL, 10);

                        // Print information about detected MTi / MTx / MTmk4 device
                        std::cout << "Device: " << device->productCode().toStdString() << " opened." << std::endl;

                        // Put the device in configuration mode
                        std::cout << "Putting device into configuration mode..." << std::endl;

                        if (!device->gotoConfig()) // Put the device into configuration mode before configuring the device
                        {
                            throw std::runtime_error("Could not put device into configuration mode. Aborting.");
                        }

                        // Configure the device. Note the differences between Mtx and MTmk4
                        std::cout << "Configuring the device..." << std::endl;

                        if (device->deviceId().isMtx())
                        {
                            XsOutputMode outputMode = XOM_Calibrated | XOM_Orientation; // output calibrated orientation data
                            XsOutputSettings outputSettings = XOS_Timestamp_PacketCounter | XOS_CalibratedMode_All | XOS_OrientationMode_Quaternion; // output orientation data as quaternion
                            XsDeviceMode deviceMode(desiredUpdateRate); // make a device mode with update rate of desiredUpdateRate
                            deviceMode.setModeFlag(outputMode);
                            deviceMode.setSettingsFlag(outputSettings);

                            // set the device configuration
                            if (!device->setDeviceMode(deviceMode))
                            {
                                throw std::runtime_error("Could not configure MTmki device. Aborting.");
                            }
                        }
                        else if (device->deviceId().isMtMk4())
                        {
                            XsOutputConfiguration quat(XDI_Quaternion, 0);
                            XsOutputConfigurationArray configArray;
                            configArray.push_back(quat);
                            if (!device->setOutputConfiguration(configArray))
                            {

                                throw std::runtime_error("Could not configure MTmk4 device. Aborting.");
                            }
                        }
                        else
                        {
                            throw std::runtime_error("Unknown device while configuring. Aborting.");
                        }

                        // Put the device in measurement mode
                        std::cout << "Putting device into measurement mode..." << std::endl;
                        if (!device->gotoMeasurement())
                        {
                            throw std::runtime_error("Could not put device into measurement mode. Aborting.");
                        }
                    }
                }
            }
        }
        std::cout << "Found " << connectedMTXCount << " wired sensors" << std::endl;

//***************************************************************************************************************

		std::cout << "Waiting for MTW to wirelessly connect...\n" << std::endl;
        
		bool waitForConnections = true;
        
		size_t connectedMTWCount = wirelessMasterCallback.getWirelessMTWs().size();
        
        std::cout << connectedMTWCount << " MTw Connected..." << std::endl;

        if (connectedWirelessMasterCount > 0)
        {
            connectedMTWCount = wirelessMasterCallback.getWirelessMTWs().size();
            connectedMTCount = connectedMTWCount + connectedMTXCount;
        }
        else
            connectedMTCount = connectedMTXCount;

        size_t acceptedSensorCount = 0;
        size_t nextMTWCount = 0;

        bool ran_once = false;
        
        do {
            XsTime::msleep(100);

            while (true)
            {
                if (connectedWirelessMasterCount > 0)
                    nextMTWCount = wirelessMasterCallback.getWirelessMTWs().size();

                // Annahme: Es wurde ein WirelessMaster gefunden
                // Demnach wird nach konnektierbaren MTws gesucht
                // Werden keine gewuenscht, dann ist dies eine Endlosschleife
                // Sollten also auch ohne MTws schon alle gewünschten Sensoren
                // gefunden worden sein, dann kann die Suche abgebrochen werden.
                if (acceptedSensorCount == sensorsToWaitFor)
                    break;
                
                if ( ( (nextMTWCount != connectedMTWCount) && (connectedWirelessMasterCount > 0) ) ||
                     ( (nextMTWCount == 0) && (connectedMTWCount == 0) && (!ran_once) ) )
                {

                    connectedMTWCount = nextMTWCount;
                    connectedMTCount = connectedMTWCount + connectedMTXCount;

                    for (int i = 0; i < connectedMTCount; i++)
                    {
                        std::cout << "Pruefe auf konfigurierte Sensoren..." << std::endl;
                        XsDeviceIdArray allDeviceIds = control->deviceIds();

                        for (XsDeviceIdArray::const_iterator indexSensor = allDeviceIds.begin(); indexSensor != allDeviceIds.end(); ++indexSensor)
                        {
                            if (indexSensor->isMtw() || indexSensor->isMtx() || indexSensor->isMtMk4())
                            {
                                XsDevicePtr mtDevice = control->device(*indexSensor);
                                if (mtDevice != 0)
                                {
                                    for (int j = 0; j < sensorsToWaitFor; j++)
                                    {
                                        if ( ( strtoul(mtDevice->deviceId().toString().toStdString().c_str(), NULL, 16) == sensorDeviceIds[j] ) && ( !sensorAccepted[j] ) )
                                        {
                                            sensorAccepted[j] = true;
                                            printf("Akzeptiere ID %ld\n", strtoul(mtDevice->deviceId().toString().toStdString().c_str(), NULL, 16) );
                                            acceptedSensorCount++;
                                            std::cout << "Number of accepted MTs: " << acceptedSensorCount << std::endl;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    ran_once = true;
                }
                else
                {
                    break;
                }
            }

            // Die Pruefung ist erst dann abgeschlossen, wenn alle mit setSensors() konfigurierten Sensoren
            // durch Abgleich der Seriennummer tatsaechlich auch konnektiert sind. Alle uebrigen erkannten
            // Sensoren werden zwar verbunden, sind aber nicht relevant.
            if (acceptedSensorCount == sensorsToWaitFor)
                waitForConnections = false;
        }
        while (waitForConnections);

        std::cout << "Number of connected MTWs: " << connectedMTWCount << std::endl;
        std::cout << "Number of connected MTXs: " << connectedMTXCount << std::endl;
        std::cout << "Number of connected  MTs: " << connectedMTCount << std::endl;
        std::cout << "Number of accepted   MTs: " << acceptedSensorCount << std::endl;        
        
        // Wireless Master und auch damit verbundene Sensoren anwesend
        if ((connectedWirelessMasterCount > 0) && (connectedMTWCount > 0))
        {
            std::cout << "Master in main() " << *wirelessMasterDevice << "\n";

            std::cout << "Starting measurement..." << std::endl;
            if (!wirelessMasterDevice->gotoMeasurement())
            {
                std::ostringstream error;
                error << "Failed to goto measurement mode: " << *wirelessMasterDevice;
                throw std::runtime_error(error.str());
            }
        }
        
        // Wireless Master ohne Sensoren abschalten
        if ((connectedWirelessMasterCount > 0) && (connectedMTWCount == 0))
        {
            std::cout << "Setting config mode..." << std::endl;
            if (!wirelessMasterDevice->gotoConfig())
            {
                std::ostringstream error;
                error << "Failed to goto config mode: " << *wirelessMasterDevice;
                throw std::runtime_error(error.str());
                initSuccess = false;
                return EXIT_FAILURE;
            }
            else
            {
                std::cout << "Disabling radio... " << std::endl;
                if (!wirelessMasterDevice->disableRadio())
                {
                    std::ostringstream error;
                    error << "Failed to disable radio: " << *wirelessMasterDevice;
                    throw std::runtime_error(error.str());
                    initSuccess = false;
                    return EXIT_FAILURE;
                }
            }            
        }

        std::cout << "Getting XsDevice instances for all MTs..." << std::endl;
        XsDeviceIdArray allDeviceIds = control->deviceIds();

        for (XsDeviceIdArray::const_iterator indexSensor = allDeviceIds.begin(); indexSensor != allDeviceIds.end(); ++indexSensor)
        {
            if (indexSensor->isMtw() || indexSensor->isMtx() || indexSensor->isMtMk4())
            {
                mtDeviceIds.push_back(*indexSensor);
            }
        }

        for (XsDeviceIdArray::const_iterator indexSensor = mtDeviceIds.begin(); indexSensor != mtDeviceIds.end(); ++indexSensor)
        {
            XsDevicePtr mtDevice = control->device(*indexSensor);
            if (mtDevice != 0)
            {   // Diese neuerliche Pruefung ist erforderlich um sicherzustellen,
                // dass keine Luecke in der Reihe der zu nutzenden Sensoren ensteht.
                // Die Indices folgen nicht aufeinander, falls ein Sensor der nicht
                // verwendet werden soll zwischen den zu verwendenden erkannt wird.
                for (int j = 0; j < sensorsToWaitFor; j++)
                {   // Akzeptiertes Device ?
                    if ( ( strtoul(mtDevice->deviceId().toString().toStdString().c_str(), NULL, 16) == sensorDeviceIds[j] ) && ( sensorAccepted[j] ) )                    {   // Ja, Device verwenden
                        mtDevices.insert(mtDevice, j);
                        //mtDevices.push_back(mtwDevice);
                    }
                }
            }
            else
            {
                throw std::runtime_error("Failed to create an MTW XsDevice instance");
            }
        }

        std::cout << "Attaching callback handlers to MTs..." << std::endl;
        mtCallbacks.resize(mtDevices.size());

        for (int indexSensor = 0; indexSensor < (int)mtDevices.size(); ++indexSensor)
        {
            std::cout << "Attaching callback handlers to MT..." << indexSensor << std::endl;
            mtCallbacks[indexSensor] = new MtCallback(indexSensor, mtDevices[indexSensor]);
            mtDevices[indexSensor]->addCallbackHandler(mtCallbacks[indexSensor]);
        }
    }
    catch (std::exception const & ex)
    {
        std::cout << ex.what() << std::endl;
        std::cout << "****ABORT****" << std::endl;
        initSuccess = false;
    }
    catch (...)
    {
        std::cout << "An unknown fatal error has occured. Aborting." << std::endl;
        std::cout << "****ABORT****" << std::endl;
        initSuccess = false;
    }

    return EXIT_SUCCESS;
}

int XsensDriver::runXs()
{
    for (size_t indexSensor = 0; indexSensor < mtCallbacks.size(); ++indexSensor)
    {
        while (mtCallbacks[indexSensor]->dataAvailable())
        {

            XsDataPacket const * packet = mtCallbacks[indexSensor]->getOldestPacket();

            // Set these data for all sensors
            sensorData[indexSensor].ori_w         = packet->orientationQuaternion().w();
            sensorData[indexSensor].ori_x         = packet->orientationQuaternion().x();
            sensorData[indexSensor].ori_y         = packet->orientationQuaternion().y();
            sensorData[indexSensor].ori_z         = packet->orientationQuaternion().z();

            sensorData[indexSensor].mag_x         = packet->calibratedMagneticField().data()[0];
            sensorData[indexSensor].mag_y         = packet->calibratedMagneticField().data()[1];
            sensorData[indexSensor].mag_z         = packet->calibratedMagneticField().data()[2];

            sensorData[indexSensor].sensorIndex   = (unsigned int)indexSensor;
            sensorData[indexSensor].deviceName    = (mtCallbacks[indexSensor]->device().deviceId().toString().toStdString().c_str());

            if (mtCallbacks[indexSensor]->device().deviceId().isMtw())
            {

                // fill these data for wireless sensors only
                
                if (useCalibratedValues) //use Calibrated Values provided by the Xsens Driver (These values are obtained by a very sophisticated process which is not public. Hence, don't use the values if you want to know exactly what is going on)
                {
                    sensorData[indexSensor].acc_x         = packet->calibratedAcceleration().data()[0];
                    sensorData[indexSensor].acc_y         = packet->calibratedAcceleration().data()[1];
                    sensorData[indexSensor].acc_z         = packet->calibratedAcceleration().data()[2];

                    sensorData[indexSensor].gyro_x        = packet->calibratedGyroscopeData().data()[0];
                    sensorData[indexSensor].gyro_y        = packet->calibratedGyroscopeData().data()[1];
                    sensorData[indexSensor].gyro_z        = packet->calibratedGyroscopeData().data()[2];

                    sensorData[indexSensor].first         = packet->frameRange().first();
                    sensorData[indexSensor].last          = packet->frameRange().last();
                    sensorData[indexSensor].count         = packet->frameRange().count();

                    sensorData[indexSensor].signal        = packet->rssi();
                }
                else // Manually calculate values from increments
                {
                    sensorData[indexSensor].vel_inc_x     = packet->sdiData().velocityIncrement()[0];
                    sensorData[indexSensor].vel_inc_y     = packet->sdiData().velocityIncrement()[1];
                    sensorData[indexSensor].vel_inc_z     = packet->sdiData().velocityIncrement()[2];

                    sensorData[indexSensor].ori_inc_w     = packet->sdiData().orientationIncrement().w();
                    sensorData[indexSensor].ori_inc_x     = packet->sdiData().orientationIncrement().x();
                    sensorData[indexSensor].ori_inc_y     = packet->sdiData().orientationIncrement().y();
                    sensorData[indexSensor].ori_inc_z     = packet->sdiData().orientationIncrement().z();

                    sensorData[indexSensor].first         = packet->frameRange().first();
                    sensorData[indexSensor].last          = packet->frameRange().last();
                    sensorData[indexSensor].count         = packet->frameRange().count();

                    sensorData[indexSensor].signal        = packet->rssi();

                    calcGyroAccData(indexSensor);
                    
                }
            }

            if (mtCallbacks[indexSensor]->device().deviceId().isMtx() || mtCallbacks[indexSensor]->device().deviceId().isMtMk4())
            {
                // fill these data for wired sensors only
                sensorData[indexSensor].acc_x         = packet->calibratedAcceleration().data()[0];
                sensorData[indexSensor].acc_y         = packet->calibratedAcceleration().data()[1];
                sensorData[indexSensor].acc_z         = packet->calibratedAcceleration().data()[2];

                sensorData[indexSensor].gyro_x        = packet->calibratedGyroscopeData().data()[0];
                sensorData[indexSensor].gyro_y        = packet->calibratedGyroscopeData().data()[1];
                sensorData[indexSensor].gyro_z        = packet->calibratedGyroscopeData().data()[2];
            }
            
            sensorDataBuffer[indexSensor].push_back(sensorData[indexSensor]);

            //printf("Sensor %i: sensorIndex %i, last %i\n", (int)indexSensor, sensorData[indexSensor].sensorIndex, sensorData[indexSensor].last);

            mtCallbacks[indexSensor]->deleteOldestPacket();
        }
    }
    return 0;
}

int XsensDriver::endXs()
{
    if (connectedWirelessMasterCount > 0)
    {
        std::cout << "Setting config mode..." << std::endl;
        if (!wirelessMasterDevice->gotoConfig())
        {
            std::ostringstream error;
            error << "Failed to goto config mode: " << *wirelessMasterDevice;
            throw std::runtime_error(error.str());
            initSuccess = false;
            return EXIT_FAILURE;
        }
        else
        {
            std::cout << "Disabling radio... " << std::endl;
            if (!wirelessMasterDevice->disableRadio())
            {
                std::ostringstream error;
                error << "Failed to disable radio: " << *wirelessMasterDevice;
                throw std::runtime_error(error.str());
                initSuccess = false;
                return EXIT_FAILURE;
            }
        }
    }

    // Kabelgebundene Sensoren anwesend
    if (connectedMTXCount > 0)
    {
        for (size_t indexSensor = 0; indexSensor < mtCallbacks.size(); ++indexSensor)
        {
            if (!mtCallbacks[indexSensor]->device().deviceId().isMtw())
            {
                XsDevice * mtDevice = control->device(mtCallbacks[indexSensor]->device().deviceId());

                if(!mtDevice->gotoConfig())
                {
                    std::ostringstream error;
                    error << "Failed to goto config mode for wired MT" << mtDevice->portName().toStdString();
                    throw std::runtime_error(error.str());
                    initSuccess = false;
                    return EXIT_FAILURE;
                }
                else
                {
                    control->closePort(mtDevice->portName().toStdString());
                }
            }
        }
    }

    std::cout << "Closing XsControl..." << std::endl;
    control->close();

    std::cout << "Deleting MT callbacks..." << std::endl;
    for (std::vector<MtCallback*>::iterator indexSensor = mtCallbacks.begin(); indexSensor != mtCallbacks.end(); ++indexSensor)
    {
        delete (*indexSensor);
    }
    
    std::cout << "Destroying XsControl Object..." << std::endl;
    control->destruct();    
    
    std::cout << "Successful exit." << std::endl;
    //std::cout << "Press [ENTER] to continue." << std::endl; std::cin.get();

    return EXIT_SUCCESS;
}


