/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C_INTERFACE_H
 *       Module:  -
 *
 *  Description:   header for the I2C INTERFACING
 *
 *********************************************************************************************************************/
#ifndef  I2C_INTERFACE_H
#define  I2C_INTERFACE_H

#include"BIT_MATH.h"
#include"STD_TYPES.h"
typedef enum{
	SM,		/*Standard Mode*/
	FM,		/*Fast Mode*/
}I2C_Mode_t;

typedef enum{
	Duty_2,
	Duty_16O9,
}I2C_FM_Duty_t;

/*CCR */



typedef enum {
	ACK_DISABLE,
	ACK_ENABLE,
}I2C_ACK_t;

typedef struct {
	u8				 I2C_Freq; /*From   2MHz to 50MHz*/
	I2C_Mode_t 		 I2C_Mode;
	I2C_FM_Duty_t	 I2C_FM_DC; /*Place Duty_2 in Standard mode*/
	u8				 I2C_SCL;
	u8				 I2C_TRISE;
}I2C_ClockConfig_t;

void I2C_voidMasterInitTx(u16 Copy_SlaveAdd,u8 *Copy_Data[]);
void I2C_u8MasterRx(u16 Copy_SlaveAdd,u8 *Copy_DataToReceive[],I2C_ACK_t Copy_ACK);
void I2C_voidSetSlaveAdd1(u16 Copy_Address);
void I2C_voidSetSlaveAdd2(u16 Copy_Address);
void I2C_voidClockConfig(I2C_ClockConfig_t Copy_ClockConfig);





#endif
