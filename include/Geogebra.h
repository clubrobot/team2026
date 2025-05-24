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
#define chgsta1 15

//position geogebra de la team jaune
struct Position positions_jaune[] = {
   Position(375.0f, 1945.0f,1.570796327), //chgsta_jaune
   Position(825.0f, 1725.0f,1.570796327), //garage1_jaune
   Position(75.0f, 1325.0f,1.570796327), //garage2all_jaune
   Position(2925.0f, 1325.0f,1.570796327), //garage3all_jaune
   Position(1100.0f, 950.0f,1.570796327), //garage4all_jaune
   Position(1900.0f, 950.0f,1.570796327), //garage5all_jaune
   Position(75.0f, 400.0f,1.570796327), //garage6all_jaune
   Position(2925.0f, 400.0f,1.570796327), //garage7all_jaune
   Position(775.0f, 250.0f,1.570796327), //garage8all_jaune
   Position(2225.0f, 250.0f,1.570796327), //garage9all_jaune
   Position(2775.0f, 875.0f,1.570796327), //start1_jaune
   Position(1225.0f, 55.0f,1.570796327), //start2_jaune
   Position(2775.0f, 75.0f,1.570796327), //depot1_jaune
   Position(775.0f, 150.0f,1.570796327), //depot2_jaune
   Position(996.0f, 566.0f,1.570796327), //check1_jaune
   Position(375.0f, 1750.0f,1.570796327), //chgsta1_jaune
};

//position geogebra de la team bleu
struct Position positions_bleu[] = {
   Position(2625.0f, 1945.0f,1.570796327), //chgsta_bleu
   Position(2175.0f, 1725.0f,1.570796327), //garage1_bleu
   Position(75.0f, 1325.0f,1.570796327), //garage2all_bleu
   Position(2925.0f, 1325.0f,1.570796327), //garage3all_bleu
   Position(1100.0f, 950.0f,1.570796327), //garage4all_bleu
   Position(1900.0f, 950.0f,1.570796327), //garage5all_bleu
   Position(75.0f, 400.0f,1.570796327), //garage6all_bleu
   Position(2925.0f, 400.0f,1.570796327), //garage7all_bleu
   Position(775.0f, 250.0f,1.570796327), //garage8all_bleu
   Position(2225.0f, 250.0f,1.570796327), //garage9all_bleu
   Position(225.0f, 875.0f,1.570796327), //start1_bleu
   Position(1775.0f, 55.0f,1.570796327), //start2_bleu
   Position(225.0f, 75.0f,1.570796327), //depot1_bleu
   Position(2225.0f, 150.0f,1.570796327), //depot2_bleu
   Position(2004.0f, 566.0f,1.570796327), //check1_bleu
   Position(2625.0f, 1750.0f,1.570796327), //chgsta1_bleu
};

struct Position* positions_match;//ce pointeur vaut soit positions_jaunes soit positions_bleu en fonction de la couleur.
#endif //TEAM2025_GEOGEBRA_H
