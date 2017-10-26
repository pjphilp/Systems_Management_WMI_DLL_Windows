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
//****************************************************************************
//
//!\brief      This module contains the implementation of the temperature
//!            conversion utilities
//
//!\author     pjp
//!
//!\version    0.1
//!
//!\date       09/7/17
//!
//****************************************************************************

#include "stdafx.h"
#include <x86_64_port.h>

#include <TemperatureUtilities.h>

///////////////////////////////////////////////////////////////////////////////
//
// Function:  KelvinToCelsius
//
//! \brief        Convert Kelvin to Celsius
//
//! @param[in]    KelvinTemperature   a double value of degrees Kelvin
//
//! \return       double    Temperature in Celsius
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
double KelvinToCelsius( double KelvinTemperature )
{
   return ( KelvinTemperature - KELVIN_TO_CELSIUS_CONVERSION_FACTOR );
}

///////////////////////////////////////////////////////////////////////////////
//
// Function:  KelvinToFahrenheit
//
//! \brief        Convert Kelvin to Fahrenheit
//
//! @param[in]    KelvinTemperature   a double value of degrees Kelvin
//
//! \return       double    Temperature in Fahrenheit
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
double KelvinToFahrenheit( double KelvinTemperature )
{
   return ( ( KelvinTemperature * CELSIUS_TO_FARENHEIT_CONVERSION_FACTOR ) - KELVIN_TO_FARENHEIT_CONVERSION_FACTOR );
}

///////////////////////////////////////////////////////////////////////////////
//
// Function:  CelsiusToKelvin
//
//! \brief        Convert Celsius to Kelvin
//
//! @param[in]    CelsiusTemperature   a double value of degrees Celsius
//
//! \return       double    Temperature in Kelvin
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
double CelsiusToKelvin( double CelsiusTemperature )
{
   return ( CelsiusTemperature + KELVIN_TO_CELSIUS_CONVERSION_FACTOR );
}


///////////////////////////////////////////////////////////////////////////////
//
// Function:  CelsiusToFahrenheit
//
//! \brief        Convert Celsius to Fahrenheit
//
//! @param[in]    CelsiusTemperature   a double value of degrees Celsius
//
//! \return       double    Temperature in Fahrenheit
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
double CelsiusToFahrenheit( double CelsiusTemperature )
{
   return ( ( CelsiusTemperature * CELSIUS_TO_FARENHEIT_CONVERSION_FACTOR ) + 32.0 );
}

///////////////////////////////////////////////////////////////////////////////
//
// Function: FahrenheitToCelsius
//
//! \brief        Convert Fahrenheit to Celsius
//
//! @param[in]    FahrenheitTemperature   a double value of degrees Fahrenheit
//
//! \return       double    Temperature in Celsius
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
double FahrenheitToCelsius( double FahrenheitTemperature )
{
   return ( ( FahrenheitTemperature - 32.0 ) / CELSIUS_TO_FARENHEIT_CONVERSION_FACTOR  );
}






