/*
   Description
      .
   Compile
      $ gcc -o time_v1 time_v1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

float measure1(void (*func)());
float measure2(void (*func)());
void execute(void);

int main()
{
  float time;

    time = measure2(execute);
    printf("Time elapsed: %lf mili\n", time); 

    time = measure1(execute);
    printf("Time elapsed: %.4f sec\n", time); 
	return 0;
}

/*
   picosecond	10−12 s
   nanosecond	10−9  s	
   microsecond	10−6  s	Symbol is µs
   millisecond	10−3  s
*/

float measure2( void (*func)())
{
  clock_t start, end;
  unsigned long micros = 0;
  float millis = 0;
  float seconds = 0;

    start = clock();
    func();
    end = clock();
    micros = end - start;
    millis  = (float)micros / 1000;
    seconds = (float)micros / 1000000; // CLOCKS_PER_SEC
    printf("M2: %d %d %d %f %f\n", start, end, micros, millis, seconds); 
    return seconds;
}

/*
   CLOCK_REALTIME
   CLOCK_MONOTONIC
   CLOCK_PROCESS_CPUTIME_ID  Tiempos efectivos de kernel
   CLOCK_THREAD_CPUTIME_ID
*/
float measure1( void (*func)())
{
  struct timespec start, end, time;

    clock_gettime(CLOCK_REALTIME, &start);
    func();
	clock_gettime(CLOCK_REALTIME, &end);
    //float result = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;    // in microseconds
    float sec = (end.tv_sec - start.tv_sec);
    float nano = (end.tv_nsec - start.tv_nsec);
    float aux = sec + (nano / 1e9);
    //printf("M1 start: %lld sec %ld nano\n", (long long) start.tv_sec, start.tv_nsec);
    //printf("M1 end: %lld sec %ld nano\n", (long long) end.tv_sec, end.tv_nsec);
    //printf("M1 dif: %lf sec \n", sec); 
    //printf("M1 dif: %lf nano\n", nano); 
    //printf("M1 sec_nano %lf \n", aux); 

    return aux;
}

void execute(void)
{
    sleep(2);
	//usleep(5);
}
