/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C_PROGRAM_C
 *       Module:  -
 *
 *  Description:   C program for I2C
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include"I2C_private.h"
#include"I2C_interface.h"
#include"GPIO_private.h"
#include"GPIO_interface.h"

void I2C_voidMasterInitTx(u16 Copy_SlaveAdd,u8 *Copy_Data[]){
	/*Setting GPIO MODER to alternative function*/
	GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_6,GPIO_ALT);
	/*Setting I2C as Alternative function*/
	MSKP_REG(GPIO_B_AFRL,24,4);
	MSKP_REG(GPIO_B_AFRH,4,4);
	/*Enabling I2C*/
	SET_BIT(I2C1->CR1,0);
	SET_BIT(I2C1->CR1,8);
	/*Start bit */
	I2C1->CR1 |= 1<<8;                		//I2C Start
	while (!(I2C1->SR1 & 0x0001));   //waiting
	/*Sending the Address of the slave*/
	MSKP_REG(I2C1->DR,0,Copy_SlaveAdd);
	/*Waiting for the address to be sent*/
	while (!(I2C1->SR1 & 0x0002));
	u32 SR2_V = (I2C1->SR2); /*to clear SR1*/
	u8 i=0;
	/*Sending the Data*/
	while(Copy_Data[i]!='\0'){
	I2C1->DR = Copy_Data[i];
	/*Waiting for Ack*/
	while (GET_BIT(I2C1->SR1,7)==0);
	i++;
	}
	/*Sending the Stop Bit*/
	SET_BIT(I2C1->CR1,9);
	while (I2C1->SR2 & 0x0002);

}



void I2C_u8MasterRx(u16 Copy_SlaveAdd,u8 *Copy_DataToReceive[],I2C_ACK_t Copy_ACK){
	/*Setting GPIO MODER to alternative function*/
		GPIO_voidSetPinMode(GPIO_PORT_B,GPIO_PIN_6,GPIO_ALT);
		/*Setting I2C as Alternative function*/
		MSKP_REG(GPIO_B_AFRL,24,4);
		MSKP_REG(GPIO_B_AFRH,4,4);
		/*Enabling I2C*/
		SET_BIT(I2C1->CR1,0);
		SET_BIT(I2C1->CR1,8);
		/*Start bit */
		I2C1->CR1 |= 1<<8;                		//I2C Start
		while (!(I2C1->SR1 & 0x0001));   //waiting
		/*Sending the Address of the slave*/
		MSKP_REG(I2C1->DR,0,Copy_SlaveAdd);
		/*Waiting for the address to be sent*/
		while (!(I2C1->SR1 & 0x0002));
		u32 SR2_V = (I2C1->SR2); /*to clear SR1*/
		u8 i=0;
		/*
		 * Setting tha Ack
		 * Receiving the Data
		 */
		MSKP_REG(I2C1->CR1,10,Copy_ACK);
		while(GET_BIT(I2C1->SR1,2)==1){
		while (!(I2C1->SR1 & 0x00000040));
		Copy_DataToReceive[i]=I2C1->DR;
		i++;
		}
		/*Sending the Stop Bit*/
			SET_BIT(I2C1->CR1,9);
			while (I2C1->SR2 & 0x0002);

}

void I2C_voidSetSlaveAdd1(u16 Copy_Address){
	I2C1->OAR1=Copy_Address;

}
void I2C_voidSetSlaveAdd2(u16 Copy_Address){
	I2C1->OAR2=Copy_Address;

}

void I2C_voidClockConfig(I2C_ClockConfig_t Copy_ClockConfig){

	MSKP_REG(I2C1->CR2,0,Copy_ClockConfig.I2C_Freq);   /*Peripheral Freq*/
	MSKP_REG(I2C1->CCR,15,Copy_ClockConfig.I2C_Mode);  /*Standard or fast*/
	MSKP_REG(I2C1->CCR,14,Copy_ClockConfig.I2C_FM_DC); /*The duty cycle for FM*/
	u16 CCR_Value=((Copy_ClockConfig.I2C_Freq*1000)/(2*Copy_ClockConfig.I2C_SCL)); /*Calculating the Clock control*/
	MSKP_REG(I2C1->CCR,0,CCR_Value);
	u16 TRISE_Value=(Copy_ClockConfig.I2C_TRISE*Copy_ClockConfig.I2C_Freq*0.001)+1;  /*TRISE in ns and I2C Freq in MHz*/
	MSKP_REG(I2C1->TRISE,0,TRISE_Value);

}
