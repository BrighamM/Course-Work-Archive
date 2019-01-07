#include <iostream>
#include <mpi.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <algorithm>

#define MCW MPI_COMM_WORLD

using namespace std;

int DEPOT_X_VALUE = 5000;
int DEPOT_Y_VALUE = 5000;
int POPULATION_COUNT = 1000;
int CITY_SQUARE_LENGTH = 25000;

struct Package {
    public:
    long xValue;
    long yValue;
    long identityNumber;
    long distanceFromDepot;
    int costToDeliverFromTruckToDoor;
    int size;
    int nebulousCost;
};

struct DeliveryRoute{
    public:
    vector<Package> travelRoute;
    long fitness;
};

void printPath(vector<DeliveryRoute> &genomeVector){

    ofstream dataOutputFile;
    dataOutputFile.open ("./GraphicalOutput.txt", std::ios_base::app);

    long bestFitness;
    DeliveryRoute winningGenome;
    bestFitness = genomeVector[0].fitness;
    winningGenome = genomeVector[0];
    for(int i = 0; i < genomeVector.size(); ++i){
        if(genomeVector[i].fitness < bestFitness){
            bestFitness = genomeVector[i].fitness;
            winningGenome = genomeVector[i];
        }
    }
    // cout << "VVVVVVVVVVVVVVVV" << " Output Size: " << winningGenome.travelRoute.size() << endl;
    for(int i = 0; i < winningGenome.travelRoute.size(); i++){
        dataOutputFile << winningGenome.travelRoute[i].xValue << " " << winningGenome.travelRoute[i].yValue << endl;
        // cout << winningGenome.travelRoute[i].xValue << " " << winningGenome.travelRoute[i].yValue << " " << winningGenome.travelRoute[i].identityNumber << endl;
    }
    dataOutputFile.close();
    // cout << "^^^^^^^^^^^" << endl;
}

long bestFitness(vector<DeliveryRoute> &genomeVector){
    long bestFitness;
    bestFitness = genomeVector[0].fitness;
    for(int i = 0; i < genomeVector.size(); ++i){
        if(genomeVector[i].fitness < bestFitness){
            bestFitness = genomeVector[i].fitness;
        }
    }
    return bestFitness;
}

void mutate(DeliveryRoute &genome){
    int start = rand()%(genome.travelRoute.size());
    int end = rand()%(genome.travelRoute.size());
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

void pmx(DeliveryRoute &genomeOne, DeliveryRoute &genomeTwo){
    int start = rand()%(genomeOne.travelRoute.size());
    int end = rand()%(genomeOne.travelRoute.size());
    int j;
    int k;
    if( start > end ) { 
        swap(start, end);
    }
    for(int i = start; i < end; ++i){
        for(j = 0; j < genomeOne.travelRoute.size(); ++j) 
            if(genomeOne.travelRoute[j].identityNumber == genomeTwo.travelRoute[i].identityNumber)
                break;
        for(k = 0; k < genomeOne.travelRoute.size(); ++k) 
            if(genomeTwo.travelRoute[k].identityNumber == genomeOne.travelRoute[i].identityNumber)
                break;
        swap(genomeOne.travelRoute[i], genomeOne.travelRoute[j]);
        swap(genomeTwo.travelRoute[i], genomeTwo.travelRoute[k]);
    }
}

void setFitness(DeliveryRoute &deliveryRoute){
    long fitness = 0;
    long xDistance = 0;
    long yDistance = 0;
    double interim = 0;
    for (int i = 1; i < deliveryRoute.travelRoute.size(); i++){
        xDistance = deliveryRoute.travelRoute[i].xValue - deliveryRoute.travelRoute[i-1].xValue;
        xDistance = xDistance*xDistance;
        yDistance = deliveryRoute.travelRoute[i].yValue - deliveryRoute.travelRoute[i-1].yValue;
        yDistance = yDistance*yDistance;
        interim = xDistance + yDistance;
        interim = sqrt(interim);
        fitness = fitness + (interim);
        // xDistance = abs(genome.travelRoute[i-1].xValue - genome.travelRoute[i].xValue);
        // yDistance = abs(genome.travelRoute[i-1].yValue - genome.travelRoute[i].yValue);
        // fitness += xDistance + yDistance;
    }
    deliveryRoute.fitness = fitness;
}

void mateAndSelect(DeliveryRoute &genomeOne, DeliveryRoute &genomeTwo){
    DeliveryRoute newGenomeOne;
    DeliveryRoute newGenomeTwo;
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

void populateMasterDeliveryRoute(DeliveryRoute &deliveryRoute){
    ifstream inputFile("UnifiedOutput.txt");
    int inputX;
    int inputY;
    int size;
    int identity;
    long xDistance = 0;
    long yDistance = 0;
    Package inputPackage;
    while (inputFile >> inputX >> inputY >> size >> identity)
    {
        inputPackage.xValue = inputX;
        inputPackage.yValue = inputY;
        inputPackage.size = size;
        inputPackage.identityNumber = identity;
        inputPackage.costToDeliverFromTruckToDoor = 15 + (15*inputPackage.size);
        inputPackage.nebulousCost = 0;
        xDistance = inputPackage.xValue - DEPOT_X_VALUE;
        xDistance = xDistance*xDistance;
        yDistance = inputPackage.yValue - DEPOT_Y_VALUE;
        yDistance = yDistance*yDistance;
        inputPackage.distanceFromDepot = xDistance + yDistance;
        inputPackage.distanceFromDepot = sqrt(inputPackage.distanceFromDepot);
        deliveryRoute.travelRoute.push_back(inputPackage);
        
    }
    inputFile.close();
}

void buildPossibleDeliveryRoutes(vector<DeliveryRoute> &possibleDeliveryRoutesVector){
    // first build a single DeliveryRoute.
    DeliveryRoute masterDeliveryRoute;
    populateMasterDeliveryRoute(masterDeliveryRoute);
    setFitness(masterDeliveryRoute);

    // Build POPULATION_COUNT copies of the master genome.
    for(int i = 0; i < POPULATION_COUNT; i++){
        possibleDeliveryRoutesVector.push_back(masterDeliveryRoute);
    }
}

void generateSolutionsFromPopulation(vector<DeliveryRoute> &populationVector){
    int myRank;
    MPI_Comm_rank(MCW, &myRank);
    int mate;
    long bestCurrentFitness = 0;
    long oldBestFitness = 999999999;
    int counter = 0;
    double start = MPI_Wtime();
    double end;

    double noGainTimeLimit = 60;
    double noGainTimeStart = 0;
    double noGainTimeEnd = 0;
    double cumulativeNoGainTime = 0;
    bool foundBetterTime = true;

    cout << "THE PROBLEM SIZE IS: " << populationVector[0].travelRoute.size() << endl;

    while(true){
        for(int i = 0; i < populationVector.size(); ++i){
            mate = rand()%populationVector.size();
            mateAndSelect(populationVector[i], populationVector[mate]);
        }
        bestCurrentFitness = bestFitness(populationVector);

        if(bestCurrentFitness < oldBestFitness){
            foundBetterTime = true;
            counter++;
            if(counter%50 == 0){
                // printPath(populationVector);
            }
            oldBestFitness = bestCurrentFitness;
            end = MPI_Wtime();
            cout << "P" << myRank << ": BestFitness-> " << bestCurrentFitness/5280 << " Time-> " << end - start << endl;
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
        else {
            if(foundBetterTime){
                noGainTimeStart = MPI_Wtime();
            }
            foundBetterTime = false;
        }
        if(!foundBetterTime){
            noGainTimeEnd = MPI_Wtime();
            cumulativeNoGainTime = noGainTimeEnd - noGainTimeStart; 
            if(cumulativeNoGainTime >= noGainTimeLimit){
                printPath(populationVector);
                cout << "YOUR DEAD TIME WAS: " << cumulativeNoGainTime << endl;
                break;
            }
        }
    }
}

void populateSubDeliveryRoute(DeliveryRoute &deliveryRouteToPopulate, 
                                DeliveryRoute &comprehensiveRoute, 
                                int rootSquare, 
                                int quadIndex) {
    // Bottom Left is zero zero with respect to xy coords of package.
    // top left is zero zero with respect to rows and columns.
    int row = quadIndex / rootSquare;
    int col = quadIndex % rootSquare;

    double dRow = row;
    double dCol = col;
    double dRootSquare = rootSquare;
    double dQuadIndex = quadIndex;
    double dCitySquareLength = CITY_SQUARE_LENGTH;

    double northBoundary = dCitySquareLength - (dRow*(dCitySquareLength/dRootSquare));
    double southBoundary = dCitySquareLength - ((dRow + 1)*(dCitySquareLength/dRootSquare));
    double westBoundary = dCol*(dCitySquareLength/dRootSquare);
    double eastBoundary = (dCol + 1)*(dCitySquareLength/dRootSquare);
    // cout << dRow << " " << dCol << " " << dRootSquare << " " << dQuadIndex << " " << dCitySquareLength << endl;

    for(int i = 0; i < comprehensiveRoute.travelRoute.size(); i++){
        if( comprehensiveRoute.travelRoute[i].xValue < eastBoundary && 
            comprehensiveRoute.travelRoute[i].xValue > westBoundary && 
            comprehensiveRoute.travelRoute[i].yValue < northBoundary &&
            comprehensiveRoute.travelRoute[i].yValue > southBoundary ) {
            deliveryRouteToPopulate.travelRoute.push_back(comprehensiveRoute.travelRoute[i]);
        }
    }
}

void populateVectorListFromPackages(vector<DeliveryRoute> &geoSortedDeliveryRoutes, 
                                    DeliveryRoute &comprehensiveRoute, 
                                    int rootSquare) {
    
    // find total number of quadrants that will be used.
    int totalQuadrants = rootSquare*rootSquare;
    // For each quadrant build a list of packages contained in the quadrant
    for(int i = 0; i < totalQuadrants; i++){
        DeliveryRoute deliveryRouteSubList;
        populateSubDeliveryRoute(deliveryRouteSubList, comprehensiveRoute, rootSquare, i);
        geoSortedDeliveryRoutes.push_back(deliveryRouteSubList);
    }
}

void printGeographicParsedVectorOfVectors(vector<DeliveryRoute>  masterList){
    for(int i = 0; i < masterList.size(); i++){
        cout << "Now we print the list for quadrant: " << i << endl;
        for(int j = 0; j < masterList[i].travelRoute.size(); j++){
            cout << masterList[i].travelRoute[j].identityNumber << endl;
        }
    }
}

void generatePopulationFromOriginalDeliveryRoute(vector<DeliveryRoute> &populationVector, 
                                                    DeliveryRoute &originalDeliveryRoute){
    setFitness(originalDeliveryRoute);
    // Build POPULATION_COUNT copies of the master genome.
    for(int i = 0; i < POPULATION_COUNT; i++){
        populationVector.push_back(originalDeliveryRoute);
    }
}

void optimizeDeliveryRoute(DeliveryRoute inputDeliveryRoute) {
    vector<DeliveryRoute> possibleRoutes;
    generatePopulationFromOriginalDeliveryRoute(possibleRoutes, inputDeliveryRoute);
    generateSolutionsFromPopulation(possibleRoutes);

}

int main(int argc, char **argv){



    // vector<DeliveryRoute> possibleRoutes;
    // buildPossibleDeliveryRoutes(possibleRoutes);

	int myRank;
	int worldSize;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MCW, &myRank);
	MPI_Comm_size(MCW, &worldSize);

    sleep(myRank*2);
    srand(time(0));
    MPI_Barrier(MCW);

    // generateSolutionsFromPopulation(possibleRoutes, myRank);











   // This is where we are going to divide the set, geographically, by powers of i.
    // For example, 1,4,9.16,25... in a sense, we are performing a sort on the DeliveryRoute
    // We are going to take our possible Routes

    // GIVEN A VECTOR OF PACKAGES
    // Return a list of vectors, where each vector represents a single "root quadrant" with all the packages 
    // contained in that geographic quadrant.

    DeliveryRoute originalPackageList;
    populateMasterDeliveryRoute(originalPackageList);

    vector<DeliveryRoute> geoSortedDeliveryRoutes;
    populateVectorListFromPackages(geoSortedDeliveryRoutes, originalPackageList, 4);
    // printGeographicParsedVectorOfVectors(geoSortedDeliveryRoutes);

    // Given a Delivery Route, optimize the bajeebers out of it.

    // Now we need to snakeify the list if applicable. to snakeify we need to reverse every
    // other row in the list
    // 
    int rootSize = sqrt(geoSortedDeliveryRoutes.size());
    for(int i = rootSize; i < geoSortedDeliveryRoutes.size(); i+=2*rootSize){
        reverse(geoSortedDeliveryRoutes.begin() + i, geoSortedDeliveryRoutes.begin() + i + rootSize);
    }

    cout << "Num Rows = " << sqrt(geoSortedDeliveryRoutes.size()) << endl;

    for(int i = 0; i < geoSortedDeliveryRoutes.size(); i++){
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Beginning Optimization with quadrant: " << i << endl;
        optimizeDeliveryRoute(geoSortedDeliveryRoutes[i]);
    }

    /**
     * Now that we have our optimized delivery routes we are going to overload one of these routes, 
     * and perform a type of load balancing wherein we give some of its packages to its neighbors.
     * In this fashion we can show simple comparisons of where gains can be made. Gains could be made
     * by the way we distribute packages across the various geo-routes, do we split by randomness or by geography?
     * Further when we have an overloaded truck can any meaningful gains be made by sharing some of it's packages?
     * Is it even worth it to give those packages away? Do we impose a time limit of some fashion where packages have
     * to be delivered by some time of the day like 5 o clock and you can only start at 8 o clock? Finally is it better 
     * to crack one big problem or break it up into smaller problems?
     */
    

    








	MPI_Finalize();
	return 0;	
}