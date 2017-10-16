//======================================================================================================================
//  28.06.2015         ver.  0.0.1            
//  Name: DataTypes.h
//  Description: Define certain data lenght
//  Author: Shiliakin Alexandr aka Hasky Laeda
//======================================================================================================================

#ifndef __DATA_TYPES_H
#define __DATA_TYPES_H

#ifndef __cplusplus
  #define bool Int8U
#endif

//======================================================================================================================
//                                               Macros
//======================================================================================================================

  #define no_err  (0)

//======================================================================================================================
//                                               Types
//======================================================================================================================


typedef unsigned char          BOOL;        // Логический
typedef unsigned char *       pBOOL;        // Указатель на Логический
typedef unsigned char          INT8U;       // Целый беззнаковый 8 бит   = 0 ... 255
typedef unsigned char *       pINT8U;       // Указатель на Целый беззнаковый 8 бит
typedef signed   char          INT8S;       // Целый знаковый 8 бит      = -128 ... 127
typedef signed   char *       pINT8S;       // Указатель на Целый знаковый 8 бит
typedef unsigned short         INT16U;      // Целый беззнаковый 16 бит  = 0 ... 65535
typedef unsigned short *      pINT16U;      // Указатель на Целый беззнаковый 16 бит
typedef signed   short         INT16S;      // Целый знаковый 16 бит     = -32768 ... 32767
typedef signed   short *      pINT16S;      // Указатель на Целый знаковый 16 бит
typedef unsigned long          INT32U;      // Целый беззнаковый 32 бит  = 0 ...4294967295
typedef unsigned long *       pINT32U;      // Указатель на Целый беззнаковый 32 бит
typedef signed   long          INT32S;      // Целый знаковый 32 бит     = -2147483648 ... 2147483648
typedef signed   long *       pINT32S;      // Указатель на Целый знаковый 32 бит
typedef unsigned long long     INT64U;      // Целый беззнаковый 64 бит  = 0 ... 2^64-1
typedef unsigned long long *  pINT64U;      // Указатель на Целый беззнаковый 64 бит
typedef signed long long       INT64S;      // Целый знаковый 64 бит     = -(2^63) ... 2^63-1
typedef signed long long *    pINT64S;      // Указатель на Целый знаковый 64 бит
typedef float                  FLOAT32;     // Вещественный с плавающей точкой 32 бит
typedef float *               pFLOAT32;     // Указатель на вещественный с плавающей точкой 32 бит
typedef double                 FLOAT64;     // Вещественный с плавающей точкой (двойная точность) 64 бит
typedef double *              pFLOAT64;     // Указатель на вещественный с плавающей точкой (двойная точность) 64 бит
typedef long double            FLOAT80;     // Вещественный с плавающей точкой 80 бит
typedef long double *         pFLOAT80;     // Указатель на вещественный с плавающей точкой 80 бит

typedef unsigned char          Boolean;     // Логический
typedef unsigned char *       pBoolean;     // Указатель на Логический
typedef unsigned char          Int8U;       // Целый беззнаковый 8 бит
typedef unsigned char *       pInt8U;       // Указатель на Целый беззнаковый 8 бит
typedef signed   char          Int8S;       // Целый знаковый 8 бит
typedef signed   char *       pInt8S;       // Указатель на Целый знаковый 8 бит
typedef unsigned short         Int16U;      // Целый беззнаковый 16 бит
typedef unsigned short *      pInt16U;      // Указатель на Целый беззнаковый 16 бит
typedef signed   short         Int16S;      // Целый знаковый 16 бит
typedef signed   short *      pInt16S;      // Указатель на Целый знаковый 16 бит
typedef unsigned long          Int32U;      // Целый беззнаковый 32 бит
typedef unsigned long *       pInt32U;      // Указатель на Целый беззнаковый 32 бит
typedef signed   long          Int32S;      // Целый знаковый 32 бит
typedef signed   long *       pInt32S;      // Указатель на Целый знаковый 32 бит
typedef unsigned long long     Int64U;      // Целый беззнаковый 64 бит
typedef unsigned long long *  pInt64U;      // Указатель на Целый беззнаковый 64 бит
typedef signed long long       Int64S;      // Целый знаковый 64 бит
typedef signed long long *    pInt64S;      // Указатель на Целый ззнаковый 64 бит
typedef float                  Float32;     // Вещественный с плавающей точкой 32 бит
typedef float *               pFloat32;     // Указатель на вещественный с плавающей точкой 32 бит
typedef double                 Float64;     // Вещественный с плавающей точкой (двойная точность) 64 бит
typedef double *              pFloat64;     // Указатель на вещественный с плавающей точкой 64 бит
typedef long double            Float80;     // Вещественный с плавающей точкой 80 бит
typedef long double *         pFloat80;     // Указатель на вещественный с плавающей точкой 80 бит

typedef unsigned char          Bool;        // Логический
typedef unsigned char *       pBool;        // Указатель на Логический

typedef signed   char          Int8;       // Целый знаковый 8 бит
typedef signed   char *       pInt8;       // Указатель на Целый знаковый 8 бит
typedef signed   short         Int16;      // Целый знаковый 16 бит
typedef signed   short *      pInt16;      // Указатель на Целый знаковый 16 бит
typedef signed   long          Int32;      // Целый знаковый 32 бит
typedef signed   long *       pInt32;      // Указатель на Целый знаковый 32 бит
typedef signed long long       Int64;      // Целый знаковый 64 бит
typedef signed long long *    pInt64;      // Указатель на Целый ззнаковый 64 бит

typedef signed   char          INT8;       // Целый знаковый 8 бит      = -128 ... 127
typedef signed   char *       pINT8;       // Указатель на Целый знаковый 8 бит
typedef signed   short         INT16;      // Целый знаковый 16 бит     = -32768 ... 32767
typedef signed   short *      pINT16;      // Указатель на Целый знаковый 16 бит
typedef signed   long          INT32;      // Целый знаковый 32 бит     = -2147483648 ... 2147483648
typedef signed   long *       pINT32;      // Указатель на Целый знаковый 32 бит
typedef signed long long       INT64;      // Целый знаковый 64 бит     = -(2^63) ... 2^63-1
typedef signed long long *    pINT64;      // Указатель на Целый знаковый 64 бит

//======================================================================================================================
//                                               Interface
//======================================================================================================================



//======================================================================================================================

#endif // __DATA_TYPES_H //

//=============================================  EOF  ==================================================================
