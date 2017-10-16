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


typedef unsigned char          BOOL;        // ����������
typedef unsigned char *       pBOOL;        // ��������� �� ����������
typedef unsigned char          INT8U;       // ����� ����������� 8 ���   = 0 ... 255
typedef unsigned char *       pINT8U;       // ��������� �� ����� ����������� 8 ���
typedef signed   char          INT8S;       // ����� �������� 8 ���      = -128 ... 127
typedef signed   char *       pINT8S;       // ��������� �� ����� �������� 8 ���
typedef unsigned short         INT16U;      // ����� ����������� 16 ���  = 0 ... 65535
typedef unsigned short *      pINT16U;      // ��������� �� ����� ����������� 16 ���
typedef signed   short         INT16S;      // ����� �������� 16 ���     = -32768 ... 32767
typedef signed   short *      pINT16S;      // ��������� �� ����� �������� 16 ���
typedef unsigned long          INT32U;      // ����� ����������� 32 ���  = 0 ...4294967295
typedef unsigned long *       pINT32U;      // ��������� �� ����� ����������� 32 ���
typedef signed   long          INT32S;      // ����� �������� 32 ���     = -2147483648 ... 2147483648
typedef signed   long *       pINT32S;      // ��������� �� ����� �������� 32 ���
typedef unsigned long long     INT64U;      // ����� ����������� 64 ���  = 0 ... 2^64-1
typedef unsigned long long *  pINT64U;      // ��������� �� ����� ����������� 64 ���
typedef signed long long       INT64S;      // ����� �������� 64 ���     = -(2^63) ... 2^63-1
typedef signed long long *    pINT64S;      // ��������� �� ����� �������� 64 ���
typedef float                  FLOAT32;     // ������������ � ��������� ������ 32 ���
typedef float *               pFLOAT32;     // ��������� �� ������������ � ��������� ������ 32 ���
typedef double                 FLOAT64;     // ������������ � ��������� ������ (������� ��������) 64 ���
typedef double *              pFLOAT64;     // ��������� �� ������������ � ��������� ������ (������� ��������) 64 ���
typedef long double            FLOAT80;     // ������������ � ��������� ������ 80 ���
typedef long double *         pFLOAT80;     // ��������� �� ������������ � ��������� ������ 80 ���

typedef unsigned char          Boolean;     // ����������
typedef unsigned char *       pBoolean;     // ��������� �� ����������
typedef unsigned char          Int8U;       // ����� ����������� 8 ���
typedef unsigned char *       pInt8U;       // ��������� �� ����� ����������� 8 ���
typedef signed   char          Int8S;       // ����� �������� 8 ���
typedef signed   char *       pInt8S;       // ��������� �� ����� �������� 8 ���
typedef unsigned short         Int16U;      // ����� ����������� 16 ���
typedef unsigned short *      pInt16U;      // ��������� �� ����� ����������� 16 ���
typedef signed   short         Int16S;      // ����� �������� 16 ���
typedef signed   short *      pInt16S;      // ��������� �� ����� �������� 16 ���
typedef unsigned long          Int32U;      // ����� ����������� 32 ���
typedef unsigned long *       pInt32U;      // ��������� �� ����� ����������� 32 ���
typedef signed   long          Int32S;      // ����� �������� 32 ���
typedef signed   long *       pInt32S;      // ��������� �� ����� �������� 32 ���
typedef unsigned long long     Int64U;      // ����� ����������� 64 ���
typedef unsigned long long *  pInt64U;      // ��������� �� ����� ����������� 64 ���
typedef signed long long       Int64S;      // ����� �������� 64 ���
typedef signed long long *    pInt64S;      // ��������� �� ����� ��������� 64 ���
typedef float                  Float32;     // ������������ � ��������� ������ 32 ���
typedef float *               pFloat32;     // ��������� �� ������������ � ��������� ������ 32 ���
typedef double                 Float64;     // ������������ � ��������� ������ (������� ��������) 64 ���
typedef double *              pFloat64;     // ��������� �� ������������ � ��������� ������ 64 ���
typedef long double            Float80;     // ������������ � ��������� ������ 80 ���
typedef long double *         pFloat80;     // ��������� �� ������������ � ��������� ������ 80 ���

typedef unsigned char          Bool;        // ����������
typedef unsigned char *       pBool;        // ��������� �� ����������

typedef signed   char          Int8;       // ����� �������� 8 ���
typedef signed   char *       pInt8;       // ��������� �� ����� �������� 8 ���
typedef signed   short         Int16;      // ����� �������� 16 ���
typedef signed   short *      pInt16;      // ��������� �� ����� �������� 16 ���
typedef signed   long          Int32;      // ����� �������� 32 ���
typedef signed   long *       pInt32;      // ��������� �� ����� �������� 32 ���
typedef signed long long       Int64;      // ����� �������� 64 ���
typedef signed long long *    pInt64;      // ��������� �� ����� ��������� 64 ���

typedef signed   char          INT8;       // ����� �������� 8 ���      = -128 ... 127
typedef signed   char *       pINT8;       // ��������� �� ����� �������� 8 ���
typedef signed   short         INT16;      // ����� �������� 16 ���     = -32768 ... 32767
typedef signed   short *      pINT16;      // ��������� �� ����� �������� 16 ���
typedef signed   long          INT32;      // ����� �������� 32 ���     = -2147483648 ... 2147483648
typedef signed   long *       pINT32;      // ��������� �� ����� �������� 32 ���
typedef signed long long       INT64;      // ����� �������� 64 ���     = -(2^63) ... 2^63-1
typedef signed long long *    pINT64;      // ��������� �� ����� �������� 64 ���

//======================================================================================================================
//                                               Interface
//======================================================================================================================



//======================================================================================================================

#endif // __DATA_TYPES_H //

//=============================================  EOF  ==================================================================
