#ifndef TEAM2026_GEOGEBRA_H_CERTIF
#define TEAM2026_GEOGEBRA_H_CERTIF
#include "Components/Odometry.h"
#define Depart_J 0
#define R1L_J 1
#define R2L_J 2
#define R3L_J 3
#define R1P_J 4
#define R2P_J 5
#define R3P_J 6
#define R1D_J 7
#define R0D_J 8
#define R2D_J 9
#define R3D_J 10
#define R0P_J 11
#define R0L_J 12
#define R0T_J 13
#define R0bisT_J 14
#define R1T_J 15
#define R1bisT_J 16
#define R2D_B 0
#define R1L_B 1
#define R1D_B 2
#define R2P_B 3
#define R2L_B 4
#define R3L_B 5
#define R3P_B 6
#define R1P_B 7
#define R0D_B 8
#define R3D_B 9
#define R0P_B 10
#define R0L_B 11
#define Depart_B 12
#define R0T_B 13
#define R0bisT_B 14
#define R1T_B 15
#define R1bisT_B 16

//position geogebra de la team jaune
inline Position positions_jaune[] = {
   Position(300.0f, 1741.0f,-PI/2), //Depart_{J}_jaune
   Position(440.00000000000006f, 400.0f,PI), //R1L_{J}_jaune
   Position(1099.11517132674f, 438.52527975099997f,-PI/2), //R2L_{J}_jaune
   Position(1147.951679161948f, 535.2824981187007f,PI/2), //R3L_{J}_jaune
   Position(400.0f, 400.0f,-PI/2), //R1P_{J}_jaune
   Position(1099.11517132674f, 398.52527975099997f,-PI/2), //R2P_{J}_jaune
   Position(1147.951679161948f, 575.2824981187008f,PI/2), //R3P_{J}_jaune
   Position(98.8404375784381f, 557.4783708591414f,PI/2), //R1D_{J}_jaune
   Position(559.756444679994f, 1030.8366002410846f,-PI/4), //R0D_{J}_jaune
   Position(940.0f, 340.0f,- 2.8 * PI / 4), //R2D_{J}_jaune
   Position(1254.0790317363299f, 1203.5880269343f,PI / 2), //R3D_{J}_jaune
   Position(399.78448130320004f, 1198.67175411751f,PI), //R0P_{J}_jaune
   Position(439.7844813032f, 1198.67175411751f,PI), //R0L_{J}_jaune
   Position(300, 1447.4414154568f,- PI / 2), //R0T_{J}_jaune
   Position(401.67436202941997f, 1086.20349433857f,- PI / 2), //R0bisT_{J}_jaune
   Position(478.07413141305f, 859.46869487747f,- PI / 2), //R1T_J_jaune
   Position(147.82996698057f, 435.57320023281f,3 * PI /4), //R1bisT_J_jaune
};

//position geogebra de la team bleu
inline Position positions_bleu[] = {
   Position(2078.9483875455016f, 351.0496055811986f,- PI / 4), //R2D_{B}_bleu
   Position(2558.8519471753484f, 402.0237154489629f,PI), //R1L_{B}_bleu
   Position(2899.7100722722757f, 560.1534813867162f,PI/2), //R1D_{B}_bleu
   Position(1899.7407953662669f, 390.2899572672202f,-1.01 * PI/2), //R2P_{B}_bleu
   Position(1899.6643874376964f, 439.28988429000924f,-PI/2), //R2L_{B}_bleu
   Position(1850.6431432355478f, 535.9536387208536f,PI/2), //R3L_{B}_bleu
   Position(1850.5667353069769f, 575.9535657436428f,PI/2), //R3P_{B}_bleu
   Position(2598.851874198138f, 402.1001233775338f,-PI/2), //R1P_{B}_bleu
   Position(2437.8906980353604f, 1032.6304062258816f,-PI/4), //R0D_{B}_bleu
   Position(1743.23938825539f, 1204.0552239802414f,PI / 2), //R3D_{B}_bleu
   Position(2597.541771143235f, 1200.7708320575468f,PI), //R0P_{B}_bleu
   Position(2557.541844120446f, 1200.6944241289762f,PI), //R0L_{B}_bleu
   Position(2696.4715847801294f, 1741.2888699588405f,-PI/2), //Depart_B_bleu
   Position(2696.f, 1541.f,-PI/2), //R0T_B_bleu
   Position(2595.8667305339627f, 1088.2991674223165f,0), //R0bisT_B_bleu
   Position(2519.9002089454284f, 861.4188429200012f,0), //R1T_B_bleu
   Position(2850.953495287365f, 438.1549534562866f,0), //R1bisT_{B}_bleu
};

inline Position* positions_match;//ce pointeur vaut soit positions_bleus soit positions_bleu en fonction de la couleur.
#endif //TEAM2026_GEOGEBRA_H_CERTIF
