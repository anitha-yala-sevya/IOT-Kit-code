/**
 ******************************************************************************
 * @file    x_nucleo_iks01a2_accelero.h
 * @author  MEMS Application Team, MP
 * @version V3.0.0
 * @date    12-August-2016
 * @brief   This file contains definitions for the x_nucleo_iks01a2_accelero.c
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __X_NUCLEO_IKS01A2_ACCELERO_H
#define __X_NUCLEO_IKS01A2_ACCELERO_H

#ifdef __cplusplus
extern "C" {
#endif



/* Includes ------------------------------------------------------------------*/
#include "LSM6DSL_ACC_GYRO_driver_HL.h"
#include "LSM303AGR_ACC_driver_HL.h"
#include "../Components/iis2dh/IIS2DH_Driver_HL.h"
#include "x_nucleo_iks01a2.h"



/** @addtogroup BSP BSP
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A2 X_NUCLEO_IKS01A2
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A2_ACCELERO Accelero
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A2_ACCELERO_Public_Types Public types
  * @{
  */

typedef enum
{
  ACCELERO_SENSORS_AUTO = -1,    /* Always first element and equal to -1 */
  LSM6DSL_X_0,                   /* On board. */
  LSM303AGR_X_0,                 /* On board. */
  IIS2DH_X_0                     /* DIL24 adapter. */  
} ACCELERO_ID_t;

/**
 * @}
 */

/** @addtogroup X_NUCLEO_IKS01A2_ACCELERO_Public_Defines Public defines
  * @{
  */

#define ACCELERO_SENSORS_MAX_NUM 3

/**
 * @}
 */

/** @addtogroup X_NUCLEO_IKS01A2_ACCELERO_Public_Function_Prototypes Public function prototypes
 * @{
 */

/* Sensor Configuration Functions */
DrvStatusTypeDef BSP_ACCELERO_Init( ACCELERO_ID_t id, void **handle );
DrvStatusTypeDef BSP_ACCELERO_DeInit( void **handle );
DrvStatusTypeDef BSP_ACCELERO_Sensor_Enable( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Sensor_Disable( void *handle );
DrvStatusTypeDef BSP_ACCELERO_IsInitialized( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_IsEnabled( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_IsCombo( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_Get_Instance( void *handle, uint8_t *instance );
DrvStatusTypeDef BSP_ACCELERO_Get_WhoAmI( void *handle, uint8_t *who_am_i );
DrvStatusTypeDef BSP_ACCELERO_Check_WhoAmI( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_Axes( void *handle, SensorAxes_t *acceleration );
DrvStatusTypeDef BSP_ACCELERO_Get_AxesRaw( void *handle, SensorAxesRaw_t *value );
DrvStatusTypeDef BSP_ACCELERO_Get_Sensitivity( void *handle, float *sensitivity );
DrvStatusTypeDef BSP_ACCELERO_Get_ODR( void *handle, float *odr );
DrvStatusTypeDef BSP_ACCELERO_Set_ODR( void *handle, SensorOdr_t odr );
DrvStatusTypeDef BSP_ACCELERO_Set_ODR_Value( void *handle, float odr );
DrvStatusTypeDef BSP_ACCELERO_Get_FS( void *handle, float *fullScale );
DrvStatusTypeDef BSP_ACCELERO_Set_FS( void *handle, SensorFs_t fullScale );
DrvStatusTypeDef BSP_ACCELERO_Set_FS_Value( void *handle, float fullScale );
DrvStatusTypeDef BSP_ACCELERO_Get_Axes_Status( void *handle, uint8_t *xyz_enabled );
DrvStatusTypeDef BSP_ACCELERO_Set_Axes_Status( void *handle, uint8_t *enable_xyz );
DrvStatusTypeDef BSP_ACCELERO_Read_Reg( void *handle, uint8_t reg, uint8_t *data );
DrvStatusTypeDef BSP_ACCELERO_Write_Reg( void *handle, uint8_t reg, uint8_t data );
DrvStatusTypeDef BSP_ACCELERO_Get_DRDY_Status( void *handle, uint8_t *status );

DrvStatusTypeDef BSP_ACCELERO_Enable_Free_Fall_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Disable_Free_Fall_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_Free_Fall_Detection_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_Set_Free_Fall_Threshold_Ext( void *handle, uint8_t thr );

DrvStatusTypeDef BSP_ACCELERO_Enable_Pedometer_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Disable_Pedometer_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_Pedometer_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_Get_Step_Count_Ext( void *handle, uint16_t *step_count );
DrvStatusTypeDef BSP_ACCELERO_Reset_Step_Counter_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Set_Pedometer_Threshold_Ext( void *handle, uint8_t thr );

DrvStatusTypeDef BSP_ACCELERO_Enable_Tilt_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Disable_Tilt_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_Tilt_Detection_Status_Ext( void *handle, uint8_t *status );

DrvStatusTypeDef BSP_ACCELERO_Enable_Wake_Up_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Disable_Wake_Up_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_Wake_Up_Detection_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_Set_Wake_Up_Threshold_Ext( void *handle, uint8_t thr );

DrvStatusTypeDef BSP_ACCELERO_Enable_Single_Tap_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Disable_Single_Tap_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_Single_Tap_Detection_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_Enable_Double_Tap_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Disable_Double_Tap_Detection_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_Double_Tap_Detection_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_Set_Tap_Threshold_Ext( void *handle, uint8_t thr );
DrvStatusTypeDef BSP_ACCELERO_Set_Tap_Shock_Time_Ext( void *handle, uint8_t time );
DrvStatusTypeDef BSP_ACCELERO_Set_Tap_Quiet_Time_Ext( void *handle, uint8_t time );
DrvStatusTypeDef BSP_ACCELERO_Set_Tap_Duration_Time_Ext( void *handle, uint8_t time );

DrvStatusTypeDef BSP_ACCELERO_Enable_6D_Orientation_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Disable_6D_Orientation_Ext( void *handle );
DrvStatusTypeDef BSP_ACCELERO_Get_6D_Orientation_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_Get_6D_Orientation_XL_Ext( void *handle, uint8_t *xl );
DrvStatusTypeDef BSP_ACCELERO_Get_6D_Orientation_XH_Ext( void *handle, uint8_t *xh );
DrvStatusTypeDef BSP_ACCELERO_Get_6D_Orientation_YL_Ext( void *handle, uint8_t *yl );
DrvStatusTypeDef BSP_ACCELERO_Get_6D_Orientation_YH_Ext( void *handle, uint8_t *yh );
DrvStatusTypeDef BSP_ACCELERO_Get_6D_Orientation_ZL_Ext( void *handle, uint8_t *zl );
DrvStatusTypeDef BSP_ACCELERO_Get_6D_Orientation_ZH_Ext( void *handle, uint8_t *zh );

DrvStatusTypeDef BSP_ACCELERO_FIFO_Set_ODR_Value_Ext( void *handle, float odr );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Get_Full_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Get_Empty_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Get_Overrun_Status_Ext( void *handle, uint8_t *status );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Get_Pattern_Ext( void *handle, uint16_t *pattern );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Get_Data_Ext( void *handle, uint8_t *aData );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Get_Num_Of_Samples_Ext( void *handle, uint16_t *nSamples );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Set_Decimation_Ext( void *handle, uint8_t decimation );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Get_Axis_Ext( void *handle, int32_t *acceleration );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Set_Mode_Ext( void *handle, uint8_t mode );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Set_INT1_FIFO_Full_Ext( void *handle, uint8_t status );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Set_Watermark_Level_Ext( void *handle, uint16_t watermark );
DrvStatusTypeDef BSP_ACCELERO_FIFO_Set_Stop_On_Fth_Ext( void *handle, uint8_t status );

DrvStatusTypeDef BSP_ACCELERO_Set_Interrupt_Latch_Ext( void *handle, uint8_t status );
DrvStatusTypeDef BSP_ACCELERO_Set_SelfTest_Ext( void *handle, uint8_t status );

DrvStatusTypeDef BSP_ACCELERO_Get_SuperRawAxes_Ext( void *handle, int16_t *acceleration, ACTIVE_AXIS_t axis );
DrvStatusTypeDef BSP_ACCELERO_Get_OpMode_Ext( void *handle, OPER_MODE_t *opMode );
DrvStatusTypeDef BSP_ACCELERO_Set_OpMode_Ext( void *handle, OPER_MODE_t opMode );
DrvStatusTypeDef BSP_ACCELERO_Get_Active_Axis_Ext( void *handle, ACTIVE_AXIS_t *axis );
DrvStatusTypeDef BSP_ACCELERO_Set_Active_Axis_Ext( void *handle, ACTIVE_AXIS_t axis );
DrvStatusTypeDef BSP_ACCELERO_Enable_HP_Filter_Ext( DrvContextTypeDef *handle, HPF_MODE_t mode, HPF_CUTOFF_t cutoff );
DrvStatusTypeDef BSP_ACCELERO_Disable_HP_Filter_Ext( DrvContextTypeDef *handle );
DrvStatusTypeDef BSP_ACCELERO_ClearDRDY_Ext( DrvContextTypeDef *handle, ACTIVE_AXIS_t axisActive );
DrvStatusTypeDef BSP_ACCELERO_Set_INT1_DRDY_Ext( DrvContextTypeDef *handle, INT1_DRDY_CONFIG_t drdyStatus );


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __X_NUCLEO_IKS01A2_ACCELERO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
