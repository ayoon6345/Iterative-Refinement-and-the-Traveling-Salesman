#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <random>

using namespace std;

struct point{double x, y;};
vector<point> points(50);
vector<int> tour(50);
vector<int> shortestTour(50);

double tempTotal = 0.0;
double total = 3000.0;

//compute distance between two points
double dist(int a, int b)
{  
    double dx = points[a].x - points[b].x, dy = points[a].y - points[b].y;  
    return sqrt(dx*dx + dy*dy);
}
//compute tour length
double tourlen(void)
{  
    double total = 0.0; 
    for (int i=0; i<50; i++) {    
        int a = tour[i];  
        int b = tour[(i+1)%50];  
        total += dist(a,b); 
    }  
    return total;
}
//Reverse section of tour
int reverse(int i, int j)
{
    while(i>j){
    swap(tour[i], tour[j]);
    i--;
    j++;
    }
    return 0;
}

int main(void)
{
    double distA, distB;
    double pointx, pointy;
    //read in file into a vector of structs
    int i = 0;
    ifstream pointfile("tsp_points.txt");
    while(pointfile >> pointx >> pointy){
        points[i].x = pointx;
        points[i].y = pointy;
        i++; 
    }
    pointfile.close();
    for(int i=0; i<50; i++){
        tour[i] = i;
    }
    //Iterative refine shortest tour
    for(int o=0; o<600;o++){
    random_shuffle(tour.begin(), tour.end());
        for(int k=0; k<1000; k++){     
            for(int i=1; i<50; i++){
             int j = rand()%i;
            
             distA = dist(tour[i], tour[(i+1)]) + dist(tour[j], tour[(j+1)]);
             distB = dist(tour[j], tour[i]) + dist(tour[(j+1)], tour[(i+1)]);

             if(distB < distA){   
                reverse(i, (j+1));              
            }
        }             
        //Set new shortest distance and tour 
         if(tourlen() < total){
             shortestTour = tour;
             total = tourlen();
        }
       }          
    }
    //print out shortest tour
    cout << "tour length: " << total << "\n";
    for(int i=0; i<50; i++){
       cout << shortestTour[i] << " ";
    }
    cout << "\n";
    return 0;
}