#ifndef I2C_H
#define I2C_H


#include <stm32f4xx.h>
#include <stm32f4xx_i2c.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#define SLAVE_ADDRESS 0x3D // the slave address (example)

void init_I2C1(void);
/* This function issues a start condition and
 * transmits the slave address + R/W bit
 *
 * Parameters:
 * 		I2Cx --> the I2C peripheral e.g. I2C1
 * 		address --> the 7 bit slave address
 * 		direction --> the tranmission direction can be:
 * 						I2C_Direction_Tranmitter for Master transmitter mode
 * 						I2C_Direction_Receiver for Master receiver
 */
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
/* This function transmits one byte to the slave device
 * Parameters:
 *		I2Cx --> the I2C peripheral e.g. I2C1
 *		data --> the data byte to be transmitted
 */
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);

/* This function reads one byte from the slave device
 * and acknowledges the byte (requests another byte)
 */
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
/* This function reads one byte from the slave device
 * and doesn't acknowledge the recieved data
 */
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);

/* This funtion issues a stop condition and therefore
 * releases the bus
 */
void I2C_stop(I2C_TypeDef* I2Cx);

int I2C_Read(I2C_TypeDef* I2Cx,uint8_t *rb,int nb);
int I2C_Write(I2C_TypeDef* I2Cx,uint8_t *rb,int nb);

#ifdef __cplusplus
 }
#endif /* __cplusplus */
#endif
