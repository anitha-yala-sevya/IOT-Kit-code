/**
******************************************************************************
* @file    x_nucleo_cca02m1_audio_f4.c
* @author  Central Labs
* @version V1.0.0
* @date    7-May-2015
* @brief   This file provides the Audio driver for the X-NUCLEO-CCA02M1
*          expansion board
*******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2s.h"
#include "x_nucleo_cca02m1_audio_f4.h"


/** @addtogroup BSP
* @{
*/

/** @addtogroup X-NUCLEO-CCA02M1
* @{
*/

/** @addtogroup X-NUCLEO-CCA02M1_AUDIO_F4
* @brief This file provides set of firmware functions to manage MEMS microphones
*        initialization on STM32F4xx-Nucleo Kit from STMicroelectronics.
* @{
*/

/** @defgroup X-NUCLEO-CCA02M1_AUDIO_F4_Private_Types
* @{
*/

/**
* @}
*/

/** @defgroup X-NUCLEO-CCA02M1_AUDIO_F4_Private_Defines 
* @{
*/

/**
* @}
*/

/** @defgroup X-NUCLEO-CCA02M1_AUDIO_F4_Private_Macros 
* @{
*/

/**
* @}
*/

/** @defgroup X-NUCLEO-CCA02M1_AUDIO_F4_Private_Variables
* @{
*/
#define CHANNEL_DEMUX_MASK                    	0x55

I2S_HandleTypeDef                 hAudioInI2s;
SPI_HandleTypeDef                 hAudioInSPI;

static TIM_HandleTypeDef          TimDividerHandle;
static TIM_SlaveConfigTypeDef     sSlaveConfig;
static TIM_IC_InitTypeDef         sICConfig;
static TIM_OC_InitTypeDef         sOCConfig;

static X_NUCLEO_CCA02M1_HandlerTypeDef X_NUCLEO_CCA02M1_Handler;

static uint16_t I2S_InternalBuffer[PDM_INTERNAL_BUFFER_SIZE];
static uint16_t SPI_InternalBuffer[PDM_INTERNAL_BUFFER_SIZE];

static uint16_t AudioInVolume = 64;
static PDMFilter_InitStruct Filter[4];
uint8_t Channel_Demux[128] = {
  0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
  0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
  0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
  0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
  0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
  0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
  0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
  0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
  0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
  0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
  0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f,
  0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f,
  0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
  0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
  0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f,
  0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f
};


/**
* @}
*/

/** @defgroup X-NUCLEO-CCA02M1_AUDIO_F4_Private_Function_Prototypes 
* @{
*/

static uint8_t AUDIO_IN_Timer_Init(void);
static uint8_t AUDIO_IN_Timer_Start(void);
static void AUDIO_IN_I2S_MspInit(void);
static void AUDIO_IN_SPI_MspInit(void);
static void PDMDecoder_Init(uint32_t AudioFreq, uint32_t ChnlNbrIn, uint32_t ChnlNbrOut);
/**
* @}
*/

/** @defgroup X-NUCLEO-CCA02M1_AUDIO_F4_Exported_Functions 
* @{
*/

/**
* @brief  Initializes audio acquisition recording.
* @param  AudioFreq: Audio frequency to be configured for the peripherals.
* 		  Possible values are 8000, 16000, 32000 or 48000 Hz
* @param  BitRes: Not used.
* @param  ChnlNbr: Number of channels to be recorded.
* @retval AUDIO_OK in case of success, AUDIO_ERROR otherwise 
*/
uint8_t BSP_AUDIO_IN_Init(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr){
  
  /*Set Structure for internal state*/
  X_NUCLEO_CCA02M1_Handler.MicChannels=ChnlNbr;
  X_NUCLEO_CCA02M1_Handler.Sampling_Freq=AudioFreq;
  
  if(X_NUCLEO_CCA02M1_Handler.MicChannels!=1)
  {
	  /*Timer Init*/
	  if (AUDIO_IN_Timer_Init() != AUDIO_OK)
	  {
		  return AUDIO_ERROR;
	  }

	  if(AUDIO_IN_Timer_Start() != AUDIO_OK)
	  {
		  return AUDIO_ERROR;
	  }
  }
  
  /*I2S PLL Configuration*/
  RCC_PeriphCLKInitTypeDef rccclkinit;
  HAL_RCCEx_GetPeriphCLKConfig(&rccclkinit);  
  
  switch(X_NUCLEO_CCA02M1_Handler.Sampling_Freq=AudioFreq){   
  case AUDIOFREQ_8K:
    {
      X_NUCLEO_CCA02M1_Handler.DecimationFactor=128;
      X_NUCLEO_CCA02M1_Handler.PdmBufferSize=256; 
#if defined(STM32F411xE) || defined (STM32F446xx)
      rccclkinit.PLLI2S.PLLI2SM = 8;
#endif
      rccclkinit.PLLI2S.PLLI2SN = 256;
      rccclkinit.PLLI2S.PLLI2SR = 5;      
      break;
    }
  case AUDIOFREQ_16K:
    {
      X_NUCLEO_CCA02M1_Handler.DecimationFactor=64;
      X_NUCLEO_CCA02M1_Handler.PdmBufferSize=256;      
#if defined(STM32F411xE) || defined (STM32F446xx)
      rccclkinit.PLLI2S.PLLI2SM = 8;
#endif
      rccclkinit.PLLI2S.PLLI2SN = 256;
      rccclkinit.PLLI2S.PLLI2SR = 5;      
      break;
    }    
  case AUDIOFREQ_32K:
    {
      X_NUCLEO_CCA02M1_Handler.DecimationFactor=64;
      X_NUCLEO_CCA02M1_Handler.PdmBufferSize=512;      
#if defined(STM32F411xE) || defined (STM32F446xx)
      rccclkinit.PLLI2S.PLLI2SM = 8;
#endif
      rccclkinit.PLLI2S.PLLI2SN = 246;
      rccclkinit.PLLI2S.PLLI2SR = 6;      
      break;
    }    
  case AUDIOFREQ_48K:
    {
      X_NUCLEO_CCA02M1_Handler.DecimationFactor=64;
      X_NUCLEO_CCA02M1_Handler.PdmBufferSize=768;      
#if defined(STM32F411xE) || defined (STM32F446xx)
      rccclkinit.PLLI2S.PLLI2SM = 8;
#endif
      rccclkinit.PLLI2S.PLLI2SN = 424;
      rccclkinit.PLLI2S.PLLI2SR = 3;      
      break;
    }
  default:
    {
      return AUDIO_ERROR;
    }
  }
  
#if defined(STM32F446xx)
  rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S_APB2;
#else
  rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
#endif
  
  if(HAL_RCCEx_PeriphCLKConfig(&rccclkinit) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  
  /* I2S Peripheral configuration */
  hAudioInI2s.Instance          = AUDIO_IN_I2S_INSTANCE;  
  __HAL_I2S_DISABLE(&hAudioInI2s);
  
  if(X_NUCLEO_CCA02M1_Handler.MicChannels==1)
  {
    hAudioInI2s.Init.DataFormat   = I2S_DATAFORMAT_16B;
  }
  else
  {
    hAudioInI2s.Init.DataFormat   = I2S_DATAFORMAT_32B;    
  }
  
  if(AudioFreq == AUDIOFREQ_8K)
  {
    hAudioInI2s.Init.AudioFreq    = 4 * AudioFreq;
  }else
  {
    hAudioInI2s.Init.AudioFreq    = 2 * AudioFreq;
  }  
  hAudioInI2s.Init.ClockSource  = I2S_CLOCK_PLL;
  hAudioInI2s.Init.CPOL         = I2S_CPOL_HIGH;
  hAudioInI2s.Init.MCLKOutput   = I2S_MCLKOUTPUT_DISABLE;
  hAudioInI2s.Init.Mode         = I2S_MODE_MASTER_RX;
  hAudioInI2s.Init.Standard     = I2S_STANDARD_MSB;
  hAudioInI2s.Init.FullDuplexMode   = I2S_FULLDUPLEXMODE_DISABLE;
  
  if(HAL_I2S_GetState(&hAudioInI2s) == HAL_I2S_STATE_RESET)
  {
    AUDIO_IN_I2S_MspInit();
  }
  
  if(HAL_I2S_Init(&hAudioInI2s) != HAL_OK)
  {
    return AUDIO_ERROR;
  }  
  /*End I2S Init*/
  
  /*SPI Init*/
  if(X_NUCLEO_CCA02M1_Handler.MicChannels>2)
  {
    /* Set the SPI parameters */
    hAudioInSPI.Instance               = AUDIO_IN_SPI_INSTANCE;
    hAudioInSPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hAudioInSPI.Init.Direction         = SPI_DIRECTION_2LINES_RXONLY;
    hAudioInSPI.Init.CLKPhase          = SPI_PHASE_2EDGE;
    hAudioInSPI.Init.CLKPolarity       = SPI_POLARITY_HIGH;
    hAudioInSPI.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
    hAudioInSPI.Init.CRCPolynomial     = 7;
    hAudioInSPI.Init.DataSize          = SPI_DATASIZE_16BIT;
    hAudioInSPI.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    hAudioInSPI.Init.NSS               = SPI_NSS_SOFT;
    hAudioInSPI.Init.TIMode            = SPI_TIMODE_DISABLED;
    hAudioInSPI.Init.Mode              = SPI_MODE_SLAVE;
    
    /* Initialize the I2S peripheral with the structure above */
    if(HAL_SPI_GetState(&hAudioInSPI) == HAL_SPI_STATE_RESET)
    {
      AUDIO_IN_SPI_MspInit();
    }    
    if(HAL_SPI_Init(&hAudioInSPI) != HAL_OK)
    {
      return AUDIO_ERROR;
    }   
  }  
  /*End SPI init*/
  
  /*PDM Filter Init*/
  PDMDecoder_Init(X_NUCLEO_CCA02M1_Handler.Sampling_Freq,X_NUCLEO_CCA02M1_Handler.MicChannels, X_NUCLEO_CCA02M1_Handler.MicChannels);
  /*End PDM Filter Init*/
  
  return AUDIO_OK;
}

/**
* @brief  Starts audio recording.
* @param  * pbuf: Buffer that will contain 1 ms of PDM for each microphone.
				  Its dimension must be equal to (in uint16_t words): 
				  ((PCM sampling frequency)/1000 * DecimationFactor * Channels)/16
				  DecimationFactor is equal to 128 for 8000 KHZ sampling frequency, 64 in all the other cases
* @param  size: Not used in this driver.
* @retval AUDIO_OK in case of success, AUDIO_ERROR otherwise
*/
uint8_t BSP_AUDIO_IN_Record(uint16_t * pbuf, uint32_t size)
{  
  
  X_NUCLEO_CCA02M1_Handler.PDM_Data = pbuf;  
  if(X_NUCLEO_CCA02M1_Handler.MicChannels > 2)
  {
    if(HAL_SPI_Receive_DMA(&hAudioInSPI, (uint8_t *)SPI_InternalBuffer, X_NUCLEO_CCA02M1_Handler.PdmBufferSize) != HAL_OK)
    {
      return AUDIO_ERROR;
    }
  }

  if(HAL_I2S_Receive_DMA(&hAudioInI2s, I2S_InternalBuffer, X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2) != HAL_OK)
  {
    return AUDIO_ERROR;
  }  
  
  /* Return 0 if all operations are OK */
  return AUDIO_OK;
}

/**
* @brief  Stops audio recording.
* @param  None
* @retval AUDIO_OK in case of success, AUDIO_ERROR otherwise
*/
uint8_t BSP_AUDIO_IN_Stop(void)
{
   if(X_NUCLEO_CCA02M1_Handler.MicChannels > 2)
  {
  HAL_SPI_DMAStop(&hAudioInSPI);
  }

  if(HAL_I2S_DMAStop(&hAudioInI2s) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  /* Return 0 if all operations are OK */
  return AUDIO_OK;
}

/**
* @brief  Controls the audio in volume level.
* @param  Volume: Volume level to be set for the PDM to PCM conversion. 
		  Values must be in the range from 0 to 64
* @retval AUDIO_OK in case of success, AUDIO_ERROR otherwise 
*/
uint8_t BSP_AUDIO_IN_SetVolume(uint8_t Volume)
{
  /* Set the Global variable AudioInVolume */
  AudioInVolume = Volume;  
  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
* @brief  Converts audio format from PDM to PCM.
* @param  PDMBuf: Pointer to PDM buffer data
* @param  PCMBuf: Pointer to PCM buffer data
* @retval AUDIO_OK in case of success, AUDIO_ERROR otherwise 
*/
uint8_t BSP_AUDIO_IN_PDMToPCM(uint16_t *PDMBuf, uint16_t *PCMBuf)
{  
  uint32_t index = 0;  
  if(X_NUCLEO_CCA02M1_Handler.DecimationFactor == 128)
  {
    for(index = 0; index < X_NUCLEO_CCA02M1_Handler.MicChannels; index++)
    {
      PDM_Filter_128_LSB(&((uint8_t*)(PDMBuf))[index], (uint16_t*)&(PCMBuf[index]), AudioInVolume , (PDMFilter_InitStruct *)&Filter[index]);
    }
  }
  
  if(X_NUCLEO_CCA02M1_Handler.DecimationFactor == 64)
  {
    for(index = 0; index < X_NUCLEO_CCA02M1_Handler.MicChannels; index++)
    {
      PDM_Filter_64_LSB(&((uint8_t*)(PDMBuf))[index], (uint16_t*)&(PCMBuf[index]), AudioInVolume , (PDMFilter_InitStruct *)&Filter[index]);
    }
  }  
  
  return AUDIO_OK;
}


/**
* @brief  Pauses the audio file stream.
* @param  None
* @retval AUDIO_OK in case of success, AUDIO_ERROR otherwise 
*/
uint8_t BSP_AUDIO_IN_Pause(void)
{    
  /* Call the Media layer pause function */
  HAL_I2S_DMAPause(&hAudioInI2s);
  
  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
* @brief  Resumes the audio file stream.
* @param  None    
* @retval AUDIO_OK in case of success, AUDIO_ERROR otherwise 
*/
uint8_t BSP_AUDIO_IN_Resume(void)
{    
  /* Call the Media layer pause/resume function */
  HAL_I2S_DMAResume(&hAudioInI2s);
  
  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}


/**
* @brief Rx Transfer completed callbacks. It performs demuxing of the bit-interleaved PDM streams into 
	     byte-interleaved data suitable for PDM to PCM conversion. 1 ms of data for each microphone is 
		 written into the buffer that the user indicates when calling the BSP_AUDIO_IN_Start(...) function.
* @param hi2s: I2S handle
* @retval None
*/
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  
  uint32_t index = 0;
  
  switch(X_NUCLEO_CCA02M1_Handler.MicChannels){
  case 1:
    {
      uint16_t * DataTempI2S = &I2S_InternalBuffer[X_NUCLEO_CCA02M1_Handler.PdmBufferSize/4] ;
      for(index = 0; index < X_NUCLEO_CCA02M1_Handler.PdmBufferSize/4; index++)
      {
        X_NUCLEO_CCA02M1_Handler.PDM_Data[index] = HTONS(DataTempI2S[index]);
      }
      break;
    }
    
  case 2:
    {      
      uint16_t * DataTempI2S = &(I2S_InternalBuffer[X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2]);
      uint8_t a,b=0;
      for(index=0; index<X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2; index++) {
        a = ((uint8_t *)(DataTempI2S))[(index*2)];
        b = ((uint8_t *)(DataTempI2S))[(index*2)+1];
        ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*2)] = Channel_Demux[a & CHANNEL_DEMUX_MASK] | Channel_Demux[b & CHANNEL_DEMUX_MASK] << 4;;
        ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*2)+1] = Channel_Demux[(a>>1) & CHANNEL_DEMUX_MASK] |Channel_Demux[(b>>1) & CHANNEL_DEMUX_MASK] << 4;
      }
      break;
    }    
  case 4:
    {      
      uint16_t * DataTempI2S = &(I2S_InternalBuffer[X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2]);
      uint16_t * DataTempSPI = &(SPI_InternalBuffer[X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2]);
      uint8_t a,b=0;
      for(index=0; index<X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2; index++) {
        
        a = ((uint8_t *)(DataTempI2S))[(index*2)];
        b = ((uint8_t *)(DataTempI2S))[(index*2)+1];
        ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)] = Channel_Demux[a & CHANNEL_DEMUX_MASK] |
          Channel_Demux[b & CHANNEL_DEMUX_MASK] << 4;;
          ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)+1] = Channel_Demux[(a>>1) & CHANNEL_DEMUX_MASK] |
            Channel_Demux[(b>>1) & CHANNEL_DEMUX_MASK] << 4;
            
            a = ((uint8_t *)(DataTempSPI))[(index*2)];
            b = ((uint8_t *)(DataTempSPI))[(index*2)+1];
            ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)+2] = Channel_Demux[a & CHANNEL_DEMUX_MASK] |
              Channel_Demux[b & CHANNEL_DEMUX_MASK] << 4;;
              ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)+3] = Channel_Demux[(a>>1) & CHANNEL_DEMUX_MASK] |
                Channel_Demux[(b>>1) & CHANNEL_DEMUX_MASK] << 4;
      }
      break;
    }
  default:
    {
      
      break;
    }
    
  }
  
  BSP_AUDIO_IN_TransferComplete_CallBack();
}

/**
* @brief Rx Transfer completed callbacks. It performs demuxing of the bit-interleaved PDM streams into 
	     byte-interleaved data suitable for PDM to PCM conversion. 1 ms of data for each microphone is 
		 written into the buffer that the user indicates when calling the BSP_AUDIO_IN_Start(...) function.
* @param hi2s: I2S handle
* @retval None
*/
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  uint32_t index = 0;
  switch(X_NUCLEO_CCA02M1_Handler.MicChannels){
  case 1:
    {
      uint16_t * DataTempI2S = I2S_InternalBuffer;
      for(index = 0; index < X_NUCLEO_CCA02M1_Handler.PdmBufferSize/4; index++)
      {
        X_NUCLEO_CCA02M1_Handler.PDM_Data[index] = HTONS(DataTempI2S[index]);
      }
      break;
    }    
  case 2:
    {      
      uint16_t * DataTempI2S = I2S_InternalBuffer;
      uint8_t a,b=0;
      for(index=0; index<X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2; index++) {
        a = ((uint8_t *)(DataTempI2S))[(index*2)];
        b = ((uint8_t *)(DataTempI2S))[(index*2)+1];
        ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*2)] = Channel_Demux[a & CHANNEL_DEMUX_MASK] |
          Channel_Demux[b & CHANNEL_DEMUX_MASK] << 4;;
          ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*2)+1] = Channel_Demux[(a>>1) & CHANNEL_DEMUX_MASK] |
            Channel_Demux[(b>>1) & CHANNEL_DEMUX_MASK] << 4;
      }      
      break;
    }    
  case 4:
    {      
      uint16_t * DataTempI2S = I2S_InternalBuffer;
      uint16_t * DataTempSPI = SPI_InternalBuffer;
      uint8_t a,b=0;
      for(index=0; index<X_NUCLEO_CCA02M1_Handler.PdmBufferSize/2; index++) 
      {        
        a = ((uint8_t *)(DataTempI2S))[(index*2)];
        b = ((uint8_t *)(DataTempI2S))[(index*2)+1];
        ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)] = Channel_Demux[a & CHANNEL_DEMUX_MASK] |
          Channel_Demux[b & CHANNEL_DEMUX_MASK] << 4;;
          ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)+1] = Channel_Demux[(a>>1) & CHANNEL_DEMUX_MASK] |
            Channel_Demux[(b>>1) & CHANNEL_DEMUX_MASK] << 4;
            
            a = ((uint8_t *)(DataTempSPI))[(index*2)];
            b = ((uint8_t *)(DataTempSPI))[(index*2)+1];
            ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)+2] = Channel_Demux[a & CHANNEL_DEMUX_MASK] |
              Channel_Demux[b & CHANNEL_DEMUX_MASK] << 4;;
              ((uint8_t *)(X_NUCLEO_CCA02M1_Handler.PDM_Data))[(index*4)+3] = Channel_Demux[(a>>1) & CHANNEL_DEMUX_MASK] |
                Channel_Demux[(b>>1) & CHANNEL_DEMUX_MASK] << 4;
      }
      break;   
    }
  default:
    {      
      break;
    }
    
  }
  
  BSP_AUDIO_IN_HalfTransfer_CallBack();
}

/**
* @brief  User callback when record buffer is filled.
* @param  None
* @retval None
*/
__weak void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
  /* This function should be implemented by the user application.
  It is called into this driver when the current buffer is filled
  to prepare the next buffer pointer and its size. */
}

/**
* @brief  User callback when record buffer is half filled.
* @param  None
* @retval None
*/
__weak void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
  /* This function should be implemented by the user application.
  It is called into this driver when the current buffer is filled
  to prepare the next buffer pointer and its size. */
}

/**
* @brief  Audio IN Error callback function
* @param  None
* @retval None
*/
__weak void BSP_AUDIO_IN_Error_Callback(void)
{   
  /* This function is called when an Interrupt due to transfer error on or peripheral
  error occurs. */
}

/**
* @brief I2S error callbacks
* @param hi2s: I2S handle
* @retval None
*/
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s)
{
  /* Manage the error generated on DMA FIFO: This function
  should be coded by user (its prototype is already declared in stm32f4_discovery_audio.h) */  
  if(hi2s->Instance == AUDIO_IN_I2S_INSTANCE)
  {
    BSP_AUDIO_IN_Error_Callback();
  }
}

/**
* @}
*/

/** @defgroup X-NUCLEO-CCA02M1_AUDIO_F4_Private_Functions 
* @{
*/

/**
* @brief  Initialize the PDM library.
* @param  AudioFreq: Audio sampling frequency
* @param  ChnlNbrIn: Number of input audio channels in the PDM buffer
* @param  ChnlNbrOut: Number of desired output audio channels in the  resulting PCM buffer
* @retval None
*/
static void PDMDecoder_Init(uint32_t AudioFreq, uint32_t ChnlNbrIn, uint32_t ChnlNbrOut)
{
  uint32_t i = 0;
  /* Enable CRC peripheral to unlock the PDM library */
  __CRC_CLK_ENABLE();
  
  for(i = 0; i < ChnlNbrIn; i++)
  {
    /* Filter LP and HP Init */
    Filter[i].LP_HZ = AudioFreq / 2;
    Filter[i].HP_HZ = 10;
    Filter[i].Fs = AudioFreq;
    Filter[i].Out_MicChannels = ChnlNbrOut;
    Filter[i].In_MicChannels = ChnlNbrIn;
    PDM_Filter_Init((PDMFilter_InitStruct *)&Filter[i]);
  }
}
/**
* @brief AUDIO IN I2S MSP Init
* @param None
* @retval None
*/
static void AUDIO_IN_I2S_MspInit(void)
{
  static DMA_HandleTypeDef hdma_i2sRx;
  GPIO_InitTypeDef  GPIO_InitStruct;
  I2S_HandleTypeDef *hi2s = &hAudioInI2s;
  
  /* Enable the I2S2 peripheral clock */
  AUDIO_IN_I2S_CLK_ENABLE();
  
  /* Enable I2S GPIO clocks */
  AUDIO_IN_I2S_SCK_GPIO_CLK_ENABLE();
  AUDIO_IN_I2S_MOSI_GPIO_CLK_ENABLE();
  
  /* I2S2 pins configuration: SCK and MOSI pins ------------------------------*/
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  
  
  GPIO_InitStruct.Pin       = AUDIO_IN_I2S_SCK_PIN;
  GPIO_InitStruct.Alternate = AUDIO_IN_I2S_SCK_AF;
  HAL_GPIO_Init(AUDIO_IN_I2S_SCK_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin       = AUDIO_IN_I2S_MOSI_PIN ;
  GPIO_InitStruct.Alternate = AUDIO_IN_I2S_MOSI_AF;
  HAL_GPIO_Init(AUDIO_IN_I2S_MOSI_GPIO_PORT, &GPIO_InitStruct);
  
  /* Enable the DMA clock */
  AUDIO_IN_I2S_DMAx_CLK_ENABLE();
  
  if(hi2s->Instance == AUDIO_IN_I2S_INSTANCE)
  {
    /* Configure the hdma_i2sRx handle parameters */
    hdma_i2sRx.Init.Channel             = AUDIO_IN_I2S_DMAx_CHANNEL;
    hdma_i2sRx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hdma_i2sRx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_i2sRx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_i2sRx.Init.PeriphDataAlignment = AUDIO_IN_I2S_DMAx_PERIPH_DATA_SIZE;
    hdma_i2sRx.Init.MemDataAlignment    = AUDIO_IN_I2S_DMAx_MEM_DATA_SIZE;
    hdma_i2sRx.Init.Mode                = DMA_CIRCULAR;
    hdma_i2sRx.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_i2sRx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    hdma_i2sRx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_i2sRx.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_i2sRx.Init.PeriphBurst         = DMA_MBURST_SINGLE;
    
    hdma_i2sRx.Instance = AUDIO_IN_I2S_DMAx_STREAM;
    
    /* Associate the DMA handle */
    __HAL_LINKDMA(hi2s, hdmarx, hdma_i2sRx);
    
    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(&hdma_i2sRx);
    
    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_i2sRx);
  }
  
  /* I2S DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(AUDIO_IN_I2S_DMAx_IRQ, AUDIO_IN_IRQ_PREPRIO, AUDIO_IN_IRQ_PREPRIO);
  HAL_NVIC_EnableIRQ(AUDIO_IN_I2S_DMAx_IRQ);
}

/**
* @brief AUDIO IN SPI MSP Init
* @param None
* @retval None
*/
static void AUDIO_IN_SPI_MspInit()
{
  
  SPI_HandleTypeDef *hspi = &hAudioInSPI;
  static DMA_HandleTypeDef hdma_rx;
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable GPIO TX/RX clock */
  AUDIO_IN_SPI_SCK_GPIO_CLK_ENABLE();
  AUDIO_IN_SPI_MISO_GPIO_CLK_ENABLE();
  AUDIO_IN_SPI_MOSI_GPIO_CLK_ENABLE();
  /* Enable SPI3 clock */
  AUDIO_IN_SPI_CLK_ENABLE();
  /* Enable DMA1 clock */
  AUDIO_IN_SPI_DMAx_CLK_ENABLE();
  
  /*##-2- Configure peripheral GPIO ##########################################*/
  /* SPI SCK GPIO pin configuration  */
  GPIO_InitStruct.Pin       = AUDIO_IN_SPI_SCK_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = AUDIO_IN_SPI_SCK_AF;
  
  HAL_GPIO_Init(AUDIO_IN_SPI_SCK_GPIO_PORT, &GPIO_InitStruct);
  
  /* SPI MOSI GPIO pin configuration  */
  GPIO_InitStruct.Pin = AUDIO_IN_SPI_MOSI_PIN;
  GPIO_InitStruct.Alternate = AUDIO_IN_SPI_MOSI_AF;
  HAL_GPIO_Init(AUDIO_IN_SPI_MOSI_GPIO_PORT, &GPIO_InitStruct);
  
  /* Configure the DMA handler for Transmission process */
  hdma_rx.Instance                 = AUDIO_IN_SPI_RX_DMA_STREAM;
  hdma_rx.Init.Channel             = AUDIO_IN_SPI_RX_DMA_CHANNEL;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
  hdma_rx.Init.Mode                = DMA_CIRCULAR;
  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma_rx.Init.MemBurst            = DMA_MBURST_INC4;
  hdma_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
  
  HAL_DMA_Init(&hdma_rx);
  
  /* Associate the initialized DMA handle to the the SPI handle */
  __HAL_LINKDMA(hspi, hdmarx, hdma_rx);
  
}

/**
* @brief Audio Timer Init
* @param None
* @retval None
*/
static uint8_t AUDIO_IN_Timer_Init(void){
  
  GPIO_InitTypeDef   GPIO_InitStruct;
  
  /* Enable AUDIO_TIMER clock*/
  AUDIO_IN_TIMER_CLK_ENABLE();
  AUDIO_IN_TIMER_CHOUT_GPIO_PORT_CLK_ENABLE();
  AUDIO_IN_TIMER_CHIN_GPIO_PORT_CLK_ENABLE();
  
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  
  GPIO_InitStruct.Alternate = AUDIO_IN_TIMER_CHIN_AF;
  GPIO_InitStruct.Pin = AUDIO_IN_TIMER_CHIN_PIN;
  HAL_GPIO_Init(AUDIO_IN_TIMER_CHIN_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Alternate = AUDIO_IN_TIMER_CHOUT_AF;
  GPIO_InitStruct.Pin = AUDIO_IN_TIMER_CHOUT_PIN;
  HAL_GPIO_Init(AUDIO_IN_TIMER_CHOUT_GPIO_PORT, &GPIO_InitStruct);
  
  TimDividerHandle.Instance = AUDIO_IN_TIMER;
  
  /* Configure the Input: channel_1 */
  sICConfig.ICPolarity  = TIM_ICPOLARITY_RISING;
  sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sICConfig.ICPrescaler = TIM_ICPSC_DIV1;
  sICConfig.ICFilter = 0;
  if(HAL_TIM_IC_ConfigChannel(&TimDividerHandle, &sICConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  
  /* Configure TIM1 in Gated Slave mode for the external trigger (Filtered Timer
  Input 1) */
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.SlaveMode    = TIM_SLAVEMODE_EXTERNAL1;
  if( HAL_TIM_SlaveConfigSynchronization(&TimDividerHandle, &sSlaveConfig) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  
  /* Initialize TIM3 peripheral in PWM mode*/
  TimDividerHandle.Init.Period            = 1;
  TimDividerHandle.Init.Prescaler         = 0;
  TimDividerHandle.Init.ClockDivision     = 0;
  TimDividerHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TimDividerHandle.Init.RepetitionCounter = 0;
  if(HAL_TIM_PWM_Init(&TimDividerHandle) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  
  /* Configure the PWM_channel_1  */
  sOCConfig.OCMode     = TIM_OCMODE_PWM1;
  sOCConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
  sOCConfig.Pulse = 1;
  if(HAL_TIM_PWM_ConfigChannel(&TimDividerHandle, &sOCConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  return AUDIO_OK;
}

/**
* @brief Audio Timer Start
* @param None
* @retval None
*/
static uint8_t AUDIO_IN_Timer_Start(){
  
  if(HAL_TIM_IC_Start(&TimDividerHandle, TIM_CHANNEL_1) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  /* Start the Output Compare */
  if(HAL_TIM_OC_Start(&TimDividerHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    return AUDIO_ERROR;
  }
  
  return AUDIO_OK;
}



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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
