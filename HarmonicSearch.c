#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//parameters
int i=0;
float harmonic_mem_size, hmcr, par, max_iterations, no_bin, no_obj;
float bin[5], object[10];
float HM[20][11];
float bin_count[5];
int random,j;


//This function imports data from the given dataset
void data_input(){

	FILE *fp = fopen("para.txt", "r");
	
	fscanf(fp, "%f", &harmonic_mem_size);
	fscanf(fp, "%f", &hmcr);
	fscanf(fp, "%f", &par);
	fscanf(fp, "%f", &max_iterations);
	fscanf(fp, "%f", &no_bin);
	fscanf(fp, "%f", &no_obj);

	
	for(i=0; i<no_obj; i++)
		fscanf(fp, "%f", &object[i]);
	for(i=0; i<no_bin; i++)
		fscanf(fp, "%f", &bin[i]);

}

//allocates the bins to the objects
bool randomGenerator(int index, int random){
	for(int i=0; i<2; i++){
		if(object[index] < bin[random]){
			bin[random] = bin[random] - object[index];
			return true;
		}
		else
			random = rand() % 5;
	}
}

//a function to calculate number of bins used for each chromosome
float fitness(int chromosome){
	for(int i=0; i<no_bin; i++)
		bin_count[i] = 0;

	int temp = 0;
	for(int i=0; i<no_obj; i++){
		int val = HM[chromosome][i];
		bin_count[val] = 1;
	}
	for(int i=0; i<no_bin; i++)
		temp = temp + bin_count[i];
	return temp;
}

//This function is used to initialize harmonic memory
void initiator(){
	for(int i=0; i<20; i++){
		for(j=0; j<10; j++){
			random = rand() % 5;
			//checks the availability of space in the selected bin for current object
			if(randomGenerator(j,random)){
				HM[i][j] = random;
			}
		}
		HM[i][j] = fitness(i);
	}
}


void display(){

	//Parameters	
	printf("Parameters:%.1f %.1f %.1f %.1f %.1f %.1f\n", harmonic_mem_size, hmcr, par, max_iterations, no_bin, no_obj);
	
	for(i=0; i<no_obj; i++)
		printf("\nObject %d Size: %.1f\n", i+1, object[i]);

	for(i=0; i<no_bin; i++)
		printf("\nBin %d Capacity: %.1f\n", i+1, bin[i]);

	for(int i=0; i<20; i++){
		for(int j=0; j<11; j++){
			printf("%.0f ", HM[i][j]);
		}
		printf("\n");
	}

}

void main(){
		
	data_input();
	initiator();
	display();
}
	
