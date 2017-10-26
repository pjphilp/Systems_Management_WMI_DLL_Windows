//****************************************************************************
//
//    Copyright 2017 by WinSystems Inc.
//
//    Permission is hereby granted to the purchaser of WinSystems GPIO cards
//    and CPU products incorporating a GPIO device, to distribute any binary
//    file or files compiled using this source code directly or in any work
//    derived by the user from this file. In no case may the source code,
//    original or derived from this file, be distributed to any third party
//    except by explicit permission of WinSystems. This file is distributed
//    on an "As-is" basis and no warranty as to performance or fitness of pur-
//    poses is expressed or implied. In no case shall WinSystems be liable for
//    any direct or indirect loss or damage, real or consequential resulting
//    from the usage of this source code. It is the user's sole responsibility
//    to determine fitness for any considered purpose.
//
///****************************************************************************
//
//    Name       : TemperatureSensor.cpp
//
//    Project    : System Management on PX1-C415
//
//    Author     : pjp
//
//    Description:
//      This module contains the implementation of the TemperatureSensor
//      class.
//
///****************************************************************************
//
//      Date      Revision    Description
//    --------    --------    ---------------------------------------------
//    06/16/17      0.1       Original Release
//
///****************************************************************************

#include "stdafx.h"
#include <comutil.h>
#include <wbemidl.h>
#include <afxpriv.h>

#include <vector>
#include <iostream>
using namespace std;

#include <x86_64_port.h>
#include <WinSys_Errors.h>

#include <WMI_LocatorServices.h>
#include "TemperatureSensor.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////


//****************************************************************************
//
//  Function:  CTemperatureSensor
//
//! \brief      Standard constructor
//
//! @param[in]  pLocSvcs    Pointer to a WMI locator services object
//
//! \return     void
//
//  Notes:
//
//****************************************************************************
CTemperatureSensor::CTemperatureSensor( CWMI_LocatorServices  *pLocSvcs )
    : m_LastError( S_OK )
    , m_SensorCount( 0 )
{
   HRESULT Result;

   if ( pLocSvcs )
       {
          m_pLocatorServices = pLocSvcs;

          CComPtr< IEnumWbemClassObject > pEnumerator;

          Result = m_pLocatorServices->GetServicesPtr()->ExecQuery( BSTR( QUERY_LANG_WQL ), BSTR( CLASS_NAME ), WBEM_FLAG_BIDIRECTIONAL, NULL, &pEnumerator );

          if ( FAILED( Result ) )
              {
                 m_LastError = Result;
              }
          else
              {
                 //
                 // get the sensor name from the object...
                 //

                 CComPtr< IWbemClassObject > ObjectString = NULL;
                 ULONG                       RetCnt;
                 _variant_t                  VarVal;

                 Result = pEnumerator->Next( WBEM_INFINITE, 1L, reinterpret_cast<IWbemClassObject**>( &ObjectString ), &RetCnt );
                 while ( Result == S_OK )
                 {
                    if ( RetCnt != 0 )
                        {
                           P_TEMP_SENSOR_STRUCT_TYPE pSensorStruct = new( TEMP_SENSOR_STRUCT_TYPE );

                           Result = ObjectString->Get( TEMP_SENSOR_NAME_PROPERTY, 0, &VarVal, NULL, NULL );
                           if ( Result == S_OK )
                               {
                                  pSensorStruct->pSensorName = new CString( VarVal.bstrVal );
                               }
                           else
                               {
                                  m_LastError = Result;
                               }

                           Result = ObjectString->Get( TEMP_SENSOR_PROPERTY, 0, &VarVal, NULL, NULL );
                           if ( Result == S_OK )
                               {
                                  pSensorStruct->SensorValue = ( ( ( double )( VarVal.lVal ) ) / 10.0 );
                               }
                           else
                               {
                                  m_LastError = Result;
                               }

                           m_SensorVector.push_back( *pSensorStruct );
                           m_SensorCount++;
                           delete( pSensorStruct );
                        }
                    else
                        {
                           m_LastError = Result;
                        }

                    ObjectString = NULL;
                    Result = pEnumerator->Next( WBEM_INFINITE, 1L, reinterpret_cast<IWbemClassObject**>( &ObjectString ), &RetCnt );
                 }
              }
       }
   else
       {
          m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_TEMPERATURE_SENSOR_CLASS, STATUS_NULL_POINTER );
       }
}

//***************************************************************************
//
//  Function:  ~CTemperatureSensor
//
//! \brief      Standard destructor
//
//! \return     void
//
//  Notes:
//
//***************************************************************************
CTemperatureSensor::~CTemperatureSensor()
{
   uint8_t  i;

   for ( i = m_SensorCount; i > 0; i-- )
   {
      delete( m_SensorVector[ i - 1 ].pSensorName );
      m_SensorVector.pop_back();
   }
}

//***************************************************************************
//
//  Function:  UpdateTemperatureSensors
//
//! \brief     Updates the temperature values for all temperature sensors
//
//! \return    HRESULTS Error result of method
//
//! \note
//
//***************************************************************************
HRESULT CTemperatureSensor::UpdateTemperatureSensors( void )
{
   HRESULT Result;

   CComPtr< IEnumWbemClassObject > pEnumerator;

   Result = m_pLocatorServices->GetServicesPtr()->ExecQuery( BSTR( QUERY_LANG_WQL ), BSTR( CLASS_NAME ), WBEM_FLAG_BIDIRECTIONAL, NULL, &pEnumerator );

   if ( FAILED( Result ) )
       {
          m_LastError = Result;
       }
   else
       {
          //
          // interate thru pEnumerator looking for the OS Name...
          //

          CComPtr< IWbemClassObject > ObjectString = NULL;
          ULONG                       RetCnt;
          uint8_t                     Index = 0;
          _variant_t                  VarVal;
          bool                        GotTemperature = FALSE;

          Result = pEnumerator->Next( WBEM_INFINITE, 1L, reinterpret_cast<IWbemClassObject**>( &ObjectString ), &RetCnt );

          while ( ( Result == S_OK ) && ( Index < m_SensorCount ) )
          {
             Result = ObjectString->Get( TEMP_SENSOR_PROPERTY, 0, &VarVal, NULL, NULL );

             if ( SUCCEEDED( Result ) )
                 {
                    m_SensorVector[ Index++ ].SensorValue = ( ( ( double ) VarVal.lVal ) / 10.0 );
                    GotTemperature = TRUE;
                 }
             else
                 {
                    m_LastError = Result;
                 }

             ObjectString = NULL;
             Result = pEnumerator->Next( WBEM_INFINITE, 1L, reinterpret_cast<IWbemClassObject**>( &ObjectString ), &RetCnt );
          }

          if ( GotTemperature == TRUE )
          {
             Result = S_OK;
          }
       }

   return Result;
}

//***************************************************************************
//
//  Function:  GetTemperatureSensorName
//
//! \brief      Gets the name of the specified sensor
//
//! @param[in]      Index  index of type uint8_t of specified temperature
//!                 sensor
//! @param[in,out]  pSensorName of type CString * Pointer to CString to hold
//!                 name of indexed sensor
//! \return         HRESULTS Error result of method
//
//***************************************************************************
HRESULT CTemperatureSensor::GetTemperatureSensorName( uint8_t Index, CString *pSensorName )
{
   HRESULT Result = S_OK;

   if ( pSensorName == 0 )
       {
          Result = m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_TEMPERATURE_SENSOR_CLASS, STATUS_NULL_POINTER );
       }
   else
       {
          if ( ( Index >= 0 ) && ( Index < m_SensorCount ) )
              {
                 *pSensorName = *m_SensorVector[ Index ].pSensorName;
              }
          else
              {
                 Result = m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_TEMPERATURE_SENSOR_CLASS, STATUS_INDEX_OUT_OF_RANGE );
              }
       }

   return Result;
}

//***************************************************************************
//
//  Function:  GetSensorCount
//
//! \brief      Gets the count of temperature sensors
//
//! @param[in,out]   pSensorCount  Pointer to uint8_t to hold return value
//! \return          HRESULTS Error result of method
//
//***************************************************************************
HRESULT CTemperatureSensor::GetSensorCount( uint8_t *pSensorCount )
{
   HRESULT Result = S_OK;

   if ( pSensorCount )
       {
          *pSensorCount = m_SensorCount;
       }
   else
       {
          Result = m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_TEMPERATURE_SENSOR_CLASS, STATUS_NULL_POINTER );
       }

   return Result;
}

//***************************************************************************
//
//  Function:  GetLatestTemperature
//
//! \brief      Get the latest temperature reading from the specified sensor
//
//! @param[in]       Index index of type uint8_t of sensor
//! @param[in,out]   pLatestTemperature pointer to double to contain returned
//!                  value
//
//! \return          HRESULTS Error result of method
//
//! \note            Returned values are in degrees Kelvin
//
//***************************************************************************
HRESULT CTemperatureSensor::GetLatestTemperature( uint8_t Index, double *pLatestTemperature )
{
   HRESULT Result = S_OK;

   if ( ( Index >= 0 ) && ( Index < m_SensorCount ) )
       {
          if ( pLatestTemperature )
              {
                 *pLatestTemperature = m_SensorVector[ Index ].SensorValue;
              }
          else
              {
                 Result = m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_TEMPERATURE_SENSOR_CLASS, STATUS_NULL_POINTER );
              }
       }
   else
       {
          Result = m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_TEMPERATURE_SENSOR_CLASS, STATUS_INDEX_OUT_OF_RANGE );
       }

   return Result;
}

//***************************************************************************
//
//  Function:  GetLastError
//
//!\brief      Returns the last error detected by a class method
//
//!\returns    HRESULTS Error result
//
//***************************************************************************
HRESULT CTemperatureSensor::GetLastError()
{
   return m_LastError;
}
