#include <iostream>
#include <set>
#include <string>
#include <map>
#include <list>

using namespace std;

void creationOfMatrixForUrlsAndMatrixMultiplication(int numberOfLines, int numberOfIterations){

    string from_degree;
    string to_degree;
    string currLine;

    map<string,double> mapForUrls;                                                  //Creation of a map for the containment of the URLS
    map<string,list<string>> mapForEdges;                                           //Creation of a map to record the edges

    int mapSize;
    double indexCounter = 0.0;

    for (int i = 0; i < numberOfLines ; i++) {                                      //For loop to get the line from user input and insert both from degree and to degree to a set
        getline(cin, currLine);
        from_degree = currLine.substr(0, currLine.find(" "));
        to_degree = currLine.substr(currLine.find(" ")+1, currLine.size()-1);
        if(mapForUrls.count(from_degree)==0){                                       //Check if from degree exists in the map, if not add it and give it a specific ID
            mapForUrls[from_degree] = indexCounter;
            indexCounter++;
        }
        if(mapForUrls.count(to_degree)==0){                                         //Check if to degree exists in the map, if not add it and give it a specific ID
            mapForUrls[to_degree] = indexCounter;
            indexCounter++;
        }
        mapForEdges[from_degree].push_back(to_degree);                              //Add to mapForEdges the edges that the vertex has
    }
    mapSize = mapForUrls.size();

    double adjMatrix[mapSize][mapSize];                                             //Creation of the adjacency matrix
    double matrixForRank[mapSize];                                                  //Creation of the array that will be used for the rank of the graphs
    double matrixFinalResult[mapSize];                                              //Creation of the array that is used for output

    for(int i = 0; i < mapSize; i++){                                               //For loop inside a for loop to initialize all values to zero
        for(int j = 0; j < mapSize; j++){
            adjMatrix[i][j] = 0;
        }
    }

    for(auto it = mapForEdges.begin();it !=mapForEdges.end(); it++){                //For loop that iterates through the key values of the map
        for(auto it2 = it->second.begin(); it2 != it->second.end();it2++) {         //For loop that iterates through the linked list of the values of the keys
            auto value = *it;
            int from_matrix = mapForUrls.at(value.first);
            int to_matrix = mapForUrls.at(*it2);
            adjMatrix[to_matrix][from_matrix] = 1.0;                                //Set all values to 1, will update by outdegree in following for loop

        }
    }
    for (int i = 0; i < mapSize; i++) {                                             //For loop used to iterate through matrix. Used for both loops in order to adjust numbers in the matrix
        double outdegree = 0.0;
        for (int j = 0; j < mapSize; j++) {                                         //For loop that checks if the value of the matrix is an edge and then increments the outdegree
            if (adjMatrix[j][i] > 0) {
                outdegree++;
            }
        }
        for (int k = 0; k < mapSize; k++) {                                         //For loop that checks if there is an edge and updates the value to be 1/outdegree
            if(adjMatrix[k][i]>0){
                adjMatrix[k][i] = 1.0/outdegree;
            }
        }
    }
    for (int i = 0; i < mapSize; i++){                                              //For loop to initialize values of the matrix carrying the page rank and final result
        matrixForRank[i] = (1.0/mapSize);
        matrixFinalResult[i] = (1.0/mapSize);
    }

    //MATRIX MULTIPLICATION
    if(numberOfIterations == 0 || numberOfIterations == 1){                         //If power of iterations is less than 2, then we do not perform a matrix multiplication
    }

    else{
        int counter = 1;
        double multResult;

        while (counter < numberOfIterations) {
            for (int i = 0; i < mapSize; i++) {
                multResult=0.0;
                for (int j = 0; j < mapSize; j++) {
                    multResult += (adjMatrix[i][j] * matrixForRank[j]);             //Multiply by the rows of the adjMatrix  and the column of the matrixForRank
                }
                matrixFinalResult[i] = multResult;                                  //Append the multiplication result for each row of the final matrix
            }
            for(int i = 0; i < mapSize; i++){                                       //For loop that Aadjust values of the Matrix rank in order to adjust the page rank values
                matrixForRank[i] = matrixFinalResult[i];
            }
            counter++;
        }
    }

    for(auto it = mapForUrls.begin();it !=mapForUrls.end(); it++){                  //For loop that iterates through the map of the urls
        auto value = *it;
        for(int i = 0; i < mapSize; i++){
            if(i == mapForUrls.at(value.first)){                                    //If i is equal to the index of the key value, then append page rank
                mapForUrls[value.first] = matrixFinalResult[i];
            }
        }
    }

    for(auto it = mapForUrls.begin();it !=mapForUrls.end(); it++) {                //For loop that iterates through the key values of the map and prints the values
        auto value = *it;
        cout << value.first << " ";
        printf("%.2f", value.second);                                               //Use printf to get decimal places
        cout << "" << endl;
    }
}

int main() {

    string firstLine;
    getline(cin, firstLine);

    int numberOfLines = stoi(firstLine.substr(0));
    int numberOfIterations = stoi(firstLine.substr(2));

    creationOfMatrixForUrlsAndMatrixMultiplication(numberOfLines, numberOfIterations);

    return 0;
}