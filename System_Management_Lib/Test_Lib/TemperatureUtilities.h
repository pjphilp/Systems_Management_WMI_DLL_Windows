#pragma once
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
//!\brief      This module contains the definitions related to the temperature
//!            conversion utilities
//
//!\author     pjp
//!
//!\version    0.1
//!
//!\date       09/7/17
//!
//****************************************************************************

#ifndef __TEMP_UTILS
#define __TEMP_UTILS

#define KELVIN_TO_CELSIUS_CONVERSION_FACTOR         273.15
#define KELVIN_TO_FARENHEIT_CONVERSION_FACTOR       459.67
#define CELSIUS_TO_FARENHEIT_CONVERSION_FACTOR      ( double )( 9.0 / 5.0 )

double KelvinToCelsius( double KelvinTemperature );
double KelvinToFahrenheit( double KelvinTemperature );
double CelsiusToKelvin( double CelciusTemperature );
double CelsiusToFahrenheit( double CelciusTemperature );
double FahrenheitToCelsius( double FahrenheitTemperature );

#endif
