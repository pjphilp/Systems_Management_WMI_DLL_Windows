//****************************************************************************
//
//!\copyright 2017 by WinSystems Inc.
//!
//!  Permission is hereby granted to the purchaser of WinSystems CPU products
//!  to distribute any binary file or files compiled using this source code
//!  directly or in any work derived by the user from this file. In no case
//!  may the source code, original or derived from this file, be distributed
//!  to any third party except by explicit permission of WinSystems. This file
//!  is distributed on an "As-is" basis and no warranty as to performance or
//!  fitness of purposes is expressed or implied. In no case shall WinSystems
//!  be liable for any direct or indirect loss or damage, real or consequential
//!  resulting from the usage of this source code. It is the user's sole re-
//!  sponsibility to determine fitness for any considered purpose.
//
///****************************************************************************
//
//! file       Test_Lib.cpp
//
//  Project    System Management WMI library
//
//! \brief     This is a test application that shows the use of the System
//!            Management DLL
//
//! \author    pjp
//!
//! \version   1.0
//!
//! \date      10/20/17
//!
//****************************************************************************

#include "stdafx.h"

#include <conio.h>            // Windows console routines
#include <x86_64_port.h>      // WinSystems porting include file

#define _WIN32_DCOM
#include <iostream>
#include <vector>
using namespace std;
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

#include <WMI_LocatorServices.h>        // include file for WMI server locator routines
#include <TemperatureSensor.h>          // include file for the WMI temperature sensor
#include <TemperatureUtilities.h>       // utilities to convert temperatures from one format to another

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only application object

CWinApp theApp;

HANDLE  hProcessHeap;           // a handle to the process'es heap

using namespace std;

HRESULT main()
{
    HRESULT RetCode = S_OK;

    HMODULE hModule = ::GetModuleHandle( nullptr );

    if ( hModule != nullptr )
        {
           // initialize MFC and print and error on failure
           if ( ! AfxWinInit( hModule, nullptr, ::GetCommandLine(), 0 ) )
               {
                  wprintf( L"Fatal Error: MFC initialization failed\n" );
                  RetCode = 1;
               }
           else
               {
                  RetCode = CoInitializeEx( 0, COINIT_MULTITHREADED );
                  if ( FAILED( RetCode ) )
                      {
                         wprintf( L"Failed to initialize COM library. Error code = %06d\n", RetCode );
                      }
                  else
                      {
                         //
                         // initializae COM...
                         //

                         RetCode = CoInitializeSecurity(
                                                          NULL,                        // Security descriptor
                                                          -1,                          // COM negotiates authentication service
                                                          NULL,                        // Authentication services
                                                          NULL,                        // Reserved
                                                          RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication level for proxies
                                                          RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation level for proxies
                                                          NULL,                        // Authentication info
                                                          EOAC_NONE,                   // Additional capabilities of the client or server
                                                          NULL );                      // Reserved

                         if ( FAILED( RetCode ) )
                             {
                                wprintf( L"Failed to initialize security. Error code = %06d\n", RetCode );
                                CoUninitialize();
                             }
                         else
                             {
                                //
                                // everything above this line is standard Microsoft code for initializing an AFX/MFC application and
                                // cannot be moved into a subroutine due to exceptions that get thrown during exit...
                                //
                                //******************************************************************************************************

                                double    Temperature;
                                CString   SensorName,
                                          NameSpace( NAMESPACE );
                                uint8_t   Count,
                                          i;

                                CWMI_LocatorServices  CIMV2_Services( &NameSpace );     // the WMI server connection

                                //
                                // Create a temperature sensor object
                                //

                                CTemperatureSensor    TemperatureSensor( &CIMV2_Services ); // the WMI object encapsulating the
                                                                                            // temperature sensor

                                if ( TemperatureSensor.GetSensorCount( &Count ) == S_OK )   // sensor count is determined when the
                                    {                                                       // WMI temperature object is created
                                       if ( Count > 0 )
                                           {
                                              bool Exit = FALSE;

                                              wprintf( L"Press any key to exit...\n" );

                                              while ( ( ! _kbhit() ) && ( Exit != TRUE ) )
                                              {
                                                 if ( TemperatureSensor.UpdateTemperatureSensors() == S_OK )    // update all the sensors
                                                     {
                                                        for ( i = 0; i < Count; i++ )                           // loop through all the sensors...
                                                        {
                                                           if ( ( RetCode = TemperatureSensor.GetTemperatureSensorName( i, &SensorName ) ) == S_OK )        // get sensor name
                                                               {
                                                                  if ( ( RetCode = TemperatureSensor.GetLatestTemperature( i, &Temperature ) ) == S_OK )    // get latest sensor reading
                                                                      {
                                                                         CString TempStr;
                                                                         uint8_t n = SensorName.GetLength();

                                                                         TempStr = SensorName.Mid( 2, n );
                                                                         wprintf( L"\\\\%s = %3.2fø K  %3.2fø C  %3.2fø F\n", ( wchar_t *) TempStr.GetString(), Temperature, KelvinToCelsius( Temperature ), KelvinToFahrenheit( Temperature ) );
                                                                      }
                                                                  else
                                                                      {
                                                                         wprintf( L"Error querying WMI for sensor value for sensor #%d\n", i );
                                                                         Exit = TRUE;
                                                                      }
                                                               }
                                                           else
                                                               {
                                                                  wprintf( L"Error reading temperature sensor #%d\n", i );
                                                                  Exit = TRUE;
                                                               }

                                                           Sleep( 1000 );
                                                        }
                                                     }
                                                 else
                                                     {
                                                        wprintf( L"Error reading temperature sensors\n" );
                                                        Exit = TRUE;
                                                     }
                                              }
                                           }
                                       else
                                           {
                                              wprintf( L"No temperature sensors are managed by WMI\n");
                                           }
                                    }
                                else
                                    {
                                       wprintf( L"Error querying WMI for sensor count\n" );
                                    }
                             }

                         CoUninitialize();
                      }
               }
        }
    else
        {
           // TODO: change error code to suit your needs
           wprintf(L"Fatal Error: GetModuleHandle failed\n");
           RetCode = 1;
        }

    return RetCode;
}
