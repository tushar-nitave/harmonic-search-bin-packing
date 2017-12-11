#include<stdio.h>
#include<stdlib.h>

void main(){
	
	int i=0;
	float harmonic_mem_size, hmcr, par, max_iterations, no_bin, no_obj;
	float array[10], array2[10];
	
	FILE *fp = fopen("para.txt", "r");
	
	fscanf(fp, "%f", &harmonic_mem_size);
	fscanf(fp, "%f", &hmcr);
	fscanf(fp, "%f", &par);
	fscanf(fp, "%f", &max_iterations);
	fscanf(fp, "%f", &no_bin);
	fscanf(fp, "%f", &no_obj);
	
	for(i=0; i<no_obj; i++)
		fscanf(fp, "%f", &array[i]);
	for(i=0; i<no_bin; i++)
		fscanf(fp, "%f", &array2[i]);
		
	//Parameters	
	printf("Parameters:%.1f %.1f %.1f %.1f %.1f %.1f\n", harmonic_mem_size, hmcr, par, max_iterations, no_bin, no_obj);
	
	for(i=0; i<no_obj; i++)
		printf("\nObject %d Size: %.1f\n", i+1, array[i]);

	for(i=0; i<no_bin; i++)
		printf("\nBin %d Capacity: %.1f\n", i+1, array2[i]);
}
