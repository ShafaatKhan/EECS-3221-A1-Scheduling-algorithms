#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

    if (head == NULL){
        head = newTaskNode;
    }

    else{
        struct node *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newTaskNode;
    }
}

void schedule(){

    struct node *temp = malloc(sizeof(struct node));
    temp = head;

    int quantum = 10;

    while (temp->task->burst != 0){

        while (temp != NULL){

            if (temp->task->burst > quantum){
                run(temp->task, quantum);
                temp->task->burst -= quantum;
            }

            else if (temp->task->burst > 0){
                run(temp->task, temp->task->burst);

                temp->task->burst = 0;
            }
            temp = temp->next;
        }
        temp = head;
    }
}