#ifndef TEAM2025_GEOGEBRA_H
#define TEAM2025_GEOGEBRA_H
#include "Odometry.h" 
#define chgsta 0
#define garage1 1
#define garage2all 2
#define garage3all 3
#define garage4all 4
#define garage5all 5
#define garage6all 6
#define garage7all 7
#define garage8all 8
#define garage9all 9
#define start1 10
#define start2 11
#define depot1 12
#define depot2 13

//position geogebra de la team jaune
struct Position positions_jaune[] = {
   Position(375.0f, 1775.0f,0), //chgsta
   Position(825.0f, 1725.0f,0), //garage1
   Position(75.0f, 1325.0f,0), //garage2all
   Position(2925.0f, 1325.0f,0), //garage3all
   Position(1100.0f, 950.0f,0), //garage4all
   Position(1900.0f, 950.0f,0), //garage5all
   Position(75.0f, 400.0f,0), //garage6all
   Position(2925.0f, 400.0f,0), //garage7all
   Position(775.0f, 250.0f,0), //garage8all
   Position(2225.0f, 250.0f,0), //garage9all
   Position(2775.0f, 875.0f,0), //start1
   Position(1225.0f, 225.0f,0), //start2
   Position(2775.0f, 75.0f,0), //depot1
   Position(775.0f, 75.0f,0), //depot2
};

//position geogebra de la team bleu
struct Position positions_bleu[] = {
   Position(2625.0f, 1775.0f,0), //chgsta
   Position(2175.0f, 1725.0f,0), //garage1
   Position(75.0f, 1325.0f,0), //garage2all
   Position(2925.0f, 1325.0f,0), //garage3all
   Position(1100.0f, 950.0f,0), //garage4all
   Position(1900.0f, 950.0f,0), //garage5all
   Position(75.0f, 400.0f,0), //garage6all
   Position(2925.0f, 400.0f,0), //garage7all
   Position(775.0f, 250.0f,0), //garage8all
   Position(2225.0f, 250.0f,0), //garage9all
   Position(225.0f, 875.0f,0), //start1
   Position(1775.0f, 225.0f,0), //start2
   Position(225.0f, 75.0f,0), //depot1
   Position(2225.0f, 75.0f,0), //depot2
};

struct Position* positions_match;//ce pointeur vaut soit positions_jaunes soit positions_bleu en fonction de la couleur.
#endif //TEAM2025_GEOGEBRA_H
