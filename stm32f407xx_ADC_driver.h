/**
 * @file stm32f407xx_adc_driver.h
 * @brief Header file for STM32F407 ADC
 * @author Karan Patel
 * @date 15 August 2024
 * @board STM32F407VG-DISC1
 */

/**
 * @defgroup ADC_Configuration ADC Configuration
 * @{
 */

#include "stm32f407xx.h"

/** @brief ADC data alignment */
#define ADC_DataAlign_RIGHT	 0 /**< Right alignment for ADC data */
#define ADC_DataAlign_LEFT 1  /**< Left alignment for ADC data */

/** @brief ADC sample time */
#define ADC_SampleTime_3_Cycle    0
#define ADC_SampleTime_15_Cycle   1
#define ADC_SampleTime_28_Cycle   2
#define ADC_SampleTime_56_Cycle   3
#define ADC_SampleTime_84_Cycle   4
#define ADC_SampleTime_112_Cycle  5
#define ADC_SampleTime_144_Cycle  6
#define ADC_SampleTime_480_Cycle  7

/** @brief ADC channels */
#define ADC_Channel_0  0  /**< ADC channel 0 */
#define ADC_Channel_1  1  /**< ADC channel 1 */
#define ADC_Channel_2  2  /**< ADC channel 2 */
#define ADC_Channel_3  3  /**< ADC channel 3 */
#define ADC_Channel_4  4  /**< ADC channel 4 */
#define ADC_Channel_5  5  /**< ADC channel 5 */
#define ADC_Channel_6  6  /**< ADC channel 6 */
#define ADC_Channel_7  7  /**< ADC channel 7 */
#define ADC_Channel_8  8  /**< ADC channel 8 */
#define ADC_Channel_9  9  /**< ADC channel 9 */
#define ADC_Channel_10 10 /**< ADC channel 10 */
#define ADC_Channel_11 11 /**< ADC channel 11 */
#define ADC_Channel_12 12 /**< ADC channel 12 */
#define ADC_Channel_13 13 /**< ADC channel 13 */
#define ADC_Channel_14 14 /**< ADC channel 14 */
#define ADC_Channel_15 15 /**< ADC channel 15 */
#define ADC_Channel_16 16 /**< ADC channel 16 */

/** @} */


#define ADC_Conversion_Once        0
#define ADC_Conversion_Continuous  1

/**
 * @struct ADC_Config_t
 * @brief Structure to hold ADC configuration parameters
 */
typedef struct {
    uint32_t ADC_DataAlign;    /**< Data alignment for ADC */
    uint32_t ADC_Channel;      /**< ADC channel */
    uint32_t ADC_SampleTime;   /**< Sample time for ADC */
    uint32_t ADC_ConversionMode;
} ADC_Config_t;

/**
 * @struct ADC_Handle_t
 * @brief Structure to hold ADC handle and configuration
 */
typedef struct {
    ADC_RegDef_t *pADCx;        /**< Pointer to ADC peripheral */
    ADC_Config_t ADCConfig;    /**< ADC configuration */
} ADC_Handle_t;

/**
 * @brief Function to control the peripheral clock of ADC
 * @param pADCx Pointer to the ADC peripheral
 * @param EnorDi Enable or disable the peripheral clock (1: enable, 0: disable)
 * @retval None
 */
void ADC_PeriClockControl(ADC_RegDef_t *pADCx, uint32_t EnorDi);

/**
 * @brief Function to initialize ADC for single channel conversion
 * @param pADCHandler Pointer to ADC handle structure
 * @retval None
 */
void ADC_Init_SingleChannel(ADC_Handle_t *pADCHandler);

/**
 * @brief Function to start ADC conversion
 * @param pADCHandler Pointer to ADC handle structure
 * @retval None
 */
void ADC_StartConversion(ADC_Handle_t *pADCHandler);

/**
 * @brief Function to read ADC conversion result
 * @param pADCHandler Pointer to ADC handle structure
 * @retval 16-bit ADC conversion result
 */
uint16_t ADC_ReadConversion(ADC_Handle_t *pADCHandler);




void ADC_PeripheralEnable(ADC_RegDef_t *pADCx,uint8_t value);


void ADC_Interrupt_Enable(ADC_Handle_t *pADCHandler);



void ADC_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi);

void ADC_ApplicationEventCallback(ADC_Handle_t *pADCHandle);


