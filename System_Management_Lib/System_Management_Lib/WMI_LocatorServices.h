//****************************************************************************
//
//!   \copyright 2017 by WinSystems Inc.
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
//!   \file      WMI_LocatorServices.h
//
//    Project    System Management on PX1-C415
//
//!   \author    pjp
//
//!   \details   This module contains the definitions for the WBEM locator
//!              and services class.
//
///****************************************************************************
//
//      Date      Revision    Description
//    --------    --------    ---------------------------------------------
//    06/16/17      0.1       Original Release
//
///****************************************************************************

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NAMESPACE          L"root\\cimv2"

//!/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//!
//! \class CWMI_LocatorServices
//!        Encapsulates the data and methods used with the WMI functionality
//
class AFX_EXT_CLASS CWMI_LocatorServices
{
public:
   CWMI_LocatorServices( CString *pNameSpace );
   ~CWMI_LocatorServices();

private:
   IWbemLocator        *m_pWbemLoc;        //!< initial namespace pointer to the IWbemServices interface
   IWbemServices       *m_pWbemSvc;        //!< interface used by clients and providers to access WMI services
   BSTR                 m_NameSpace;       //!< namespace string that contains WMI object
   HRESULT              m_LastError;       //!< contains the value of the last error detected during execution of class methods

public:
   IWbemLocator  * GetLocatorPtr();
   IWbemServices * GetServicesPtr();
   HRESULT         GetLastError();
};

