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
#define check1 14
#define garage41all 15
#define garage51all 16
#define chgsta1 17
#define garage81all 18
#define garage91all 19

//position geogebra de la team jaune
struct Position positions_jaune[] = {
   Position(375.0f, 1945.0f, -1.570796327), //chgsta
   Position(825.0f, 1725.0f, -1.570796327), //garage1
   Position(75.0f, 1325.0f, PI/3), //garage2all
   Position(2925.0f, 1325.0f, -1.570796327), //garage3all
   Position(1100.0f, 870.0f, -1.570796327), //garage4all
   Position(1900.0f, 870.0f, -1.570796327), //garage5all
   Position(75.0f, 400.0f, -1.570796327), //garage6all
   Position(2925.0f, 400.0f, -1.570796327), //garage7all
   Position(775.0f, 250.0f, -1.570796327), //garage8all
   Position(2225.0f, 250.0f, -1.570796327), //garage9all
   Position(2775.0f, 875.0f, -1.570796327), //start1
   Position(1225.0f, 55.0f, -1.570796327), //start2
   Position(2775.0f, 75.0f, -1.570796327), //depot1
   Position(775.0f, 150.0f, -1.570796327), //depot2
   Position(996.0f, 566.0f, -1.570796327), //check1
   Position(1100.0f, 800.0f, -1.570796327), //garage41all
   Position(1900.0f, 800.0f, -1.570796327), //garage51all
   Position(375.0f, 1750.0f, -1.570796327), //chgsta1
   Position(775.0f, 350.0f, -1.570796327), //garage81all
   Position(2225.0f, 350.0f, -1.570796327), //garage91all
};

//position geogebra de la team bleu
struct Position positions_bleu[] = {
   Position(2625.0f, 1945.0f, -1.570796327), //chgsta
   Position(2175.0f, 1725.0f, -1.570796327), //garage1
   Position(75.0f, 1325.0f, -1.570796327), //garage2all
   Position(2925.0f, 1325.0f, -1.570796327), //garage3all
   Position(1100.0f, 870.0f, -1.570796327), //garage4all
   Position(1900.0f, 870.0f, -1.570796327), //garage5all
   Position(75.0f, 400.0f, -1.570796327), //garage6all
   Position(2925.0f, 400.0f, -1.570796327), //garage7all
   Position(775.0f, 250.0f, -1.570796327), //garage8all
   Position(2225.0f, 250.0f, -1.570796327), //garage9all
   Position(225.0f, 875.0f, -1.570796327), //start1
   Position(1775.0f, 55.0f, -1.570796327), //start2
   Position(225.0f, 75.0f, -1.570796327), //depot1
   Position(2225.0f, 150.0f, -1.570796327), //depot2
   Position(2004.0f, 566.0f, -1.570796327), //check1
   Position(1100.0f, 800.0f, -1.570796327), //garage41all
   Position(1900.0f, 800.0f, -1.570796327), //garage51all
   Position(2625.0f, 1750.0f, -1.570796327), //chgsta1
   Position(775.0f, 350.0f, -1.570796327), //garage81all
   Position(2225.0f, 350.0f, -1.570796327), //garage91all
};

struct Position* positions_match;//ce pointeur vaut soit positions_jaunes soit positions_bleu en fonction de la couleur.
#endif //TEAM2025_GEOGEBRA_H
