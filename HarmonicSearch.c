#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

//parameters
int i=0;
float harmonic_mem_size, hmcr, par, max_iterations;
int no_bin, no_obj;
float bin[1000], object[1000];
float HM[20][11];
float bin_count[1000];
int random,j;
int binWeight[1000];


//This function imports data from the given dataset
void data_input(){

	FILE *fp = fopen("para.txt", "r");
	
	fscanf(fp, "%f", &harmonic_mem_size);
	fscanf(fp, "%f", &hmcr);
	fscanf(fp, "%f", &par);
	fscanf(fp, "%f", &max_iterations);
	fscanf(fp, "%d", &no_bin);
	fscanf(fp, "%d", &no_obj);

	
	for(i=0; i<no_obj; i++)
		fscanf(fp, "%f", &object[i]);
	for(i=0; i<no_bin; i++)
		fscanf(fp, "%f", &bin[i]);
		//fscanf(fp, "%f", &bin[i]);

}

//allocates the bins to the objects
/*bool randomGenerator(int index, int random){
	for(int i=0; i<3; i++){
		if(object[index] < bin[random]){
			bin[random] = bin[random] - object[index];
			return true;
		}
		else
			random = rand() % no_bin;
	}
	return false;
}*/

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
	for(int i=0; i<harmonic_mem_size; i++){
		for(j=0; j<no_obj; j++){
			random = rand() % no_bin;
			//checks the availability of space in the selected bin for current object
			//if(randomGenerator(j,random)){
				HM[i][j] = random;
			/*}
			else{
				randomGenerator(j, random+1);
			}*/

		}
		HM[i][j] = fitness(i);
	}
}

//Generates new solution
void newSolution(){
	int dim;
	int x = 0;
	float rand1 = (double)(rand()%10)/10;
	float rand2 = (double)(rand()%10)/10;

	dim = rand() % 20;

	printf("\nRand 1: %.1f\n", rand1);
	printf("\nRand 2: %.1f\n", rand2);

	printf("\nSelected chromosome from %d dimension of harmonic memory\n", dim);

	while(x < no_obj){
		x++;

		if(rand1 < hmcr){
			if(rand2 < par){
				HM[dim][x] = rand()%no_bin;
			}
		}

		else
			continue;
	}

	HM[dim][x] = fitness(dim);

}

void penalty(int row){
	int temp;
	for(int i=0; i<no_bin; i++)
		binWeight[i] = bin[i];
	for(int i=0; i<no_obj; i++){
		temp = HM[row][i];
		binWeight[temp] = binWeight[temp] - object[i];
	}

}

void display(){

	//Parameters	
	printf("Parameters:%.1f %.1f %.1f %.1f %.1f %.1f\n", harmonic_mem_size, hmcr, par, max_iterations, no_bin, no_obj);
	
	for(i=0; i<no_obj; i++)
		printf("\nObject %d Size: %.1f\n", i+1, object[i]);

	for(i=0; i<no_bin; i++)
		printf("\nBin %d Capacity: %.1f\n", i+1, bin[i]);

	for(int i=0; i<harmonic_mem_size; i++){
		for(int j=0; j<no_obj+1; j++){
			printf("%.0f ", HM[i][j]);
		}
		printf("\n");
	}

	for(int i=0; i<max_iterations; i++)
		newSolution();

	for(int i=0; i<harmonic_mem_size; i++){
		penalty(i);
		printf("\nWeight of Bins\n");
		for(int i=0; i<no_bin; i++)
			printf(" %d ", binWeight[i]);
	}

	printf("\n");
	for(int i=0; i<harmonic_mem_size; i++){
		for(int j=0; j<no_obj+1; j++){
			printf("%.0f ", HM[i][j]);
		}
		printf("\n");
	}

}

void main(){

	srand(time(NULL));

	data_input();
	initiator();
	display();
}
	
