#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
/*
Add function simply adds the tasks from txt file into a linked list

Priority scheduling function uses linear search approach by first setting two pointers: highest and current
Initally, first node in the linked list is assigned highiest value. As the the "current" pointer iterates through the nodes,
it checks its own value with value stored in "highest", if it is current > highest, it will update highest the current value, if not,
continue iterating. 

*/
 // empty pointer, points to head of linked list of tasks
 struct node *task_list = NULL;
 
 // same as add function in fcfs, adds each task to a linked list
 void add(char *name, int priority, int burst) {
     Task *newTask = malloc(sizeof(Task));       // Allocate memory for a new Task
     newTask->name = name;                       
     newTask->priority = priority;               
     newTask->burst = burst;                     
 
     insert(&task_list, newTask);               
 }

// Priority Scheduling
void schedule() {
    while (task_list != NULL) {
        // Both start at the first node
        struct node *highest = task_list;   
        struct node *current = task_list;           

        while (current != NULL) { 
            Task *currTask = current->task; 
            Task *highTask = highest->task;

            if (currTask->priority > highTask->priority) {
                highest = current;               
            }
            current = current->next;                  
        }
        Task *t = highest->task;
        run(t, t->burst);                              
        delete(&task_list, t);                         
    }
}