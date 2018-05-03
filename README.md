# Example1_C_synchronization

Simple illustration of sychronization in POSIX threads using POSIX semaphores, mutex

-Check program modifying NUMTHREADS, NUM macros and recompiling
-NUMTHREADS = number of threads, NUM = number of times/cycles each thread (needs to access critical path) prints its number. 
-Debug build available as make DEBUG=1

Brief description:
-Each thread is supposed to print its number sequentially, starting from thread 0, thread 1, thread 2 ... till NUMTHREADS-1.
 This printing happens for NUM number of times
-There is a syncvar global variable which is mutually exclusively accessed and whose access/update is critical path, 
 and synchronized using pthread_mutex. Threads cooperate using semaphore of size NUMTHREADS.
-Scheduling of threads is not in scope of this program and the program works (supposed to) irrespective of scheduler used 
  in any general OS/scenarios. Scheduling api/pthread schedule apis are not used.
-Sample output: (NUMTHREADS =4, NUM =3)

i= 0,thread num 0
i= 0,thread num 1
i= 0,thread num 2
i= 0,thread num 3
i= 1,thread num 0
i= 1,thread num 1
i= 1,thread num 2
i= 1,thread num 3
i= 2,thread num 0
i= 2,thread num 1
i= 2,thread num 2
i= 2,thread num 3



