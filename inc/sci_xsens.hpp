/***************************************************************************
 *
 * sci_xsens.hpp
 *
 * TU Berlin -- Fachgebiet Regelungssysteme
 *  -> Dateibeschreibung:  Xsens for MATLAB
 *  -> Author:             Dorn
 *
 * SVN revision information:
 * @version $Revision: 169 $:
 * @Author  $Author: dorn $:
 * @date    $Date: 2015-12-09 12:47:57 +0100 (Mi, 09 Dez 2015) $:
 * @url     $HeadURL: https://files.control.tu-berlin.de/svn/Matlab/simulink_libraries/Libraries/Lib_Xsens/inc/sci_xsens.hpp $:
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "xsens.h"

/*
 * **********************************************
 */

static void init_xsens(void **work, uint8_t *p1, unsigned int p1len, uint8_t *p2, unsigned int p2len, uint8_t *p3, unsigned int p3len, uint8_t *p4,
                       unsigned int p4len, uint8_t *p5, unsigned int p5len, uint8_t *p6, unsigned int p6len, uint8_t *p7, unsigned int p7len,
                       uint8_t *p8, unsigned int p8len, uint8_t *p9, unsigned int p9len, uint8_t *p10, unsigned int p10len, uint8_t *p11,
                       unsigned int p11len, unsigned int p12, unsigned int p13)
{

#ifdef WITH_HW    
    
    XsensDriver * XSENS = new XsensDriver();

    int retval;
    unsigned long int id[SENSORS_MAX];
    unsigned int sensorCount, iparCount, i, j, frequenz, doppelteSensoren, useCalibratedValues;

    iparCount = 0;
    sensorCount = 0;
    doppelteSensoren = 0;

    for (i = 0; i < SENSORS_MAX; i++)
        id[i] = 0;

    // assign device name from blockmask
    char devicename[p1len + 1];
    for (int i = 0; i < p1len; i++)
    {
        devicename[i] = (char) p1[i];
    }
    devicename[p1len] = '\0';
    printf("Requesting wireless master at: %s  \n", devicename);

    XSENS->setWirelessMasterName(devicename);

    // SensorIDs / SerialPorts aus Blockmaske lesen
    char SensorStrings[SENSORS_MAX][30];
       
    for (int i = 0; i < p2len; i++)
    {
        SensorStrings[0][i] = (char) p2[i];
    }
    SensorStrings[0][p2len] = '\0';   
    
    for (int i = 0; i < p3len; i++)
    {
        SensorStrings[1][i] = (char) p3[i];
    }
    SensorStrings[1][p3len] = '\0';
    
    for (int i = 0; i < p4len; i++)
    {
        SensorStrings[2][i] = (char) p4[i];
    }
    SensorStrings[2][p4len] = '\0';
    
    for (int i = 0; i < p5len; i++)
    {
        SensorStrings[3][i] = (char) p5[i];
    }
    SensorStrings[3][p5len] = '\0';
    
    for (int i = 0; i < p6len; i++)
    {
        SensorStrings[4][i] = (char) p6[i];
    }
    SensorStrings[4][p6len] = '\0';
    
    for (int i = 0; i < p7len; i++)
    {
        SensorStrings[5][i] = (char) p7[i];
    }
    SensorStrings[5][p7len] = '\0';
    
    for (int i = 0; i < p8len; i++)
    {
        SensorStrings[6][i] = (char) p8[i];
    }
    SensorStrings[6][p8len] = '\0';
    
    for (int i = 0; i < p9len; i++)
    {
        SensorStrings[7][i] = (char) p9[i];
    }
    SensorStrings[7][p9len] = '\0';
    
    for (int i = 0; i < p10len; i++)
    {
        SensorStrings[8][i] = (char) p10[i];
    }
    SensorStrings[8][p10len] = '\0';
    
    for (int i = 0; i < p11len; i++)
    {
        SensorStrings[9][i] = (char) p11[i];
    }
    SensorStrings[9][p11len] = '\0';

    // Wenn moeglich in unsigned long (SensorId) umwandeln
    unsigned long int SensorNumbers[SENSORS_MAX];
    for (i = 0; i < SENSORS_MAX; i++)
    {
        SensorNumbers[i] = strtoul(SensorStrings[i], NULL, 16);
        printf("Sensor found: %s\n",SensorStrings[i]);
    }
    
    for (i = 0; i < SENSORS_MAX; i++)
    {
        // There is a number in the field of the mask (SensorId)
        if (SensorNumbers[i] > 0)
        {
            id[sensorCount] = SensorNumbers[i];
            printf("Requesting wireless ID %lu\n", SensorNumbers[i]);
            sensorCount++;
        }
        else
        {
            // The port should not be used or calls a port string
            if (strcmp(SensorStrings[i], "0") == 0)
            {
                printf("Id/Port %s dropped\n", SensorStrings[i]);
            }
            else
            {   
                printf("Requesting wired Port %s\n", SensorStrings[i]);
                XSENS->setWiredPortName(sensorCount, SensorStrings[i]);
                id[sensorCount] = 0;
                sensorCount++;
            }
        }
    }

    frequenz = p12;
   
    useCalibratedValues = p13;

//    for (i = 0; i < sensorCount; i++)
//    {
//        for (j = sensorCount - 1; j > i; j--)
//        {
//            if ((id[i] == id[j]) && (id[i] > 0) && (id[j] > 0))
//            {
//                printf("Sensor ID %ld an den Positionen %i und %i doppelt -> bitte korrigieren\n", id[i], i, j);
//                doppelteSensoren++;
//            }
//        }
//    }

    // Parameteranzahl pruefen
    // Durch ein nicht ausgefuelltes Parameterfeld in XCOS werden weniger Parameter uebergeben, als noetig.
    // 10 Sensoren, ein Flag und eine Samplingrate muessen sein. Nicht genutzte Felder muessen Null (0) sein.
    //if (doppelteSensoren == 0)
    //{
        // Zuerst die Sensoren setzen, um die Samplefrequenz laut Herstellerempfehlung pruefen zu koennen.
        printf("Sensor Count: %d\n",sensorCount);
        XSENS->setSensors(sensorCount, id);
        XSENS->setSampleFrequency(frequenz);
        
   /*******************/
        
        if (useCalibratedValues == 1) 
        {
            XSENS->setCalibratedValues(true);
            printf("Now using Xsens calibrated Values.\n");
        }
        else
        {
            XSENS->setCalibratedValues(false);
            printf("Using raw increment data.\n");
        }

        if ((XSENS->initXs() == EXIT_SUCCESS) && (XSENS->getInitSuccess()))
            printf("Init Successful\n");
        else
            printf("Init Failed\n");
    //}
    //else
        //printf("Parameteranzahl %i zu klein!\n");

    *work = (void *)XSENS;
    
#endif    
    
}

static void output_xsens(void **work, double *y1, double *y2, double *y3, double *y4, double *y5, double *y6, double *y7, double *y8, double *y9, double *y10)
{
    
#ifdef WITH_HW    
    
    XsensDriver * XSENS = (XsensDriver*) (*work);

    int retval;
    unsigned long int i;

    double *sensor1, *sensor2, *sensor3, *sensor4, *sensor5,
           *sensor6, *sensor7, *sensor8, *sensor9, *sensor10;

    if (XSENS->getInitSuccess())
    {
        retval = XSENS->runXs();

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 0, (unsigned long int)XSENS->getBufferedDataAmount(0) );

        sensor1 = y1;

        //XSENS->getBufferedData(0, sensor1);

        XSENS->getNewestData(0, sensor1);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 1, (unsigned long int)XSENS->getBufferedDataAmount(1) );

        sensor2 = y2;

        XSENS->getBufferedData(1, sensor2);

        //XSENS->getNewestData(1, sensor2);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 2, (unsigned long int)XSENS->getBufferedDataAmount(2) );

        sensor3 = y3;

        XSENS->getBufferedData(2, sensor3);

        //XSENS->getNewestData(2, sensor3);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 3, (unsigned long int)XSENS->getBufferedDataAmount(3) );

        sensor4 = y4;

        XSENS->getBufferedData(3, sensor4);

        //XSENS->getNewestData(3, sensor4);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 4, (unsigned long int)XSENS->getBufferedDataAmount(4) );

        sensor5 = y5;

        XSENS->getBufferedData(4, sensor5);

        //XSENS->getNewestData(4, sensor5);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 5, (unsigned long int)XSENS->getBufferedDataAmount(5) );

        sensor6 = y6;

        XSENS->getBufferedData(5, sensor6);

        //XSENS->getNewestData(5, sensor6);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 6, (unsigned long int)XSENS->getBufferedDataAmount(6) );

        sensor7 = y7;

        XSENS->getBufferedData(6, sensor7);

        //XSENS->getNewestData(6, sensor7);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 7, (unsigned long int)XSENS->getBufferedDataAmount(7) );

        sensor8 = y8;

        XSENS->getBufferedData(7, sensor8);

        //XSENS->getNewestData(7, sensor8);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 8, (unsigned long int)XSENS->getBufferedDataAmount(8) );

        sensor9 = y9;

        XSENS->getBufferedData(8, sensor9);

        //XSENS->getNewestData(8, sensor9);

    /*************************************************************************************************************************/

        //printf( "Buffer fuer Sensor %i umfasst %lu Elemente.\n", 9, (unsigned long int)XSENS->getBufferedDataAmount(9) );

        sensor10 = y10;

        XSENS->getBufferedData(9, sensor10);

        //XSENS->getNewestData(9, sensor10);

    /*************************************************************************************************************************/
    }
    else
        printf("Nicht initialisiert, nichts zu tun\n");

#endif    
    
}

static void terminate_xsens(void **work)
{
    
#ifdef WITH_HW    
    
    XsensDriver * XSENS = (XsensDriver*) (*work);

    int retval;

    retval = XSENS->endXs();

    delete XSENS;
    
#endif    
    
}
