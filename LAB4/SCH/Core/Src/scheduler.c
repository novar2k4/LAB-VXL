/*
 * scheduler.c
 *
 *  Created on: Oct 27, 2025
 *      Author: admin
 */

#include "scheduler.h"
sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void){
	for (uint32_t i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
}

#define tick 10
void SCH_Add_Task ( void ( * pFunction ) ( ) , uint32_t DELAY, uint32_t PERIOD){
	while ((SCH_tasks_G[current_index_task].pTask!= 0) && (current_index_task < SCH_MAX_TASKS)) {
		current_index_task++;
	}
	if(current_index_task < SCH_MAX_TASKS){

		SCH_tasks_G [ current_index_task ].pTask  = 	pFunction ;
		SCH_tasks_G [ current_index_task ].Delay  = 	DELAY/tick;
		SCH_tasks_G [ current_index_task ].Period = 	PERIOD/tick;
		SCH_tasks_G [ current_index_task ].RunMe  = 	0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update (void){
	for(int i = 0; i < current_index_task; i++){
		if (SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay --;
		}else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}

void SCH_Dispatch_Tasks (void){
	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe --;
			(*SCH_tasks_G[i].pTask)();
			if (SCH_tasks_G[i].Period == 0) {
				SCH_Delete_Task(i);
			}
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t taskID) {
    if (taskID >= SCH_MAX_TASKS) {
        return 1;
    }

    SCH_tasks_G[current_index_task].pTask = 0x0000;
    SCH_tasks_G[current_index_task].Delay = 0;
    SCH_tasks_G[current_index_task].Period = 0;
    SCH_tasks_G[current_index_task].RunMe = 0;

    return 0;
}

