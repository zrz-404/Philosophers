
/* 
	each philosopher is a thread
	threads in a multithreading process share the same base of knowledge
	this means all threads share the origin code, data, resources, etc

	the forks and food with be data that is centralized and shared by each thread of the process (which is the activity itself)
 	each thread can have a status assigned to it: in this case it will be eating, thinking or sleeping
*/


/*	Mutexes

	mutexes basically create mutual exclusion
	this means, that they "organize" two threads operating on the same data
	in the case of the philosophers, mutexes will be the thing telling each philosopher
	if forks are available to them or if they should sleep / think

	in C they are pretty straightforward to implement:


	#include <pthread.h>

	pthread_mutex_t my_mutex;

	int main(int argc, char **argv)
	{
		pthread_mutex_init(&my_mutex); 		-> mutex initialization
	}

	void critical_function()
	{
		pthread_mutex_lock(&my_mutex);
		...									-> how to lock / unlock mutexes
		pthread_mutex_unlock(&my_mutex);
	}

	unix threads in c -> https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
	
	intro to threads in c -> https://www.youtube.com/watch?v=ldJ8WGZVXZk

	oceano philosophers - > https://www.youtube.com/watch?v=zOpzGHwJ3MU

	https://en.wikipedia.org/wiki/Multithreading_(computer_architecture)

	https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2

	https://github.com/DeRuina/philosophers?source=post_page-----893a24bc0fe2--------------------------------


	Multi threaded programs can work concurrently (the cpu goes back and forward on the multiple threads) 
	or in parallel (the cpu processes all threads at the same time, without having to switch)
	this functionality depends not only on software, but mainly on the architecture of the cpu

	How to create threads?

 	--- parallel execution ---

	#include <pthread.h>

	pthread_create ---- creates the separate thread or function which gets run in parallel

	to then rejoin this thread to the main process, we must use pthread_join
	
	if the parallel thread is not finished yet by the time pthread_join runs,
	execution pauses here until the thread is done with its execution.

	threads with  code: https://www.youtube.com/watch?v=ldJ8WGZVXZk



*/