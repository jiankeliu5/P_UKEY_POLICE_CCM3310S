/*All rights reserved */
/*************************************************
  	  Copyright (C), 2010-2013, C*Core Technology Co., Ltd
  File name:clk.c                              // 文件名
  Author:       Version:1.0     Date:          // 作者、版本及完成日期
  Description:                                 // 用于详细说明此程序文件完成的主要功能
  Others:                                      // 其它内容的说明
  History:                                     // 修改历史记录列表，每条修改记录应包括修改日期、修改
                                               // 者及修改内容简述  
    1. Date:         2013-03-13
       Author:       徐凯
       Modification: 按照《天津国芯科技有限公司产品应用部C语言编程规范》V1.0标准化
/*************************************************/
#define  CLK_SYMBOL
#include "includes.h"

UINT32 g_sys_clk = EFLASH_SYS_CLK_40M;

/*******************************************
*
* 
*
*******************************************/
void Delay(UINT32 times)
{
	while(times--);
}
/////////////////////////////////////////////



/*******************************************
*
* 更新CCVR寄存器的值
*
*******************************************/
void UpdataCardReg()
{
	CLK_UCR |=0x00000002;
}
/////////////////////////////////////////////



/*******************************************
*
* 更新GCVR寄存器的值 
*
******************************************/
void UpdataGlobalReg()
{
	CLK_UCR |=0x00000001;
}
/////////////////////////////////////////////



/*******************************************
*
* 更新PCVR寄存器的值
*
******************************************/
void UpdataPLLReg()
{
	CLK_UCR |=0x00000004;
}


/*******************************************
*
* 选择内部32K时钟源，
*
*******************************************/	
void InternalClk_32K()
{
	//internal clk 32k
	//1.set clock mode 1,将开发板 CLKMODE pin脚跳 1, 选择内部时钟
	
	//2.set PLLBI_REG_32KSEL 1
	CLK_G1CR |=0x00080000;  					//选择32k作为系统输出时钟
	UpdataGlobalReg();							//更新GCVR
	Delay(500);
	//3.set PLLBI_REG_CLKSEL 01
	CLK_CCVR =(CLK_CCVR&0xfffcffff)|0x00010000;  //选择内部32k时钟源
	//4.set PLLBI_REG_CLKEXT 0
	CLK_CCVR &=0xfffbffff; 						//选择内部时钟源 
	UpdataCardReg();							//更新CCVR
	Delay(500);
}

/*******************************************
*
* 选择内部1M时钟源，
*
*******************************************/	
void InternalClk_1M()
{
	//internal clk 1M
	//1.set clock mode 1,将开发板 CLKMODE pin脚跳 1,选择内部时钟源
	
	//2.set PLLBI_REG_32KSEL 0
	CLK_G1CR &=0xfff7ffff;    						 //选择1M作为系统输出时钟  
	UpdataGlobalReg();                               //更新GCVR
	//3.set PLLBI_REG_CLKSEL 01
	CLK_CCVR =(CLK_CCVR&0xfffcffff)|0x00010000;        // 选择内部32K or 1M时钟源
	//4.set PLLBI_REG_CLKEXT 0
	CLK_CCVR &=0xfffbffff;                            // 选择内部时钟源 
	UpdataCardReg();								  //更新CCVR	
	Delay(500);
	
}


/*******************************************
*
* 选择内部4M时钟源，
*
*******************************************/	
void InternalClk_4M()
{
	//internal clk 32M
	//1.set clock mode 1,将开发板 CLKMODE pin脚跳 1,选择内部时钟源
	
	//2.set PLLBI_REG_CLKSEL 00
	CLK_CCVR &=0xfffcffff;                  // clksel[1:0]=00  选择内部32M Divid 时钟源
	//3.set PLLBI_REG_CLKEXT 0
	CLK_CCVR &=0xfffbffff;                  // 通过程序选择内部时钟源
	//div freq
	CLK_CCVR =(CLK_CCVR&0xffff0fff)|0x00003000; //配置分频值 F = 32Mosc/2(PLLBI_REG_CLKDIV+1) 即 F = 32/2*(3+1) = 4M
	UpdataCardReg();                        // 更新CCVR
	
	Delay(500);

}


/*******************************************
*
* 选择内部8M时钟源，
*
*******************************************/	
void InternalClk_8M()
{
	//internal clk 32M
	//1.set clock mode 1,将开发板 CLKMODE pin脚跳 1,选择内部时钟源
	
	//2.set PLLBI_REG_CLKSEL 00
	CLK_CCVR &=0xfffcffff;                  // clksel[1:0]=00  选择内部32M Divid 时钟源
	//3.set PLLBI_REG_CLKEXT 0
	CLK_CCVR &=0xfffbffff;                  // 通过程序选择内部时钟源
	//div freq
	CLK_CCVR =(CLK_CCVR&0xffff0fff)|0x00001000; //配置分频值 F = 32Mosc/2(PLLBI_REG_CLKDIV+1) 即 F = 32/2*(1+1) = 8M
	UpdataCardReg();                        // 更新CCVR
	
	Delay(500);

}


/*******************************************
*
* 选择内部16M时钟源，
*
*******************************************/	
void InternalClk_16M()
{
	//internal clk 32M                       
	//1.set clock mode 1,将开发板 CLKMODE pin脚跳 1,选择内部时钟源
	
	//2.set PLLBI_REG_CLKSEL 00
	CLK_CCVR &=0xfffcffff;                  // clksel[1:0]=00  选择内部32M Divid 时钟源
	//3.set PLLBI_REG_CLKEXT 0
	CLK_CCVR &=0xfffbffff;                  // 通过程序选择内部时钟源
	//div freq
	CLK_CCVR =(CLK_CCVR&0xffff0fff)|0x00000000; //配置分频值 F = 32Mosc/2(PLLBI_REG_CLKDIV+1) 即 F = 32/2*(0+1) = 16M
	UpdataCardReg();                        // 更新CCVR
	
	Delay(500);

}


/*******************************************
*
* 选择内部32M时钟源，
*
*******************************************/	
void InternalClk_32M()
{
	//internal clk 32M
	//1.set clock mode 1  将开发板 CLKMODE pin脚跳 1  选择内部32M时钟
	
	//2.set PLLBI_REG_CLKSEL 10
	CLK_CCVR =(CLK_CCVR&0xfffcffff)|0x00020000;	//clksel[1:0] =10b 设置内部时钟为32M
	//3.set PLLBI_REG_CLKEXT 0	
	CLK_CCVR &=0xfffbffff;						//选择内部时钟源
	UpdataCardReg();							//将CCVR内容更新到Clock module				
	Delay(500);
}


/*******************************************
*
* 选择内部64M时钟源
*
*******************************************/	
void InternalClk_64M()
{
	//internal clk 32M
	//1.set clock mode 1  将开发板 CLKMODE pin脚跳 1  选择内部32M时钟
	
	//2.set PLLBI_REG_CLKSEL 11         
	CLK_CCVR =(CLK_CCVR&0xfffcffff)|0x00030000;  // clksel[1:0] =11b 选择32M*2 时钟源 即倍频 F = 64M
	
	//3.set PLLBI_REG_CLKEXT 0
	CLK_CCVR &=0xfffbffff;                       // 选择内部时钟源 
	UpdataCardReg();                             // 更新CCVR
	
	Delay(500);

}
/*******************************************
*
*  选择外部12M时钟源
*
*******************************************/
void ExternalClk_12M()//xiang
{
	//Externaled clk	
	//set clock mode 0 将开发板 CLKMODE pin脚跳 0
	//1.set clock mode 0,将开发板 CLKMODE pin脚跳 0,选择外部时钟源
	
	//2.清除PHY_BIT_DIR控制位，由时钟模块寄存器控制PLL
	CLEAR_PHY_BIT_DIR;
	
	//3.PLL en
	CLK_PCVR |=0x00200000;                        // PLLBI_RFG_PLLEN =1, pll enable     
	     
	//4.set PLLCLK_SEL 0,  PLL_DIV 9
	CLK_PCVR =(CLK_PCVR&0xffb0ffff)|0x00090000;   // PLLCLK_SEL = 0, select 240M clock, F = 240/2(9+1) = 12Mhz

	UpdataPLLReg();                               // 更新PCVR
	Delay(500);
}

/*******************************************
*
*  选择外部20M时钟源
*
*******************************************/
void ExternalClk_20M()
{
	//1.set clock mode 0,将开发板 CLKMODE pin脚跳 0,选择外部时钟源
	
	//2.清除PHY_BIT_DIR控制位，由时钟模块寄存器控制PLL
	CLEAR_PHY_BIT_DIR;
	
	//3.PLL en
	CLK_PCVR |=0x00200000;                        // PLLBI_RFG_PLLEN =1, pll enable     
	     
	//4.set PLLCLK_SEL 0,  PLL_DIV 5 
	CLK_PCVR =(CLK_PCVR&0xffb0ffff)|0x00050000;   // PLLCLK_SEL = 0, select 240M clock, F = 240/2(5+1) = 20Mhz

	UpdataPLLReg();                               // 更新PCVR
	Delay(500);
}

/*******************************************
*
*  选择外部24M时钟源
*
*******************************************/
void ExternalClk_24M()
{
	//1.set clock mode 0,将开发板 CLKMODE pin脚跳 0,选择外部时钟源
	
	//2.清除PHY_BIT_DIR控制位，由时钟模块寄存器控制PLL
	CLEAR_PHY_BIT_DIR;
	
	//3.PLL en
	CLK_PCVR |=0x00200000;                        // PLLBI_RFG_PLLEN =1, pll enable     
	     
	//4.set PLLCLK_SEL 0,  PLL_DIV 4
	CLK_PCVR =(CLK_PCVR&0xffb0ffff)|0x00040000;   // PLLCLK_SEL = 0, select 240M clock, F = 240/2(4+1) = 24Mhz

	UpdataPLLReg();                               // 更新PCVR
	Delay(500);
}

/*******************************************
*
*  选择外部30M时钟源
*
*******************************************/
void ExternalClk_30M()
{
	//1.set clock mode 0,将开发板 CLKMODE pin脚跳 0,选择外部时钟源
	
	//2.清除PHY_BIT_DIR控制位，由时钟模块寄存器控制PLL
	CLEAR_PHY_BIT_DIR;
	
	//3.PLL en
	CLK_PCVR |=0x00200000;                        // PLLBI_RFG_PLLEN =1, pll enable     
	     
	//4.set PLLCLK_SEL 0,  PLL_DIV 3 
	CLK_PCVR =(CLK_PCVR&0xffb0ffff)|0x00030000;   // PLLCLK_SEL = 0, select 240M clock, F = 240/2(3+1) = 30Mhz

	UpdataPLLReg();                               // 更新PCVR
	Delay(500);
}

/*******************************************
*
*  选择外部40M时钟源
*
*******************************************/
void ExternalClk_40M()
{
	//1.set clock mode 0,将开发板 CLKMODE pin脚跳 0,选择外部时钟源
	
	//2.清除PHY_BIT_DIR控制位，由时钟模块寄存器控制PLL
	CLEAR_PHY_BIT_DIR;
	
	//3.PLL en
	CLK_PCVR |=0x00200000;                        // PLLBI_RFG_PLLEN =1, pll enable     
	     
	//4.set PLLCLK_SEL 0,  PLL_DIV 2 
	CLK_PCVR =(CLK_PCVR&0xffb0ffff)|0x00020000;   // PLLCLK_SEL = 0, select 240M clock, F = 240/2(2+1) = 40Mhz

	UpdataPLLReg();                               // 更新PCVR
	Delay(500);
}

/*******************************************
*
*  选择外部60M时钟源
*
*******************************************/
void ExternalClk_60M()
{
	//1.set clock mode 0,将开发板 CLKMODE pin脚跳 0,选择外部时钟源
	
	//2.清除PHY_BIT_DIR控制位，由时钟模块寄存器控制PLL
	CLEAR_PHY_BIT_DIR;
	
	//3.PLL en
	CLK_PCVR |=0x00200000;                        // PLLBI_RFG_PLLEN =1, pll enable     
	     
	//4.set PLLCLK_SEL 0,  PLL_DIV 1 
	CLK_PCVR =(CLK_PCVR&0xffb0ffff)|0x00010000;   // PLLCLK_SEL = 0, select 240M clock, F = 240/2(1+1) = 60Mhz

	UpdataPLLReg();                               // 更新PCVR
	Delay(500);
}



/*******************************************
*
*  选择外部80M时钟源
*
*******************************************/
void ExternalClk_80M()
{
//1.set clock mode 0,将开发板 CLKMODE pin脚跳 0,选择外部时钟源

//2.清除PHY_BIT_DIR控制位，由时钟模块寄存器控制PLL
CLEAR_PHY_BIT_DIR;

//3.PLL en
CLK_PCVR |=0x00200000;                        // PLLBI_RFG_PLLEN =1, pll enable     
     
//4.set PLLCLK_SEL 0,  PLL_DIV 2 
CLK_PCVR =(CLK_PCVR&0xfff0ffff)|0x00420000;   // PLLCLK_SEL = 0, select 480M clock, F = 480/2(2+1) = 80Mhz

UpdataPLLReg();                               // 更新PCVR
Delay(500);
}

/*******************************************
*
*  打开某个模块时钟
*                                         
#define     MODULE_CLK_USI1               0x00000001	//默认打开
#define     MODULE_CLK_SPI1               0x00000002	//默认打开
#define     MODULE_CLK_USBC               0x00000004	//默认打开
#define     MODULE_CLK_PIT1               0x00000008	//默认打开
#define     MODULE_CLK_WDT                0x00000010	//默认打开
#define     MODULE_CLK_EPORT              0x00000020	//默认打开
#define     MODULE_CLK_CRYPTO             0x00000040	//默认关闭
#define     MODULE_CLK_DES                0x00000080	//默认关闭
#define     MODULE_CLK_SM1                0x00000100	//默认关闭
#define     MODULE_CLK_TRNG               0x00000400	//默认关闭
#define     MODULE_CLK_PIT2               0x00000800	//默认关闭
#define     MODULE_CLK_SCI                0x00002000	//默认关闭
#define     MODULE_CLK_USI2               0x00004000	//默认打开
#define     MODULE_CLK_USI3               0x00008000	//默认打开
#define     MODULE_CLK_I2C                0x00010000	//默认打开
#define     MODULE_CLK_SSF33              0x00020000	//默认关闭
#define     MODULE_CLK_TC                 0x00040000	//默认打开
#define     MODULE_CLK_AES                0x00080000	//默认关闭
#define     MODULE_CLK_SHA1               0x00100000	//默认关闭
#define     MODULE_CLK_SPI2               0x01000000	//默认打开
#define     MODULE_CLK_SMS4               0x08000000	//默认打开

*******************************************/
void ModuleClk_On(UINT32 module)
{
	CLK_MSCR &= (~module);
}

/*******************************************
*
*  关闭某个模块时钟
*
*******************************************/
void ModuleClk_Off(UINT32 module)
{
	CLK_MSCR |= module;
}

/*******************************************
*
*  CLKOUT引脚输出系统时钟的开关，用于测试，默认打开
*  u8Switch: 1打开， 0关闭
*******************************************/
void ClkoutPin_switch(UINT8 u8Switch)
{
	if (u8Switch == 1)
	{
		CLK_MSCR |= (1<<25);
	}
	else if (u8Switch == 0)
	{
		CLK_MSCR &= ~(1<<25);
	}
}

/////////////////////////////////////////////


/**********************************************************************
*
*  系统时钟配置
*
**********************************************************************/
void SetClk()
{
    if(PHYPA&CLKMODE)
    {
        //internal Ring-Oscillator
        InternalClk_32M();
        g_sys_clk = EFLASH_SYS_CLK_32M;
    }
    else
    {
        //external oscillator
        //Set PLL
        ExternalClk_40M();
        g_sys_clk = EFLASH_SYS_CLK_40M;
    }
}
///////////////////////////////////////////////////////////////////////