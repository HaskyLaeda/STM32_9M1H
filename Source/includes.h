/*******************************************************************************
 **
 **    Master include file
 **     
 **    In this file should be placed headers of different including source modules and files.
 **    File "include.h" is a single point of inclusion headers and connecting modules. 
 **
 **
 ******************************************************************************/

#ifndef __INCLUDES_H
#define __INCLUDES_H
//==============================================================================   
   
  //-----------------------------------------------------------
  //  IDE depended standart headers
  //-----------------------------------------------------------

#include "stm32f10x.h"

//#include <stdio.h>
#include <string.h>
//#include <ctype.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <limits.h>
//#include <math.h>
//#include <intrinsics.h>
//#include <iolpc2148.h>


  //-----------------------------------------------------------
  //    User aplication including headers
  //-----------------------------------------------------------
   
#include "interrupts.h"
#include "DataTypes.h"
#include "main.h"
#include "UserConfig.h"
#include "9M1H.h"



  //-----------------------------------------------------------
  //  User module including headers
  //-----------------------------------------------------------
   
#include "STM32F10xXX_USART.h"
//#include "STM32F10xXX_SPI.h"
//#include "lcd.h"
   
//#include "ApplicationConfig.h"  
//#include "OperatingFunctions.h"
//#include "ff.h"
//#include "GlobalError.h"

   
//==============================================================================

#endif  // __INCLUDES_H

//=============================================  EOF  ==================================================================