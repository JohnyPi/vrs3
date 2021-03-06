/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "assignment.h"
#include <stddef.h>
#include "stm32f3xx_it.h"



enum EDGE_TYPE edgeDetect(uint8_t pin, uint8_t samples)
{
	 static uint8_t count_hi=0;
	 static uint8_t count_low=0;
	 static enum EDGE_TYPE edge_type;
	 edge_type = NONE;

	  if(!(pin))
	  {	  count_hi= 0;
		  count_low++;
		  if(count_low >= samples)
		  	  {
			  	  edge_type = FALL;
			  	  count_low=0;
		  	  }
		  else
		  {
			  edge_type = NONE;
		  }
	  }


	  if(pin)
	  {   	  count_low= 0;
		  count_hi++;
		  if(count_hi >= samples)
		  	  {
			  	  edge_type = RISE;
			  	  count_hi= 0;
		  	  }
		  else
		  {
			  edge_type = NONE;
		  }
	  }

	  return edge_type;
}

int main(void)
{
  /*
   *  DO NOT WRITE TO THE WHOLE REGISTER!!!
   *  Write to the bits, that are meant for change.
   */
	  //Systick init
	  LL_Init1msTick(8000000);
	  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	  LL_SetSystemCoreClock(8000000);

  /*
   * TASK - configure MCU peripherals so that button state can be read and LED will blink.
   * Button must be connected to the GPIO port A and its pin 3.
   * LED must be connected to the GPIO port A and its pin 4.
   *
   * In header file "assignment.h" define macros for MCU registers access and LED blink application.
   * Code in this file must use these macros for the peripherals setup.
   * Code of the LED blink application is already given so just the macros used in the application must be defined.
   */


  /* Enable clock for GPIO port A*/
  //*((volatile uint32_t *) (uint32_t)(0x40021000 + 0x14U)) |= (uint32_t)(1 << 17);
  RCC_AHBENR_REG |= (uint32_t)(1 << 17);

  /* GPIOA pin 3 and 4 setup */
  //set PA_3 as input
  GPIOA_MODER_REG &= ~(uint32_t)(0x3 << 6);
  //reset PA_4 and set PA_4 as output
  GPIOA_MODER_REG &= ~(uint32_t)(0x3 << 8);
  GPIOA_MODER_REG |= (1 << 8);

  /*GPIO OTYPER register*/
  GPIOA_OTYPER_REG &= ~(1 << 4);

  /*GPIO OSPEEDR register*/
  //Set Low speed for GPIOB pin 4
  GPIOA_OSPEEDER_REG &= ~(0x3 << 8);

  /*GPIO PUPDR register, reset*/
  //Set pull up for GPIOA pin 3 (input)
  GPIOA_PUPDR_REG |= (1 << 6);
  //GPIOA_PUPDR_REG |= (0x2 << 6);
  //Set no pull for GPIOA pin 4
  GPIOA_PUPDR_REG &=~ (0x3 << 8);
  //GPIOA_PUPDR_REG = (1 << 8);


  while (1)
  {


      switch (edgeDetect((BUTTON_GET_STATE(3)), 5))
      {
          case NONE:
          {
    		  LED_OFF(4);
    		  break;
          }
          case RISE:
          {
        	  //LED_ON(4);
              break;
          }
          case FALL:
          {
    		  LED_ON(4);
    		  break;
          }
          default:
          {
              break;
          }
      }
  }

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
