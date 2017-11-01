#ifndef _LCD_FLASH_H
#define _LCD_FLASH_H

#include "OS_StartFile.h"
#include <string.h>


void FF_Init(void);
u8 Write_FF(u8 value);
u8 Write_FF2(u8 value);
void FF_ChipErase(void);
void FF_WriteEnable(void);
u8 FF_ReadStatusReg(void);
void FF_WriteStatusReg(u8 dat);
void FF_PageWrite(u8 *pBuffer, u32 addr, u16 num);  
void FF_WaitForWriteEnd(void);

void Read_FLASH(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead,u8 NUM);

#endif /* end of lcd_flash.h*/
