// Tyler Cole
// EVO Project Module Implementation
// timer.cpp

// Credit:  Kenneth Wilder, University of Chicago, Department of Statistics

#include <ctime>
#include <iostream>
#include <iomanip>
#include "timer.h"

// __________________________________________________________________________
// Return the time that has passed since the timer was started.  If the
// total time is less than a minute, the time is reported to two decimal
// places.

double timer::elapsed_time()
{
  time_t acc_sec = time(0) - start_time;
  if (acc_sec < 60)
    return (clock() - start_clock) / (1.0 * CLOCKS_PER_SEC);
  else
    return acc_sec;

} // timer::elapsed_time

// __________________________________________________________________________
// Start a timer.  If it is already running, let it continue running.
// Print an optional message.

void timer::start(const char* msg)
{
  // Report the timer message
  if (msg)
    std::cout << msg << std::endl;

  // Return immediately if the timer is already running
  if (running)
    return;

  // Change timer status to running
  running = 1;

  // Set the start time;
  start_clock = clock();
  start_time = time(0);

} // timer::start

// __________________________________________________________________________
// Turn the timer off and start it again from 0.  Print an optional message.

void timer::restart(const char* msg)
{
  // Report the timer message
  if (msg)
    std::cout << msg << std::endl;

  // Set the timer status to running
  running = 1;

  // Set the accumulated time to 0 and the start time to now
  acc_time = 0;
  start_clock = clock();
  start_time = time(0);

} // timer::restart

// __________________________________________________________________________
// Stop the timer and print an optional message.

void timer::stop(const char* msg)
{
  // Report the timer message
  if (msg)
    std::cout << msg << std::endl;

  // Recalculate and store the total accumulated time up until now
  if (running)
    acc_time += elapsed_time();

  running = 0;

} // timer::stop

// __________________________________________________________________________
// Print out an optional message followed by the current timer timing.

void timer::check(const char* msg)
{
  // Report the timer message
  if (msg)
    std::cout << msg << " : ";

  std::cout << "Elapsed time [" << std::setiosflags(std::ios::fixed)
            << std::setprecision(2)
            << acc_time + (running ? elapsed_time() : 0)
            << "] seconds\n";

} // timer::check

// __________________________________________________________________________
// Allow timers to be printed to ostreams using the syntax 'os << t'
// for an ostream 'os' and a timer 't'.

std::ostream& operator<<(std::ostream& os, timer& t)
{
  os << std::setprecision(2) << std::setiosflags(std::ios::fixed)
    << t.acc_time + (t.running ? t.elapsed_time() : 0);
  return os;
}

// end of file
