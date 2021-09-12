#include "sharp.h"
#include "adc.h"
#include "main.h"


//��ʼ��ADC,�����޸�
//�������ǽ��Թ���ͨ��Ϊ��														   
		  
//��ʼ������������Ҫ�޸Ķ˿ں����źţ�������c���ڣ�c1���ţ�ADC3��IN11
void ShuiWeiSensor_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  __HAL_RCC_GPIOA_CLK_ENABLE();//ʹ��GPIOAʱ��
	
  //�ȳ�ʼ��ADC1ͨ��11 IO��
  GPIO_InitStructure.Pin = GPIO_PIN_1;//PA1
  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;//ģ������
  GPIO_InitStructure.Pull = GPIO_NOPULL ;//����������
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��  
	
 
	MX_ADC1_Init();//��ʼ��ADC1
}
//Pc1=IN11����Ҫ�޸ģ�15ͨ��
float ShuiWeiSensor_Get_Val(void)
{
	uint32_t temp_val=0;
	float distemp=0.0;
	uint8_t t;
	for(t=0;t<Adc1IN11SHUIWEI_READ_TIMES;t++)
	{
		temp_val+=HAL_ADC_GetValue(&hadc1);	//��ȡADCֵ,ͨ��1
		HAL_Delay(5);
	}
	temp_val/=Adc1IN11SHUIWEI_READ_TIMES;//�õ�ƽ��ֵ,�����ƽ����ADC��
	printf("average_val=%d\r\n",temp_val);
	distemp=temp_val*3.3/4095;
	printf("****voltage= %f\r\n",distemp);//��ѹֵ
	//��ѹ��Ӧ����
	distemp=(-13.2*distemp*distemp*distemp)+72.84*distemp*distemp-140*distemp+107.12;
  return distemp;
//	if(temp_val>4000)temp_val=4000;
//	//�������󣬴���� 0~100 �Ĺ�ǿֵ��0 ��Ӧ���100 ��Ӧ����
//	return (uint8_t)(100-(temp_val/40));
}

