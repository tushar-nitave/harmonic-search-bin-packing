#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

//parameters
int i=0;
float harmonic_mem_size;			//Harmonic Memory Size
float hmcr;							//Harmonic memory consideration rate
float par;							//Pitch adjusting rate
float max_iterations;				//Maximum number of iterations
int no_bin;							//No of bins available
int no_obj;							//No of objects to be fitted
float bin[1000], object[1000];
float HM[1000][1000];				
float bin_count[1000];				//No of bins used for each chromosome
int random_var,j;
int binWeight[1000];				//temporary bin for penalty function
int aggregate_bin_weight = 0;
int temp_weight[1000];
float temp_HM[1][1000];
int flag = 0;
int bestWeight;						//stores best weight of the population



int penalty(int );

//imports data from the given dataset
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

//calculate number of bins used for each chromosome
float fitness(int current_chromosome){
	for(int i=0; i<no_bin; i++)
		bin_count[i] = 0;

	int temp = 0;
	for(int i=0; i<no_obj; i++){
		int val = HM[current_chromosome][i];
		bin_count[val] = 1;
	}
	for(int i=0; i<no_bin; i++)
		temp = temp + bin_count[i];

	return temp;
}

//initialize harmonic memory
void initiator(){
	for(int i=0; i<harmonic_mem_size; i++){
		for(j=0; j<no_obj; j++){
			random_var = rand() % no_bin;
			HM[i][j] = random_var;
		}
		HM[i][j] = fitness(i);
		temp_weight[i] = penalty(i);
	}

	flag = 1;
}

//Generates new solution
void newSolution(int chromosome){
	int dim;
	int i;
	int x = 0;
	float rand1;	//random value for HMCR
	float rand2;	//random value for PAR

	for(i=0; i<no_obj; i++){

		rand1 = (double)(rand()%10)/10;
		rand2 = (double)(rand()%10)/10;

		//printf("\nRandom 1: %.1f\n", rand1);
		//printf("\nRandom 2: %.1f\n", rand2);

		if(rand1 < hmcr){
			if(rand2 < par){
				//HM[chromosome][i] = rand()%no_bin;
				temp_HM[0][i] = rand()%no_bin;
			}
		}

		else 
			continue;
	}

	penalty(chromosome);
	HM[chromosome][i] = fitness(chromosome);

	/*for(int i=0; i<no_obj+1; i++){
		printf("%.0f ", HM[chromosome][i]);
	}*/

	//printf("\n");
	/*for(int i=0; i<no_bin; i++)
		printf("%d ", binWeight[i]);
	printf("\n============\n");*/
}

//calculates assigned weight for each bin
int penalty(int row){
	int temp = 0;
	aggregate_bin_weight = 0;

	for(int i=0; i<no_bin; i++)
		binWeight[i] = bin[i];

	for(int i=0; i<no_obj; i++){
		if(flag == 0)
			temp = HM[row][i];
		else
			temp = temp_HM[0][i];

		binWeight[temp] = binWeight[temp] - object[i];
	}

	for(int i=0; i<no_bin; i++){
		if(binWeight[i] != bin[i]){
			aggregate_bin_weight = aggregate_bin_weight + abs(binWeight[i]);
		}
	}

	if(aggregate_bin_weight < temp_weight[row]){
		temp_weight[row] = aggregate_bin_weight;
		printf("%d\t", aggregate_bin_weight);
		for(int i=0; i<no_obj; i++)
			HM[row][i] = temp_HM[0][i];
	}

	else{
		printf("%d\t", temp_weight[row]);	
	}

	return aggregate_bin_weight;

}

void display(){

	//Parameters	
	//printf("Parameters:%.1f %.1f %.1f %.1f %d %d\n", harmonic_mem_size, hmcr, par, max_iterations, no_bin, no_obj);
	
	/*for(i=0; i<no_obj; i++)
		printf("\nObject %d Size: %.1f\n", i+1, object[i]);

	for(i=0; i<no_bin; i++)
		printf("\nBin %d Capacity: %.1f\n", i+1, bin[i]);*/

	for(int i=0; i<harmonic_mem_size; i++){
		for(int j=0; j<no_obj+1; j++){
			printf("%.0f ", HM[i][j]);
		}		
		printf("\n");
	}

	/*for(int i=0; i<max_iterations; i++)
		newSolution();


	/*printf("\n----------Calculated Penalties----------\n");
	for(int i=0; i<harmonic_mem_size; i++){
		penalty(i);
		printf("\n\nWeight of Bins\n\n");
		for(int i=0; i<no_bin; i++)
			printf("%d ", binWeight[i]);
	}
	printf("\n\n----------------------------------------");

	printf("\n\n");
	printf("\nObjects Allocated to different bins\n\n");
	for(int i=0; i<harmonic_mem_size; i++){
		for(int j=0; j<no_obj+1; j++){
			printf("%.0f ", HM[i][j]);
		}
		printf("\n");
	}*/

}

void main(){

	int i=0;
	srand(time(NULL));

	data_input();
	initiator();
	display();

	printf("\n\n\t=============== Result =============== \n\n\n");
	printf("\t\t Total Bin Weight\n\n");

	while(i < max_iterations){
		printf("\nIteration %d:\t", i+1);
		for(int j=0; j<harmonic_mem_size; j++){
			//printf("\nChromosome %d: ", j+1);
			newSolution(j);
		}
		printf("\n");
		i++;
	}
	
	printf("\n\n\t=============== End =============== \n\n");

	for(int i=0; i<harmonic_mem_size; i++){
		for(int j=0; j<no_obj; j++){
			printf("%0.f ", HM[i][j]);
		}
		printf("\n");
	}
}
	
