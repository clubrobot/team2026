#ifndef TEAM2025_GEOGEBRA_H
#define TEAM2025_GEOGEBRA_H
#include "Odometry.h"
#define psdepart 0
#define psfin 1

//position geogebra de la team jaune
struct Position positions_jaune[] = {
        Position(0.0f, 275.0f,0), //psdepart
        Position(-12.0f, 725.0f,0), //psfin
};

//position geogebra de la team bleu
struct Position positions_bleu[] = {
        Position(0.0f, 2725.0f,0), //psdepart
        Position(-11.0f, 2275.0f,0), //psfin
};

struct Position* positions_match;//ce pointeur vaut soit positions_jaunes soit positions_bleu en fonction de la couleur.
#endif //TEAM2025_GEOGEBRA_H
