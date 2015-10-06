#include <stdio.h>


int main(){
    int limit = 1500000;
    int prime = 1030;
    int i,j,numbers[limit];
    int primes[prime];

    /*fill the array with natural numbers*/
    i = 0;
    while (i<limit) {
        numbers[i]=i+2;
        i++;
    }

    /*sieve the non-primes*/
    i = 0;
    while (i<limit) {
        if (numbers[i] != -1){
            j = 2*numbers[i]-2;
            while (j<limit) {
                numbers[j]=-1;
                j+= numbers[i];
            }
        }
        i++;

    }

    /*transfer the primes to their own array*/
    j = 0;
    i = 0;
    while (i<limit&&j<prime) {
        if (numbers[i]!=-1){
            j++;
            primes[j] = numbers[i];   
        }
        i++;
    }

    /*print*/
    i = 0;
    while (i<prime) {
        printf("%d, ",primes[i]);
        i++;
    }

return 0;
}

