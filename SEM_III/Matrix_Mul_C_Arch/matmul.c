/*
 * Program: Speedup calculation of matrix multiplication with
 *          multi-processing and multi-threading.
 * Author:  Shreyas Jayant Havaldar
 * Roll# :  CS18BTECH11042
 */

#include <stdlib.h> /* for exit, atoi */
#include <stdio.h>  /* for fprintf */
#include <errno.h>  /* for error code eg. E2BIG */
#include <getopt.h> /* for getopt */
#include <assert.h> /* for assert */
#include <pthread.h> /* Using pthreads to create threads */
#include <sys/shm.h> /* For creating and using shared memory */
#include <sys/ipc.h> /* For inter process communication*/
#include <sys/wait.h> // For making the parent process wait until all child processes have computed
#include <unistd.h>
#include <sys/sysinfo.h> // For getting no of cores
#include <semaphore.h> // Using library to be able to use semaphores to avoid synchronization issues
#include <math.h> // For square root operation




#define f(i,j,k) for(int i=j; i<k; i++)
#define ll long long int

/*
 * Forward declarations
 */
void usage(int argc, char *argv[]);
void input_matrix(int *mat, int nrows, int ncols);
void output_matrix(int *mat, int nrows, int ncols);


int *A, *B, *C;
int crows, ccols;
int arows, acols, brows, bcols;
char interactive = 0;
ll start;
ll end;
int nrt; // No of threads to divide the rows of A in
int nct; // No of threads to divide the columns of B in
int npros; // No of processors on the machine the code will execute on
sem_t mutex; // Mutual exclusion variable which represents locking and unlocking access provided to different threads
sem_t tc; // To make worker threads wait until all threads are created
int t_count; // Maintains the no of threads active currently


static long getNanos (void) // Function to calculate timestamp in nanoseconds
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

void init_matrix() // Initializing matrices A and B with random values
{	

	f(i, 0, arows) {
		f(j, 0, acols) {
			A[i*acols + j] = rand(); // A in row major format
		}
	}
	f(i, 0, brows) {
		f(j, 0, bcols) {
			B[i*bcols + j] = rand(); // B in row major format
		}
	}

}

void* matrix_multi_t(void* a) 
{	
	sem_wait(&mutex); // Critical section
	t_count++;
	if(t_count == 1) {
		sem_wait(&tc);
	}
	sem_post(&mutex);

	int index = *((int *)a) ; 
	int m=0; int n=0; // Tiling is achived by assigning start indices and end indices for loop variable i and j to run concurrently on respective tiles on each individual thread.
	m = index / nct;
	n = index % nct;


	int mina = (m)*arows/nrt < arows-1 ? (m)*arows/nrt: arows-1; // Start indices
	int minb = (n)*bcols/nct < bcols-1 ? (n)*bcols/nct: bcols-1; 

	int maxa = (m+1)*arows/nrt < arows ? (m+1)*arows/nrt: arows; // End indices
	int maxb = (n+1)*bcols/nct < bcols ? (n+1)*bcols/nct: bcols;

	f(i,mina, maxa) {
		f(j,minb, maxb) {
			C[i*bcols + j] = 0;
			f(k,0,acols) {
				C[i*bcols + j] += A[i*acols + k] * B[k*bcols + j];
			}

		}
	}

	sem_wait(&mutex); // Critical section
	t_count--;
	if (t_count == 0) {
		sem_post(&tc);
	}
	sem_post(&mutex);
}

void matrix_multi_p(int index) 
{	
	int m=0; int n=0;  // Tiling is achived by assigning start indices and end indices for loop variable i and j to run concurrently on respective tiles on each individual process.
	m = index / nct;
	n = index % nct;


	int mina = (m)*arows/nrt < arows-1 ? (m)*arows/nrt: arows-1; // Start indices
	int minb = (n)*bcols/nct < bcols-1 ? (n)*bcols/nct: bcols-1;

	int maxa = (m+1)*arows/nrt < arows ? (m+1)*arows/nrt: arows; // End indices
	int maxb = (n+1)*bcols/nct < bcols ? (n+1)*bcols/nct: bcols;

	f(i,mina, maxa) {
		f(j,minb, maxb) {
			C[i*bcols + j] = 0;
			f(k,0,acols) {
				C[i*bcols + j] += A[i*acols + k] * B[k*bcols + j];
			}

		}
	}
}

int single_thread_mm()
{	
	
	A = (int*)malloc(arows*acols*(sizeof(int))); // Memory allocation in the heap
	B = (int*)malloc(brows*bcols*(sizeof(int)));
	C = (int*)malloc(arows*bcols*(sizeof(int)));

	if (interactive) { // Checking if --interactive argument is true and proceeding accordingly
        fprintf(stdout, "Enter A:\n");
		input_matrix(A, arows, acols);
		fprintf(stdout, "Enter B:\n");
		input_matrix(B, brows, bcols);
	} else {
		init_matrix(A, arows, acols);
		init_matrix(B, brows, bcols);
	}

	start = getNanos();  // The start time is maintained in this variable

	f(i,0,arows) {
		f(j,0,bcols) {
			C[i*bcols + j] = 0;
			f(k,0,acols) {
				C[i*bcols + j] += A[i*acols + k] * B[k*bcols + j];

			}

		}
	}

	end = getNanos(); // The time at the end of computation is maintained here
    ll timeTaken = (end - start); // The time taken in computation is thus calculated

	if(interactive) { // Checking if --interactive argument is true and proceeding accordingly
		fprintf(stdout, "Result:\n");
		output_matrix(C, arows, bcols);
	}

	return timeTaken/1000.0;
}

int multi_thread_mm()
{	
	
	A = (int*)malloc(arows*acols*(sizeof(int))); // Memory allocation in the heap
	B = (int*)malloc(brows*bcols*(sizeof(int)));
	C = (int*)malloc(arows*bcols*(sizeof(int)));

	if (interactive) { // Checking if --interactive argument is true and proceeding accordingly
        fprintf(stdout, "Enter A:\n");
		input_matrix(A, arows, acols);
		fprintf(stdout, "Enter B:\n");
		input_matrix(B, brows, bcols);
	} else {
		init_matrix(A, arows, acols);
		init_matrix(B, brows, bcols);
	}

	int tid[nrt*nct]; // Stores thread nos

	f(i,0,nrt*nct) { 
		tid[i] = i;
	}

	pthread_t threads[nrt*nct]; // Creating threads
	
	sem_wait(&tc); // Making worker threads wait until all are created
	f(i,0,nrt*nct) {
		pthread_create(&threads[i], NULL, matrix_multi_t, (void*)&tid[i]);
	}
	sem_post(&tc);

	start = getNanos();  // The start time is maintained in this variable

	f(i,0,nrt*nct) {
		pthread_join(threads[i], NULL); // Joining the threads
	}
	
	end = getNanos(); // The time at the end of computation is maintained here
    ll timeTaken = (end - start); // The time taken in computation is thus calculated

	if(interactive) { // Checking if --interactive argument is true and proceeding accordingly
		fprintf(stdout, "Result:\n");
		output_matrix(C, arows, bcols);
	}

	return timeTaken/1000.0;
}

int multi_process_mm()
{	
	ll timeTaken;
	int status;
	int shmid[3];
	shmid[0] = shmget(IPC_PRIVATE, arows*acols*sizeof(int), 0777 | IPC_CREAT); // Creation of shared memory
	shmid[1] = shmget(IPC_PRIVATE, brows*bcols*sizeof(int), 0777 | IPC_CREAT);
	shmid[2] = shmget(IPC_PRIVATE, arows*bcols*sizeof(int), 0777 | IPC_CREAT);

	A = (int*)shmat(shmid[0],0,0); // Attaching to shared memory
	B = (int*)shmat(shmid[1],0,0);
	C = (int*)shmat(shmid[2],0,0);


	if (interactive) { // Checking if --interactive argument is true and proceeding accordingly
        fprintf(stdout, "Enter A:\n");
		input_matrix(A, arows, acols);
		fprintf(stdout, "Enter B:\n");
		input_matrix(B, brows, bcols);
	} else {
		init_matrix(A, arows, acols);
		init_matrix(B, brows, bcols);
	}
		
	start = getNanos();  // The start time is maintained in this variable
	f(i,0,nrt*nct) {

		fflush(stdout);

		if(fork()==0) { // Forking off child processes

			matrix_multi_p(i); // Calling the computation function passing the child process no
			exit(0);
		}
	}

	f(i,0,nrt*nct) {
		wait(NULL); // To wait for all child processes to exit
	}

	end = getNanos(); // The time at the end of computation is maintained here
	timeTaken = (end - start); // The time taken in computation is thus calculated	

	if(interactive) { // Checking if --interactive argument is true and proceeding accordingly
		fprintf(stdout, "Result:\n");
		output_matrix(C, arows, bcols);
	}

	return timeTaken/1000.0;

}

int main(int argc, char *argv[])
{

	int c;


	/* Loop through each option (and its's arguments) and populate variables */
	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"help",	no_argument,		0, 'h'},
			{"ar",		required_argument,	0, '1'},
			{"ac",		required_argument,	0, '2'},
			{"br",		required_argument,	0, '3'},
			{"bc",		required_argument,	0, '4'},
			{"interactive",	no_argument, 		0, '5'},
			{0,		0,			0,  0 }
		};

		c = getopt_long(argc, argv, "h1:2:3:4:5", long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			fprintf(stdout, "option %s", long_options[option_index].name);
			if (optarg)
				fprintf(stdout, " with arg %s", optarg);
				fprintf(stdout, "\n");
			break;

		case '1':
			arows = atoi(optarg);
			break;

		case '2':
			acols = atoi(optarg);
			break;

		case '3':
			brows = atoi(optarg);
			break;

		case '4':
			bcols = atoi(optarg);
			break;

		case '5':
			interactive = 1;
			break;

		case 'h':
		case '?':
			usage(argc, argv);

		default:
			fprintf(stdout, "?? getopt returned character code 0%o ??\n", c);
			usage(argc, argv);
		}
	}

	if (optind != argc) {
		fprintf(stderr, "Unexpected arguments\n");
		usage(argc, argv);
	}

	if (acols != brows) { // Checking if matrix multiplication is indeed possible
		
		fprintf(stderr, "Matrix multiplication not possible\n");		
		exit(EXIT_FAILURE);

	}

	npros = get_nprocs(); // Getting the no of of total processor threads that can be executed on the machine for maximum speedup during computation

	nrt = (int)sqrt(npros-1); 
	nct = (int)sqrt(npros-1);

	nrt = nrt > arows ? arows: nrt;
	nct = nct > bcols ? bcols: nct;


    sem_init(&tc, 0, 1); // Initializing both semaphores to 1
    sem_init(&mutex, 0, 1); 

	unsigned long long time_single, time_multi_process, time_multi_thread;
	time_single = single_thread_mm();

	time_multi_thread = multi_thread_mm();

	time_multi_process = multi_process_mm();


	fprintf(stdout, "Time taken for single threaded: %llu us\n",
			time_single);
	fprintf(stdout, "Time taken for multi process: %llu us\n",
			time_multi_process);
	fprintf(stdout, "Time taken for multi threaded: %llu us\n",
			time_multi_thread);
	fprintf(stdout, "Speedup for multi process : %4.2f x\n",
			(double)time_single/time_multi_process);
	fprintf(stdout, "Speedup for multi threaded : %4.2f x\n",
			(double)time_single/time_multi_thread);

	exit(EXIT_SUCCESS);
}

/*
 * Show usage of the program
 */
void usage(int argc, char *argv[])
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s --ar <rows_in_A>  --ac <cols_in_A>"
			" --br <rows_in_B>  --bc <cols_in_B>"
			" [--interactive]",
			argv[0]);
	exit(EXIT_FAILURE);
}

/*
 * Input a given 2D matrix
 */
void input_matrix(int *mat, int rows, int cols)
{	
	int inp=0;
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			inp = fscanf(stdin, "%d", mat+(i*cols+j));
		}
	}
}

/*
 * Output a given 2D matrix
 */
void output_matrix(int *mat, int rows, int cols)
{
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			fprintf(stdout, "%d ", *(mat+(i*cols+j)));
		}
		fprintf(stdout, "\n");
	}
}



