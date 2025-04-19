/**
 * FCFS scheduling
 */

 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 
 #include "task.h"
 #include "list.h"
 #include "cpu.h"
 /*
 Add function simply adds the tasks from txt file into a linked list. However, new strings are added to
 the front of the list. For example if we're adding to task_list: add(t1), add(t2), add(t3), task_list = t3, t2, t1. 
 In FCFS, we need to make sure that the first task that arrived is ran first, if we run the list as is then the LAST task 
 that arrived ends up running first 

 To fix this, schedule function needs to reverse the order of the linked list then run the tasks. 
 */
 // empty pointer, points to head of linked list of tasks
 struct node *task_list = NULL;
 
 // adds task to the linked list frpm driver.c
 void add(char *name, int priority, int burst) {
     Task *newTask = malloc(sizeof(Task));       // Allocate memory for a new Task
     newTask->name = name;                       
     newTask->priority = priority;               
     newTask->burst = burst;                     
 
     insert(&task_list, newTask);               
 }
 
// FCFS scheduling
 void schedule() {
     struct node *reversed = NULL; // pointer for reversed list (needed because FCFS uses FIFO)
     struct node *curr = task_list;  // pointer for the head of the linked list
 
     // revereses the linked list  
     while (curr != NULL) { //  
         struct node *next = curr->next; //save the contents of the next node (this is so we dont lose track of the order)
         curr->next = reversed; // current node to front of reversed list
         reversed = curr; 
         curr = next;                           
     }
     // outputs the reversed linked list
     // Ex: T1, 4, 20
     int current_time = 0;
     struct node *temp = reversed; // points to the head of the reversed list
     while (temp != NULL) {
        Task *t = temp->task; // get task in current noder
        int burst = t->burst; // points to burst "20"
        run(t, burst);
        
        current_time += burst;
         temp = temp->next;   // moves to next task in list                   
     }
 }