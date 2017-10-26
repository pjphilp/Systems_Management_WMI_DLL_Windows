//****************************************************************************
//
//!  \copyright 2017 by WinSystems Inc.
//!
//!    Permission is hereby granted to the purchaser of WinSystems CPU products
//!    to distribute any binary file or files compiled using this source code
//!    directly or in any work derived by the user from this file. In no case
//!    may the source code, original or derived from this file, be distributed
//!    to any third party except by explicit permission of WinSystems. This file
//!    is distributed on an "As-is" basis and no warranty as to performance or
//!    fitness of purposes is expressed or implied. In no case shall WinSystems
//!    be liable for any direct or indirect loss or damage, real or consequential
//!    resulting from the usage of this source code. It is the user's sole re-
//!    sponsibility to determine fitness for any considered purpose.
//
///****************************************************************************
//
//! \file       TemperatureSensor.h
//
//  Project     System Management on PX1-C415
//
//! \brief      This module contains the definition of the temperature sensors
//
//! \author     pjp
//!
//! \version    0.1
//!
//! \date       06/16/17
//
//****************************************************************************

#pragma once

//////////////////////////////////////////////////////////////////////////////
//
//!
//! \class CTemperatureSensor
//!        The CTemperatureSensor class encapsulates the WMI temperature
//!        sensor object.
//
class AFX_EXT_CLASS CTemperatureSensor
{
public:
   //! constructor
   CTemperatureSensor( CWMI_LocatorServices * pLocSvcs );
   //! destructor
   ~CTemperatureSensor();

private:

//! \struct _TEMP_SENSOR_STRUCT
//! \brief  A structure to encapsulate a temperature sensor's properties
//
   struct _TEMP_SENSOR_STRUCT {
                                 uint8_t       Index;
                                 CString      *pSensorName;
                                 double        SensorValue;
                              };

//! \typedef  TEMP_SENSOR_STRUCT_TYPE
//! \brief  A typedef of the temperature sensor structure
//
   typedef  _TEMP_SENSOR_STRUCT         TEMP_SENSOR_STRUCT_TYPE;

//! \typedef  P_TEMP_SENSOR_STRUCT_TYPE
//! \brief  And typedef of a pointer to temperature sensor structure
//
   typedef  _TEMP_SENSOR_STRUCT      *  P_TEMP_SENSOR_STRUCT_TYPE;

    CWMI_LocatorServices              *m_pLocatorServices;        //!< pointer to WMI locator services. See WMI_LocatorService.h
    uint8_t                            m_SensorCount;             //!< count of temperature sensors reported by WMI
    HRESULT                            m_LastError;               //!< contains the value of the last error encountered by the class
    vector<TEMP_SENSOR_STRUCT_TYPE>    m_SensorVector;            //!< a vector of the TEMP_SENSOR_STRUCT_TYPE

public:
   HRESULT            GetLastError( void );
   HRESULT            UpdateTemperatureSensors( void );                                   // Updates all the temperature sensor values
   HRESULT            GetTemperatureSensorName( uint8_t Index, CString *pSensorName );    // Returns the name of the indicated temperature sensor
   HRESULT            GetSensorCount( uint8_t *pSensorCount );                            // Returns the count of temperature sensors managed by WMI
   HRESULT            GetLatestTemperature( uint8_t Index, double *pLatestTemperature );  // Returns the latest temperature for the indicated sensor

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// strings used with the WMI functions
//
#define NAMESPACE                   L"root\\cimv2"                                                              //!< namespace where the TZ0 temperature sensor is located
#define CLASS_NAME                  L"SELECT * FROM Win32_PerfFormattedData_Counters_ThermalZoneInformation"    //!< class name to read from namespace
#define TEMP_SENSOR_PROPERTY        L"HighPrecisionTemperature"                                                 //!< value property within class
#define TEMP_SENSOR_NAME_PROPERTY   L"Name"                                                                     //!< nameproperty within class
#define QUERY_LANG_WQL              L"WQL"                                                                      //!< query language



