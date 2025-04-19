#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "list.h"
#include "cpu.h"

#define time_limit 10

struct node *task_list = NULL;

 // same as add function in fcfs, adds each task to a linked list
 void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));       
    newTask->name = name;                       
    newTask->priority = priority;               
    newTask->burst = burst;                     

    insert(&task_list, newTask);               
}

// Round Robin Scheduling
void schedule() {
    // the insert() function in list.c adds tasks to the front of the list, LIFO.
    // This while loop is the same used in FCFS to reverse the list (FIFO)
    struct node *reversed = NULL;
    struct node *curr = task_list;

    while (curr != NULL) {
        struct node *next = curr->next;
        curr->next = reversed;
        reversed = curr;
        curr = next;
    }

    // Round robin implementation
    while (reversed != NULL) {
        struct node *prev = NULL;
        struct node *temp = reversed;

        while (temp != NULL) {
            Task *t = temp->task; // get the current task from node
        
            int run_time; 
            if (t->burst > time_limit) { // if remaining burst time is more than the time limit (10), run only for allowed time limit
                run_time = time_limit;  
            } else {                    // else, run until task is complete (if burst < 10)
                run_time = t->burst;
            }
            run(t, run_time);
        
            // burst - time limit (10) 
            t->burst = t->burst - run_time;
            if (t->burst <= 0) { // this indicates that the task has been completed
                struct node *next_node = temp->next; // saves next node into temp before deleting
                delete(&reversed, t); // delete the node that is finished
                temp = next_node; 
                if (prev != NULL) { // checks if we are at the head of the list (the previous node would be null if we are at the head)
                    prev->next = temp; // prev node now points to temp, which was previously stored as the next node (line 55)
                } else { // if prev is null, then the head of the list was deleted, temp is now the new head of the list
                    reversed = temp;
                }
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
    }
}