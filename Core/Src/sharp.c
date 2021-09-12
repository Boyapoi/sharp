#include "sharp.h"
#include "adc.h"
#include "main.h"


//初始化ADC,不用修改
//这里我们仅以规则通道为例														   
		  
//初始化传感器，需要修改端口和引脚号，这里是c出口，c1引脚，ADC3的IN11
void ShuiWeiSensor_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  __HAL_RCC_GPIOA_CLK_ENABLE();//使能GPIOA时钟
	
  //先初始化ADC1通道11 IO口
  GPIO_InitStructure.Pin = GPIO_PIN_1;//PA1
  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;//模拟输入
  GPIO_InitStructure.Pull = GPIO_NOPULL ;//不带上下拉
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  
	
 
	MX_ADC1_Init();//初始化ADC1
}
//Pc1=IN11，需要修改，15通道
float ShuiWeiSensor_Get_Val(void)
{
	uint32_t temp_val=0;
	float distemp=0.0;
	uint8_t t;
	for(t=0;t<Adc1IN11SHUIWEI_READ_TIMES;t++)
	{
		temp_val+=HAL_ADC_GetValue(&hadc1);	//读取ADC值,通道1
		HAL_Delay(5);
	}
	temp_val/=Adc1IN11SHUIWEI_READ_TIMES;//得到平均值,这个是平均的ADC，
	printf("average_val=%d\r\n",temp_val);
	distemp=temp_val*3.3/4095;
	printf("****voltage= %f\r\n",distemp);//电压值
	//电压对应距离
	distemp=(-13.2*distemp*distemp*distemp)+72.84*distemp*distemp-140*distemp+107.12;
  return distemp;
//	if(temp_val>4000)temp_val=4000;
//	//简单量化后，处理成 0~100 的光强值。0 对应最暗，100 对应最亮
//	return (uint8_t)(100-(temp_val/40));
}

