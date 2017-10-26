///****************************************************************************
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
//    Name       : WinSys_Errors.h
//
//    Project    : Definitions of WinSystems errors
//
//    Author     : pjp
//
//    #defines for WinSystems defined errors (follows Microsoft error code
//    syntax found in winerror.h
//
///****************************************************************************
//
//      Date      Revision    Description
//    --------    --------    ---------------------------------------------
//    08/14/17      0.1       PJP - Original
//
///****************************************************************************

#pragma once

///////////////////////////////////////////////////////////////////////////////

typedef uint32_t     WINSYS_ERROR;

//
// top 2 bits define the error type (error, warning, info, success)
//
#define WINDOWS_SUCCESS                         0x0
#define WINDOWS_INFO                            0x1
#define WINDOWS_WARN                            0x2
#define WINDOWS_ERROR                           0x3

//
// bit 29 will be set as these are not Windows errors...
//
#define WINDOWS_CUSTOMER_CODE                   0x1

#define FACILITY_WINSYSTEMS                            ( FACILITY_PIX + 1 )
#define WINSYS_FACILITY_MAC_ADDRESS_CLASS              ( FACILITY_WINSYSTEMS + 1 )
#define WINSYS_FACILITY_IP_ADDRESS_CLASS               ( FACILITY_WINSYSTEMS + 2 )
#define WINSYS_FACILITY_BIOS_CLASS                     ( FACILITY_WINSYSTEMS + 3 )
#define WINSYS_FACILITY_BUS_CLASS                      ( FACILITY_WINSYSTEMS + 4 )
#define WINSYS_FACILITY_DISK_LOGICAL_CLASS             ( FACILITY_WINSYSTEMS + 5 )
#define WINSYS_FACILITY_DISK_PHYSICAL_CLASS            ( FACILITY_WINSYSTEMS + 6 )
#define WINSYS_FACILITY_DISK_PARTITION_CLASS           ( FACILITY_WINSYSTEMS + 7 )
#define WINSYS_FACILITY_PROCESSOR_CLASS                ( FACILITY_WINSYSTEMS + 8 )
#define WINSYS_FACILITY_VIDEO_CONTROLLER_CLASS         ( FACILITY_WINSYSTEMS + 9 )
#define WINSYS_FACILITY_SERIAL_PORT_CLASS              ( FACILITY_WINSYSTEMS + 10 )
#define WINSYS_FACILITY_SERIAL_PORT_CONFIG_CLASS       ( FACILITY_WINSYSTEMS + 11 )
#define WINSYS_FACILITY_MEMORY_LOGICAL_CLASS           ( FACILITY_WINSYSTEMS + 12 )
#define WINSYS_FACILITY_MEMORY_PHYSICAL_CLASS          ( FACILITY_WINSYSTEMS + 13 )
#define WINSYS_FACILITY_BASE_BOARD_CLASS               ( FACILITY_WINSYSTEMS + 14 )
#define WINSYS_FACILITY_TEMPERATURE_SENSOR_CLASS       ( FACILITY_WINSYSTEMS + 15 )
#define WINSYS_FACILITY_ACTIVE_COOLING_CLASS           ( FACILITY_WINSYSTEMS + 16 )
#define WINSYS_FACILITY_COMMON_PROPERTIES              ( FACILITY_WINSYSTEMS + 17 )
#define WINSYS_FACILITY_WBEM_SERVER_PROPERTIES         ( FACILITY_WINSYSTEMS + 18 )
#define WINSYS_FACILITY_MFC_INITIALIZATION             ( FACILITY_WINSYSTEMS + 19 )


//
// a macro to build the error code from type, customer, facility and error
//
#define WINS_ERROR( TYPE, WINDOWS_CUSTOMER_CODE, FACILITY, ERROR_CODE )     ( ( TYPE << 30 ) | ( WINDOWS_CUSTOMER_CODE << 29 ) | ( FACILITY << 16 ) | ERROR_CODE )

//
// define the errors
//
#define STATUS_SUCCESS                          S_OK
#define STATUS_BAD_PARAMETER                    1
#define STATUS_NULL_POINTER                     2
#define STATUS_BAD_POINTER                      3
#define STATUS_BAD_DEV_HANDLE                   4
#define STATUS_INDEX_OUT_OF_RANGE               5
#define STATUS_ENUMERATION_OUT_OF_RANGE         6
#define STATUS_OBJECT_HAS_NO_WMI_ENUMERATION    7
#define STATUS_MODULE_HANDLE_ERROR              8
#define STATUS_AFX_INIT_ERROR                   9


