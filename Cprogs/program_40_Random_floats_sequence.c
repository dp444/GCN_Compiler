#include <stdio.h>
#include <stdlib.h>

int main(){ unsigned int seed = 12345; srand(seed); for (int i=0;i<10;++i) printf("%.6f\n", (double)rand()/RAND_MAX); return 0; }