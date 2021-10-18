#ifndef HELPERCLASSES_H_
#define HELPERCLASSES_H_

/* Copyright (c) Xsens Technologies B.V., 2006-2012. All rights reserved.

      This source code is provided under the MT SDK Software License Agreement
      and is intended for use only by Xsens Technologies BV and
      those that have explicit written permission to use it from
      Xsens Technologies BV.

      THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
      KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
      PARTICULAR PURPOSE.
 */
//#include "/usr/local/include/xsensdeviceapi.h" // The Xsens device API header
#include <xsensdeviceapi.h> // The Xsens device API header
#include "serialkey.h"		// For setSerialKey()
#include "conio.h"			// For non ANSI _kbhit() and _getch()

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <utility>
#include <pthread.h>

/*! \class CriticalSection used for thread synchronization */
class CriticalSection {
#ifdef _MSC_VER
public:
    CriticalSection() {InitializeCriticalSection(&m_CriticalSection);}
    virtual ~CriticalSection() throw() {DeleteCriticalSection(&m_CriticalSection);}
    void enter() {EnterCriticalSection(&m_CriticalSection);}
    void leave() {LeaveCriticalSection(&m_CriticalSection);}

private:
    mutable CRITICAL_SECTION m_CriticalSection;
#else
public:
    CriticalSection() {
      pthread_mutexattr_t mAttr; //create mutex attribute variable
      pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP); // setup recursive mutex for mutex attribute
      pthread_mutex_init(&m_CriticalSection, &mAttr); // Use the mutex attribute to create the mutex
      pthread_mutexattr_destroy(&mAttr); // Mutex attribute can be destroy after initializing the mutex variable
    }
    virtual ~CriticalSection() throw()  {
        pthread_mutex_destroy(&m_CriticalSection);
    }
    void enter() {
        pthread_mutex_lock(&m_CriticalSection);
    }
    void leave() {
        pthread_mutex_unlock(&m_CriticalSection);
    }
private:
    mutable pthread_mutex_t m_CriticalSection;

#endif
};

/*! \class Locker RAII locking object that used CriticalSection */
class Locker
{
public:
    Locker(CriticalSection& criticalSection) : m_criticalSection(&criticalSection) {m_criticalSection->enter();}
    ~Locker() throw() {m_criticalSection->leave();}
    void unlock() {m_criticalSection->leave();}
private:
    CriticalSection* m_criticalSection;
};

/*! \brief Stream insertion operator overload for XsPortInfo */
std::ostream& operator << (std::ostream& out, XsPortInfo const & p)
{
    out << "Port: " << std::setw(2) << std::right << p.portNumber() << " (" << p.portName().toStdString() << ") @ "
        << std::setw(7) << p.baudrate() << " Bd"
        << ", " << "ID: " << p.deviceId().toString().toStdString()
    ;
    return out;
}

/*! \brief Stream insertion operator overload for XsDevice */
std::ostream& operator << (std::ostream& out, XsDevice const & d)
{
    out << "ID: " << d.deviceId().toString().toStdString() << " (" << d.productCode().toStdString() << ")";
    return out;
}

//----------------------------------------------------------------------
// Callback handler for wireless master
//----------------------------------------------------------------------
class WirelessMasterCallback : public XsCallback
{
public:
    typedef std::set<XsDevice*> XsDeviceSet;

    XsDeviceSet getWirelessMTWs() const {
        Locker lock(m_criticalSection);
        return m_connectedMTWs;
    }

protected:
    virtual void onConnectivityChanged(XsDevice* dev, XsConnectivityState newState) {
        Locker lock(m_criticalSection);
        switch (newState)
        {
        case XCS_Disconnected:		/*!< Device has disconnected, only limited informational functionality is available. */
            std::cout << "\nEVENT: MTW Disconnected -> " << *dev << std::endl;
            m_connectedMTWs.erase(dev);
            break;
        case XCS_Rejected:			/*!< Device has been rejected and is disconnected, only limited informational functionality is available. */
            std::cout << "\nEVENT: MTW Rejected -> " << *dev << std::endl;
            m_connectedMTWs.erase(dev);
            break;
        case XCS_PluggedIn:			/*!< Device is connected through a cable. */
            std::cout << "\nEVENT: MTW PluggedIn -> " << *dev << std::endl;
            m_connectedMTWs.erase(dev);
            break;
        case XCS_Wireless:			/*!< Device is connected wirelessly. */
            std::cout << "\nEVENT: MTW Connected -> " << *dev << std::endl;
            m_connectedMTWs.insert(dev);
            break;
        case XCS_File:				/*!< Device is reading from a file. */
            std::cout << "\nEVENT: MTW File -> " << *dev << std::endl;
            m_connectedMTWs.erase(dev);
            break;
        case XCS_Unknown:			/*!< Device is in an unknown state. */
            std::cout << "\nEVENT: MTW Unknown -> " << *dev << std::endl;
            m_connectedMTWs.erase(dev);
            break;
        default:
            std::cout << "\nEVENT: MTW Error -> " << *dev << std::endl;
            m_connectedMTWs.erase(dev);
            break;
        }
    }
private:
    mutable CriticalSection m_criticalSection;
    XsDeviceSet m_connectedMTWs;
};

//----------------------------------------------------------------------
// Callback handler for MTw
// Handles onDataAvailable callbacks for MTW devices
// and MTx devices
//----------------------------------------------------------------------
class MtCallback : public XsCallback
{
public:
    MtCallback(int mtIndex, XsDevice* device) : m_mtIndex(mtIndex), m_device(device) {}

    bool dataAvailable() const {
        Locker lock(m_criticalSection);
        return !m_packetBuffer.empty();
    }

    XsDataPacket const * getOldestPacket() const {
        Locker lock(m_criticalSection);
        XsDataPacket const * packet = &m_packetBuffer.front();
        return packet;
    }

    void deleteOldestPacket() {
        Locker lock(m_criticalSection);
        m_packetBuffer.pop_front();
    }

    int getMtIndex() const {
        return m_mtIndex;
    }

    XsDevice const & device() const {
        assert(m_device != 0);
        return *m_device;
    }

protected:
    virtual void onDataAvailable(XsDevice*, const XsDataPacket* packet)
    {
        Locker lock(m_criticalSection);
        // NOTE: Processing of packets should not be done in this thread.

        m_packetBuffer.push_back(*packet);
        if (m_packetBuffer.size() > 300) {
            std::cout << std::endl;
            deleteOldestPacket();
        }
    }

private:
    mutable CriticalSection m_criticalSection;
    std::list<XsDataPacket> m_packetBuffer;
    int m_mtIndex;
    XsDevice* m_device;
};

XsControl                       *control;

XsPortInfo                      wirelessMasterPort;
XsPortInfo                      wiredSensorPort;
// XsPortInfoArray                 detectedDevices;

// XsPortInfoArray::const_iterator wirelessMasterPort;
XsDevicePtr                     wirelessMasterDevice;
WirelessMasterCallback          wirelessMasterCallback; // Callback for wireless master

XsPortInfoArray::const_iterator mtPort;

XsDeviceIdArray                 mtDeviceIds;
XsDevicePtrArray                mtDevices;

std::vector<MtCallback*>        mtCallbacks; // Callbacks for mt devices

#endif // HELPERCLASSES_H_
