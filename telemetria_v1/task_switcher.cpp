#include <Arduino.h>
#include "task_switcher.h"

#define READY 1
#define WAIT  0

TaskSwitcher::TaskSwitcher() : taskCount(0) {
}
    
// set up timer1 - 
// compare interrupt @ timerInterruptInuSecs microseconds
void TaskSwitcher::begin(long timerInterruptInuSecs) {
  noInterrupts();           // disable all interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // compare match register 16MHz/256 * t(s) - 1
  OCR1A = (16e6 / 256L * timerInterruptInuSecs) / 1e6 - 1;            

  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts
}

void TaskSwitcher::createTask(void (*t)(), long interval) {
  taskList[taskCount++] = {t, interval, 0, WAIT};
}
    
void TaskSwitcher::runCurrentTask() {
  int i;
  void (*task)();
  for (i=0; i<  taskCount; i++) {
    if (taskList[i].status == READY) {
      task = taskList[i].task;
      (*task)();
      noInterrupts();
      taskList[i].status = WAIT;
      taskList[i].current_time = 0;
      interrupts();
    } // if task is READY
  } //for each task
}
    
void TaskSwitcher::updateTickCounter() {
  int i;
  for (i=0; i< taskCount; i++) {
    if (taskList[i].status == WAIT) {
      taskList[i].current_time++;
      if (taskList[i].current_time >= taskList[i].interval) {
        taskList[i].status = READY;
      }
    } // if task is WAITing
  } // for each task
}

TaskSwitcher TaskController;

ISR(TIMER1_COMPA_vect) {
   TaskController.updateTickCounter();
}
