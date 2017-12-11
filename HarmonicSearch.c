//Implementing Harmonic Search Algorithm for bin packing problem

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

//Harmonic Search Parameters
#define nvar 5			//number of decision variables
#define HMS 5			//Harmonic Memory Size
#define HMCR 0.9		//Probability of selecting the components from HM members
#define PAR 0.4			// Pitch Adjusting Rate : Probability of a candidate from the HM to be mutated
#define max_iterations 100 


/***************	1. Initiator : Initializes the harmonic memory	***************/

void Initiator()
{

} 

/***************	2. Fitness : Calculating fitness of each row	***************/
double fitness()
{

}

/***************	3. StopCondition : Terminates the program after reaching max iterations	***************/
bool stopCondition()
{

}


void main(){
	int a;
	printf("Enter a: ");
	scanf("%d", &a);

	printf("Enter a: %d", a);
}