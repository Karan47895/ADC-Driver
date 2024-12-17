

#include "stm32f407xx_ADC_driver.h"

/**
 * @brief Function to control the peripheral clock of ADC
 * @param pADCx Pointer to the ADC peripheral
 * @param EnorDi Enable or disable the peripheral clock (ENABLE: enable, DISABLE: disable)
 * @retval None
 */
void ADC_PeriClockControl(ADC_RegDef_t *pADCx,uint32_t EnorDi){
		if(EnorDi == ENABLE)
		{
			if(pADCx == ADC1)
			{
				ADC1_PCLK_EN();
			}
			else if(pADCx == ADC2)
			{
				ADC2_PCLK_EN();
			}
			else if(pADCx == ADC3){
                ADC3_PCLK_EN();
			}
		}
		else
		{
			if(pADCx == ADC1)
			{
				ADC1_PCLK_DI();
			}
			else if(pADCx == ADC2)
			{
				ADC2_PCLK_DI();
			}
			else if(pADCx == ADC3){
				ADC3_PCLK_DI();
			}
		}
}


/**
 * @brief Function to initialize ADC for single channel conversion
 * @param pADCHandler Pointer to ADC handle structure
 * @retval None
 */

void ADC_PeripheralEnable(ADC_RegDef_t *pADCx,uint8_t value){
	if(value==1){
		pADCx->CR2|=(1<<0);
	}
	else {
		pADCx->CR2&=~(1<<0);
	}
}


void ADC_Init_SingleChannel(ADC_Handle_t *pADCHandler){

	ADC_PeriClockControl(pADCHandler->pADCx,ENABLE);
/**
	* @brief: Configure Data Align
	*/
	if(pADCHandler->ADCConfig.ADC_DataAlign == ADC_DataAlign_RIGHT){
			pADCHandler->pADCx->CR2 &= ~(1<<11);
	}
	else{
			pADCHandler->pADCx->CR2 |= (1<<11);
	}

/**
	* @brief: Configure Continuious Mode
	*/
	pADCHandler->pADCx->CR2 |= (1<<1) ;

///**
//	* @brief: Configure Conversion start due to external event.
//	*/
//	pADCHandler->pADCx->CR2 |= (0<<24);

/**
	* @brief: Configure Sample Cycle
	*/

	uint32_t value=pADCHandler->ADCConfig.ADC_SampleTime;
	if(pADCHandler->ADCConfig.ADC_Channel <= ADC_Channel_9){
		pADCHandler->pADCx->SMPR2 |= (uint32_t)(value<<(3*(pADCHandler->ADCConfig.ADC_Channel)));
	}
	else{
		pADCHandler->pADCx->SMPR1 |= (uint32_t)(value<<(3*(pADCHandler->ADCConfig.ADC_Channel-10)));
	}

/**
	* @brief: Configure Sequence
	*/
	pADCHandler->pADCx->SQR3 |= (pADCHandler->ADCConfig.ADC_Channel);


  // Configure the length of the regular channel.
	pADCHandler->pADCx->SQR1|=(0<<20);

}



/**
 * @brief Function to start ADC conversion
 * @param pADCHandler Pointer to ADC handle structure
 * @retval None
 */
void ADC_StartConversion(ADC_Handle_t *pADCHandler){
    pADCHandler->pADCx->CR2|=(1<<30);
    if(pADCHandler->ADCConfig.ADC_ConversionMode==ADC_Conversion_Continuous){
         pADCHandler->pADCx->CR2|=(1<<1);
    }
}

/**
 * @brief Function to read ADC conversion result
 * @param pADCHandler Pointer to ADC handle structure
 * @retval 16-bit ADC conversion result
 */
uint16_t ADC_ReadConversion(ADC_Handle_t *pADCHandler){
	while((pADCHandler->pADCx->SR & (1<<1))==0);
	return (uint16_t)(pADCHandler->pADCx->DR & (0xffff));
}

//void ADC_Interrupt_Enable(ADC_Handle_t *pADCHandle){
//	pADCHandle->pADCx->CR1|=(1<<5);
//}

//IRQ configuration and ISR handling.
void ADC_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi){
	 if(EnorDi==ENABLE){
		 if(IRQNumber<=31){
			//Program ISER0 register.
           *NVIC_ISER0|=(1<<IRQNumber);
		 }
		 else if(IRQNumber>31 &&IRQNumber<64){
			 //Program ISER1 register.
		  *NVIC_ISER1|=(1<<(IRQNumber)%32);
		 }
		 else if(IRQNumber>=64 &&IRQNumber<96){
			 //Program ISER2 register
			 *NVIC_ISER2|=(1<<(IRQNumber)%64);
		 }
	 }
	 else {
		 if(IRQNumber<=31){
			 *NVIC_ICER0|=(1<<IRQNumber);
		   }
         else if(IRQNumber>31 &&IRQNumber<64){
        	 *NVIC_ICER1|=(1<<(IRQNumber)%32);
		   }
		 else if(IRQNumber>=64 &&IRQNumber<96){
			 *NVIC_ICER2|=(1<<(IRQNumber)%64);
		   }
	 }
}


void ADC_Interrupt_Enable(ADC_Handle_t *pADCHandler){
  pADCHandler->pADCx->CR1|=(1<<5);
}



__weak void ADC_ApplicationEventCallback(ADC_Handle_t *pADCHandle)
{

}


