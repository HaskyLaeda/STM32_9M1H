#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H
//==============================================================================
#include "includes.h"


#define SET_BIT(REG, BIT)      ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)    ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)     ((REG) & (BIT))
#define CLEAR_REG(REG)         ((REG) = (0x0))
#define WRITE_REG(REG, VAL)    ((REG) = (VAL))
#define READ_REG(REG)          ((REG))
//#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

//#define  GPIO_CRH_MODE8(ARG)   ((ARG << 0))
//#define  GPIO_CRH_MODE9(ARG)   ((ARG << 4))
//#define  GPIO_CRH_MODE10(ARG)  ((ARG << 8))
//#define  GPIO_CRH_MODE11(ARG)  ((ARG << 12))
//#define  GPIO_CRH_MODE12(ARG)  ((ARG << 16))
//#define  GPIO_CRH_MODE13(ARG)  ((ARG << 20))
//#define  GPIO_CRH_MODE14(ARG)  ((ARG << 24))
//#define  GPIO_CRH_MODE15(ARG)  ((ARG << 28))



  #ifdef __cplusplus
    extern "C"
    {
  #endif
  //============================================================================       
    
    void InitSysTick(void);
    void InitPinout(void);
    void InitUSART1(void);
        
  //============================================================================   
  #ifdef __cplusplus
    }
  #endif
//==============================================================================
#endif //__USER_CONFIG_H
//=============================================  EOF  ==================================================================