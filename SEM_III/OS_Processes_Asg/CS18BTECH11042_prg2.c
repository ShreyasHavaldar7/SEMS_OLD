#define _GNU_SOURCE
#include <sys/utsname.h>
#include <unistd.h> 
#include <sys/syscall.h> 
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#define SIGINT 2
#define SIGKILL 9
#define TIME_UTC 1

long start;
long end;
//Using linux kernel style indentation


static long 
getNanos (void) // Function to calculate timestamp in nanoseconds
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

void 
sigPass (int sigid) // Function invoked when the signal was successfully passed and context switch was complete
{
    if (sigid == SIGINT) {
        end = getNanos(); // The time at the end of context switch is maintained here
        long timeTaken = (end - start); // The time taken in context switch is thus calculated
        printf("Time taken in nanoseconds: %ld || ", timeTaken);
        printf("Context switch complete \n");
    }

return;
}
void 
runner (int i) // The function which forks off a process and brings about context switching between the child and parent
{ 
    pid_t pid, ppid;                    
    ppid = getpid();
    struct sigaction sig;               
    sigemptyset(&sig.sa_mask);          
    sig.sa_flags = 0;                   
       
    
    printf("Context Switch no: %d || ", i+1); // Keeps track of the context switch no
    pid=fork(); 
    start = getNanos();  // The start time is maintained in this variable            

    if (pid  < 0) { 
        perror("fork"); 
        exit(1); 
    } else if (pid == 0) { //Child    
            kill(ppid, SIGINT); // Passes signal to parent process
                         
    } else {  // Parent                             
            signal(SIGINT,sigPass);
            sleep(1); // Necessary to ensure child process has completed execution
            kill(pid, SIGKILL); // Kills the child process
    }
}

void 
info () // Function to print all the info as asked for in the question. Functions snippets used are from various online sources
{

    struct utsname unamePointer;
    char buffer[500], c;

    uname(&unamePointer);

    printf(" OS Type        : %s \n", unamePointer.sysname); // OS Type
    printf(" OS Release     : %s \n", unamePointer.release); // OS Release Name
    printf(" OS Version     : %s \n", unamePointer.version); // OS Version

    FILE *cpuinfo = fopen("/proc/cpuinfo", "r"); // Storing the file data in cpuinfo
    char *arg = 0; 
    char line[256]; 
    int count=0; 
    size_t size = 0;
    while (fgets(line, sizeof line, cpuinfo) != NULL) {   
        if (count == 4) { // Line 4 of cpuinfo contains the CPU model name and the speed
        printf(" CPU %s ", line);
        }  
        if (count == 8) { // Line 8 of the cpuinfo contains the Cache Size
        printf("CPU %s", line);
        }           
        count++;
            
    }
   fclose(cpuinfo);
   FILE *meminfo = fopen("/proc/meminfo", "r"); // Storing the file data in Meminfo
    double totalMemory = 0;

    char buff[256];
    while(fgets(buff, sizeof(buff), meminfo)) {
    
        int ramKB;
        if(sscanf(buff, "MemTotal: %d kB", &ramKB) == 1) {
        
            totalMemory = ramKB/1024.0; // Converting to MB
            totalMemory = totalMemory/1024.0; // Converting to GB
        }
    }
    fclose(meminfo);
    printf(" RAM Size in GB : %f\n", totalMemory); // Contains the RAM size

}

int 
main ()
{   
    for(int i=0; i<20; i++) { // Running the loop 20 times to perform 20 context switches
    runner(i); // Calling the function to perform context switch
    }
    sleep(5); // Sleeping for a while to ensure the context switches have all been completed
    printf("Printing System Details: \n");
    info(); // Calling function to print the required info

    return 0;

}
