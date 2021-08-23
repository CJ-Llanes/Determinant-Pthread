#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

// number of threads
#define MAX_THREAD 4

#define size 20

float matA[size][size];
int step_i = 0;
float det;
int pivot,n ;

void* create(void* arg);
void* Det(void* arg);
void exceptions();

int main()
{

// definition of threads with the amount of threads
pthread_t threads[MAX_THREAD];


printf("Introduce the size of the matrix:(less than 20) ");
scanf("%d",&n);
printf("\n");


    for (int i = 0; i < MAX_THREAD; i++) {
		int* p;

		pthread_create(&threads[i], NULL, create, (void*)(p));
	}
    // joining and waiting for all threads to complete
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);


    printf("\nMatrix\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
            printf("%.0f ",matA[i][j]);
		printf("\n");
	}



    if (n == 1 || n ==2)
        exceptions();
    else{
        // Creating four threads, each evaluating its own part
        for (int i = 0; i < MAX_THREAD; i++) {
            int* p;
            pthread_create(&threads[i], NULL, Det, (void*)(p));
        }
        // joining and waiting for all threads to complete
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_join(threads[i], NULL);

    }


      // destroy threats
    pthread_exit(NULL);

    return 0;

}

void* create(void* arg){
    int core = step_i++;
    printf("core %d \n",core);
    for (int i = core * n / 4; i < (core + 1) * n / 4; i++){
		for (int j = 0; j < n; j++){
            matA[i][j] = rand() % 10;
		}}


}
void* Det(void* arg)
{
	int core = step_i++%4;
    det=matA[0][0];
    for(int k=core*n/4;k<(core + 1) * n / 4-1;k++){
    pivot=k+1;
    for(int i=pivot+core*n/4;i<< (core + 1) * n / 4;i++){
        for(int j=pivot;j<n;j++)
            matA[i][j] = ( matA[k][k]*matA[i][j]-matA[k][j]*matA[i][k] )/matA[k][k];
            }
    det=det*matA[k+1][k+1];
    printf("\n\nDeterminant = %d \n", core);
    }



}

void exceptions(){
    if (n == 1)
        printf("\n\nDeterminant = %f\n", matA[0][0]);
    else
         printf("\n\nDeterminant = %f\n", matA[0][0] * matA[1][1] - matA[1][0] * matA[0][1]);
}


