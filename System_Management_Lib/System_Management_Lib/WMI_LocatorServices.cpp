//****************************************************************************
//
//!   copyright 2017 by WinSystems Inc.
//!
//!    Permission is hereby granted to the purchaser of WinSystems GPIO cards
//!    and CPU products incorporating a GPIO device, to distribute any binary
//!    file or files compiled using this source code directly or in any work
//!    derived by the user from this file. In no case may the source code,
//!    original or derived from this file, be distributed to any third party
//!    except by explicit permission of WinSystems. This file is distributed
//!    on an "As-is" basis and no warranty as to performance or fitness of pur-
//!    poses is expressed or implied. In no case shall WinSystems be liable for
//!    any direct or indirect loss or damage, real or consequential resulting
//!    from the usage of this source code. It is the user's sole responsibility
//!    to determine fitness for any considered purpose.
//
///****************************************************************************
//
//!   \file      : WMI_LocatorServices.h
//
//    Project    : System Management on PX1-C415
//
//!   \author    : pjp
//
//!   \details   :  This module contains the implementation of the WBEM locator
//!                 and services class.
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

#include <atlsafe.h>
#include <comdef.h>

#include <vector>
#include <iostream>
using namespace std;
//using namespace System;

#include <x86_64_port.h>
#include <WinSys_Errors.h>

#include <WMI_LocatorServices.h>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//*******************************************************************************
//
//  Function:   CWMI_LocatorServices
//
//! \brief      Standard constructor
//
//! @param[in]  pNameSpace  a CString pointer to containing the WMI namespace
//
//! \return     void
//
//! \note    This function connects to the WMI server that handles requests for
//!          the specified WMI name space. In addition to establishing the
//!          connection, the constructor also sets up the authoriztion scheme
//!          used to connect to the server
//
//*******************************************************************************
CWMI_LocatorServices::CWMI_LocatorServices( CString *pNameSpace )
    : m_pWbemLoc( NULL )
    , m_pWbemSvc( NULL )
    , m_LastError( S_OK )
{
   HRESULT Result;

   if ( pNameSpace )
       {
          if ( pNameSpace->GetLength() != 0 )
              {
                 bool Remote = FALSE;

                 m_NameSpace = SysAllocString( *pNameSpace );

                 Result = CoCreateInstance( CLSID_WbemLocator,
                                            0,
                                            CLSCTX_INPROC_SERVER,
                                            IID_IWbemLocator,
                                            (LPVOID *) &m_pWbemLoc );

                 if ( FAILED( Result ) )
                     {
                        m_LastError = Result;
                     }
                 else
                     {
                        //
                        // Connect to the root\default namespace with the current user.
                        //

                        Result = m_pWbemLoc->ConnectServer(
                                                              m_NameSpace,                  // namespace
                                                              NULL,                         // User name
                                                              NULL,                         // User password
                                                              0,                            // Locale
                                                              NULL,                         // Security flags
                                                              0,                            // Authority
                                                              0,                            // Context object
                                                              &m_pWbemSvc );                // IWbemServices proxy

                        if ( FAILED( Result ) )
                            {
                               //
                               // could not connect to the namespace server...
                               //

                               m_LastError = Result;
                            }
                        else
                            {
                               //
                               // set security level on WMI connection
                               //

                               Result = CoSetProxyBlanket( m_pWbemSvc,
                                                           RPC_C_AUTHN_WINNT,              // authentication service to be used.
                                                           RPC_C_AUTHZ_NONE,               //
                                                           NULL,                           // server principal name to be used with the authentication service
                                                           RPC_C_AUTHN_LEVEL_CALL,         // authentication level
                                                           RPC_C_IMP_LEVEL_IMPERSONATE,    // impersonation level
                                                           NULL,                           // authentication identity
                                                           EOAC_NONE                       // proxy capabilities
                                                        );

                               if ( FAILED( Result ) )
                               {
                                  //
                                  // failed to set security level for WMI connection
                                  //

                                  m_LastError = Result;
                               }
                            }
                     }
              }
          else
              {
                 m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_WBEM_SERVER_PROPERTIES, STATUS_BAD_PARAMETER );
              }
       }
   else
       {
          m_LastError = WINS_ERROR( WINDOWS_ERROR, WINDOWS_CUSTOMER_CODE, WINSYS_FACILITY_WBEM_SERVER_PROPERTIES, STATUS_NULL_POINTER );
       }
}


//****************************************************************************
//
//  Function:  ~CWMI_LocatorServices
//
//! \brief      Standard destructor
//
//! \return     void
//
//  Notes:
//
//****************************************************************************
CWMI_LocatorServices::~CWMI_LocatorServices()
{
   if ( SysStringLen( m_NameSpace ) != 0 )
   {
      SysFreeString( m_NameSpace );
   }

   if ( m_pWbemSvc )
   {
      m_pWbemSvc->Release();
   }

   if (  m_pWbemLoc )
   {
      m_pWbemLoc->Release();
   }
}

//****************************************************************************
//
//  Function:  GetLocatorPtr
//
//! \brief     Get the WBEM services locator pointer
//
//! \return    IWbemLocator *    Pointer to IWbemLocator
//
//  Notes:
//
//****************************************************************************
IWbemLocator * CWMI_LocatorServices::GetLocatorPtr()
{
   return m_pWbemLoc;
}

//****************************************************************************
//
//  Function:  GetServicesPtr
//
//! \brief     Get the WBEM services pointer
//
//! \return    IWbemServices *    Pointer to IWbemServices
//
// Notes:
//
//****************************************************************************
IWbemServices * CWMI_LocatorServices::GetServicesPtr()
{
   return m_pWbemSvc;
}

//*****************************************************************************/
//                                                                            */
//  Function:  GetLastError                                                   */
//                                                                            */
//!\brief      Get the last error encountered by class                        */
//                                                                            */
//!\return     HRESULT    Error value                                         */
//                                                                            */
// Notes:
//
//*****************************************************************************/
HRESULT CWMI_LocatorServices::GetLastError()
{
   return m_LastError;
}
