#ifndef __SHARP2Y0A21_H
#define __SHARP2Y0A21_H	

#include "main.h"


#define Adc1IN11SHUIWEI_READ_TIMES	10		//定义光敏传感器读取次数,读这么多次,然后取平均值
 
void ShuiWeiSensor_Init(void); 				//初始化光敏传感器
float ShuiWeiSensor_Get_Val(void);				//读取光敏传感器的值


#endif 

