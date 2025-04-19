/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 #include "task.h"
 #include "list.h"
 #include "schedulers.h"
 
 #define SIZE    100

 int main(int argc, char *argv[])
 {
     FILE *in;
     char *temp;
     char task[SIZE];
 
     char *name;
     int priority;
     int burst;
 
     in = fopen(argv[1],"r");
     /* 
     NOTES:
        - strsep() was replaced with strtok(), strep() is only compatiable with linux/mac.  
        - Output showed garbage characters: Running task = [P→¿Σµ☺] [4] [20] for 20 units.
        - Fixed by adding 
     */  
     while (fgets(task, SIZE, in) != NULL) { // reads one line at a time from file in, stores it in task, return null when finished
      temp = strdup(task); // creates a copy of task (i.e. T1, 4, 20) and stores it in temp
      char *parsedName = strtok(temp, ","); // splits temp by the first comma (T1), returns it pointer.  
      priority = atoi(strtok(NULL, ","));  // continue to next string (4) note: atoi = ASCII to int
      burst = atoi(strtok(NULL, ",")); // gets next string (20)
      name = strdup(parsedName); // store parsed name into variable name
      
      add(name, priority, burst);
      
      free(temp);  
      
  }
 
     fclose(in);
 
     // invoke the scheduler
     schedule();
 
     return 0;
 }

// Given Code **Origional**
/*
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

        free(temp);
    } 

*/