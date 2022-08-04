# LCD1620-Driver
## Overview
for HD44780 1602 display module
work well on STM32Cube IDE

## Set up
open .ioc file in your project and configure Gpio as follow
![1](https://user-images.githubusercontent.com/80786844/182936694-ab9b7657-0388-4673-b586-c437781d8297.png)

in main.c and add following lines between USER CODE 2

>  /* USER CODE BEGIN 2 */
```
extern void runLcdTest();
runLcdTest();
```
>  /* USER CODE END 2 */
######
it may has some problem with undefined header. 
Using relative path should solves the problem.  
Or put all the .cpp in Src-folder and .h files in Inc-folder.
