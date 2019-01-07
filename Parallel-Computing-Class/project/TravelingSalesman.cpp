#include <iostream>
#include <mpi.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>

#define MCW MPI_COMM_WORLD

using namespace std;

int NUM_CITIES = 100;
int POPULATION_COUNT = 1000;

struct City {
    public:
    int xValue;
    int yValue;
    int identity;
};

struct Genome{
    public:
    vector<City> travelRoute;
    long fitness;
};

void setFitness(Genome &genome){
    long fitness = 0;
    long xDistance = 0;
    long yDistance = 0;
    double interim = 0;
    for (int i = 1; i < genome.travelRoute.size(); i++){
        xDistance = genome.travelRoute[i].xValue - genome.travelRoute[i-1].xValue;
        xDistance = xDistance*xDistance;
        yDistance = genome.travelRoute[i].yValue - genome.travelRoute[i-1].yValue;
        yDistance = yDistance*yDistance;
        interim = xDistance + yDistance;
        interim = sqrt(interim);
        fitness = fitness + (interim);
        // xDistance = abs(genome.travelRoute[i-1].xValue - genome.travelRoute[i].xValue);
        // yDistance = abs(genome.travelRoute[i-1].yValue - genome.travelRoute[i].yValue);
        // fitness += xDistance + yDistance;
    }
    genome.fitness = fitness;
}

void mutate(Genome &genome){
    int start = rand()%NUM_CITIES;
    int end = rand()%NUM_CITIES;
    if( start > end ) { 
        swap(start, end);
    }
    if(start == end){
        return;
    }
    int startIndex = start;
    int endIndex = end;
    while(startIndex < endIndex){
        swap(genome.travelRoute[startIndex],genome.travelRoute[endIndex]);
        startIndex++;
        endIndex--;
    }
}

void pmx(Genome &genomeOne, Genome &genomeTwo){
    int start = rand()%NUM_CITIES;
    int end = rand()%NUM_CITIES;
    int j;
    int k;
    if( start > end ) { 
        swap(start, end);
    }
    for(int i = start; i < end; ++i){
        for(j = 0; j < NUM_CITIES; ++j) 
            if(genomeOne.travelRoute[j].identity == genomeTwo.travelRoute[i].identity)
                break;
        for(k = 0; k < NUM_CITIES; ++k) 
            if(genomeTwo.travelRoute[k].identity == genomeOne.travelRoute[i].identity)
                break;
        swap(genomeOne.travelRoute[i], genomeOne.travelRoute[j]);
        swap(genomeTwo.travelRoute[i], genomeTwo.travelRoute[k]);
    }
}

void populateMasterGenome(Genome &genome){
    ifstream inputFile("CartesianInput.txt");
    int inputX;
    int inputY;
    City inputCity;
    int identityValue = 0;
    while (inputFile >> inputX >> inputY)
    {
        inputCity.xValue = inputX;
        inputCity.yValue = inputY;
        inputCity.identity = identityValue;
        genome.travelRoute.push_back(inputCity);
        identityValue++;
    }
    inputFile.close();
}

void buildPopulation(vector<Genome> &genomeVector){
    // first build a single Genome.
    Genome masterGenome;
    populateMasterGenome(masterGenome);
    setFitness(masterGenome);

    // Build POPULATION_COUNT copies of the master genome.
    for(int i = 0; i < POPULATION_COUNT; i++){
        genomeVector.push_back(masterGenome);
    }
}

long bestFitness(vector<Genome> &genomeVector){
    long bestFitness;
    bestFitness = genomeVector[0].fitness;
    for(int i = 0; i < genomeVector.size(); ++i){
        if(genomeVector[i].fitness < bestFitness){
            bestFitness = genomeVector[i].fitness;
        }
    }
    return bestFitness;
}

void mateAndSelect(Genome &genomeOne, Genome &genomeTwo){
    Genome newGenomeOne;
    Genome newGenomeTwo;
    newGenomeOne = genomeOne;
    newGenomeTwo = genomeTwo;
    pmx(newGenomeOne,newGenomeTwo);
    if(rand()%200==0) {
        mutate(newGenomeOne);
    }
    if(rand()%200==0) {
        mutate(newGenomeTwo);
    }
    setFitness(newGenomeOne);
    setFitness(newGenomeTwo);
    if(newGenomeOne.fitness < genomeOne.fitness){
        genomeOne = newGenomeTwo;
    }
        
    if(newGenomeTwo.fitness < genomeTwo.fitness){
        genomeTwo = newGenomeTwo;
    }
}

void printPath(vector<Genome> &genomeVector){
    long bestFitness;
    Genome winningGenome;
    bestFitness = genomeVector[0].fitness;
    for(int i = 0; i < genomeVector.size(); ++i){
        if(genomeVector[i].fitness < bestFitness){
            bestFitness = genomeVector[i].fitness;
            winningGenome = genomeVector[i];
        }
    }
    cout << "VVVVVVVVVVVVVVVV" << endl;
    for(int i = 0; i < winningGenome.travelRoute.size(); i++){
        cout << winningGenome.travelRoute[i].identity << endl;
    }
    cout << "^^^^^^^^^^^" << endl;
}


int main(int argc, char **argv){

    vector<Genome> population;
    buildPopulation(population);
	
	int myRank;
	int worldSize;
    int mate;
    long bestCurrentFitness = 0;
    long oldBestFitness = 999999999;
    int counter = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MCW, &myRank);
	MPI_Comm_size(MCW, &worldSize);

    sleep(myRank*2);
    srand(time(0));
    MPI_Barrier(MCW);
    double start = MPI_Wtime();
    double end;




   while(true){
        for(int i = 0; i < population.size(); ++i){
            mate = rand()%population.size();
            mateAndSelect(population[i], population[mate]);
        }
        bestCurrentFitness = bestFitness(population);

        if(bestCurrentFitness < oldBestFitness){
            counter++;
            // if(counter%50 == 0){
            //     printPath(population);
            // }
            oldBestFitness = bestCurrentFitness;
            end = MPI_Wtime();
            
            // cout << bestCurrentFitness << " " << end - start << endl;
           
            
            cout << "P" << myRank << ": BestFitness-> " << bestCurrentFitness << " Time-> " << end - start << endl;
            
            
            // if(myRank == 0){
            //     cout << "P0: " << bestCurrentFitness << " ->" << counter << endl;
            // }
            // if(myRank == 1){
            //     cout << "                       P1: " << bestCurrentFitness << " ->" << counter << endl;
            // }
            // if(myRank == 2){
            //     cout << "                                             P2: " << bestCurrentFitness << " ->" << counter << endl;
            // }
            // if(myRank == 3){
            //     cout << "                                                                     P3: " << bestCurrentFitness << " ->" << counter << endl;
            // }
        }        
    }

	MPI_Finalize();

	return 0;	
}
