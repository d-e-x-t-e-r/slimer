## Slimer.txt README

Slimer (sleep and timer) provides the sleep, msleep, and usleep functions to Lua
as a C extension. It also provides a high resolution (<1us) clock that can be
used for timing purposes. It is currently supported on Windows only.

MODULE FUNCTIONS:

slimer.sleep(s) - Sleeps for "s" seconds.

slimer.msleep(ms) - Sleeps for "ms" milliseconds.

slimer.usleep(us) - Sleeps for "us" microseconds.

slimer.frequency() - Queries the frequency of the PerformanceCounter

slimer.clock() - Queries the current count of the PerformanceCounter

slimer.period() - Returns a double indicating the period of the
                  PerformanceCounter


SLEEP FUNCTIONS:

Slimer uses the Windows "Sleep" function for the sleep and msleep functions.
For the usleep function, Slimer uses a waitable timer with a precision of
100 nanoseconds. See the MSDN documentation for more details.


PERFORMANCE COUNTER FUNCTIONS:

Slimer queries the PerformanceCounter to get a precise measurement of system
time. Frequency measures the literal frequency of the counter. 1 / frequency is
equal to the period of the counter. The period is a measurement of the precision
of your counter. For example, a period of 300 nanoseconds indicates that you can
query measurements at an interval of 300 nanoseconds at best. Of course, in
practice you will never reach this number as calling the function itself will
take longer than that. For most purposes this level of precision will serve well
enough to time applications of Lua code. See the MSDN documentation for more
details.


NOTES:

As with any sleep function, the total time slept will always be the sleep time
<i>plus the time it takes to call the function</i>. If you need to sleep for a precise
amount of time, you can calibrate the sleep functions to work correctly by
using this formula:
  NEEDED SLEEP TIME - TIME TO EXECUTE CODE - TIME TO CALL FUNCTION = ACTUAL TIME YOU SHOULD SLEEP

The _WINDLL preprocessor definition must be defined when compiled your DLL
(Visual Studio does this for you automatically).

