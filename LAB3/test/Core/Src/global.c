/*
 * global.c
 *
 *  Created on: Oct 3, 2025
 *      Author: DELL
 */
#include "global.h"
int status1 = NORMAL;
int lastState1 = NORMAL;
int status2 = NORMAL;
int lastState2 = NORMAL;
int status3 = DELAY;

int red1_duration = 5000;
int yellow1_duration = 2000;
int green1_duration = 3000;

int red2_duration = 5000;
int yellow2_duration = 2000;
int green2_duration = 3000;

int time_input = 1;
int mode = 1;

int countdown1 = 0;
int countdown2 = 0;

int return_flag1 = 0;
int return_flag2 = 0;

void systemINIT(){
	setButton();
	GPIOB->ODR = 0xffff;
	setTimer0(100);
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);

	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, RESET);
	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, SET);
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, SET);
	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, SET);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, RESET);
}

