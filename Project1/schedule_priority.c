#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "schedulers.h"
#include "cpu.h"
#include "task.h"

void run(Task *task, int slice);

struct node *head;

void add(char *name, int priority, int burst){

    struct node *newTaskNode = malloc(sizeof(struct node));
    newTaskNode->task = malloc(sizeof(struct task));

    newTaskNode->task->name = name;
    newTaskNode->task->priority = priority;
    newTaskNode->task->burst = burst;
    
    if(head == NULL){
        head = newTaskNode;
    }

    else{
        struct node *temp = head;

        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newTaskNode; 
    }
}

void schedule() {

    struct node *temp = malloc(sizeof(struct node));
    struct node *temp2 = malloc(sizeof(struct node));
    struct node *node = malloc(sizeof(struct node));
    node = head;

    while(node != NULL) {
        
        temp = head; 

        while (temp->next != NULL) {

           if(temp->task->priority < temp->next->task->priority){
            temp2->task = temp->task;
            temp->task = temp->next->task;
            temp->next->task = temp2->task;
            }
        temp = temp->next;
        }
        node = node->next;
    }

    float waitingTime = 0;
    float turnAroundTime = 0;
    float completionTime = 0;
    float numberOfProcesses = 0;
    float burstSum = 0;
    float responseTime = 0;

    temp = head;
    
    while (temp != NULL) {

        //this prints list of processes
        run(temp->task, temp->task->burst);
        
        completionTime += temp->task->burst;
        turnAroundTime += completionTime;
        waitingTime += burstSum;
        responseTime += burstSum;
        
        burstSum += temp->task->burst;
        
	    numberOfProcesses++;
        temp = temp->next;
    }

    float averageWaitingTime = waitingTime/numberOfProcesses;
    float averageTurnAroundTime = turnAroundTime/numberOfProcesses;
    float averageResponseTime = responseTime/numberOfProcesses;

    printf("\nAverage waiting time = %.2f", averageWaitingTime);
    printf("\nAverage turnaround time = %.2f", averageTurnAroundTime);
    printf("\nAverage response time = %.2f\n", averageResponseTime);
}