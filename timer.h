// Tyler Cole
// EVO Project Module Header
// timer.h

// Credit:  Kenneth Wilder, University of Chicago, Department of Statistics

#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>

class timer
{
 friend std::ostream& operator<<(std::ostream& os, timer& t);

 private:
  int running;
  clock_t start_clock;
  time_t start_time;
  double acc_time;

 public:
  // 'running' is initially 0.  A timer needs to be explicitly started
  // using 'start' or 'restart'
  timer() : running(0), start_clock(0), start_time(0), acc_time(0) { }

  void start(const char* msg = 0);
  void restart(const char* msg = 0);
  void stop(const char* msg = 0);
  void check(const char* msg = 0);
  double elapsed_time();

}; // class timer

#endif
// end of file
