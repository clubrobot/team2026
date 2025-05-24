//
// Created by boris on 5/21/25.
//

#include "Teleplot.h"

#define BEACON_MSG_LEN_MAX 50

char teleplot_tampon[BEACON_MSG_LEN_MAX]="";

long teleplote_temps_ms;
bool teleplot_temps_fige;

void Teleplot_send_string(){
    printf(teleplot_tampon);
}

/// @brief Renvoi le temps en milliseconde, le temps réel ou le temps figé
/// @param
/// @return temps en millisecondes
long Teleplot_get_temps(void){
    if(teleplot_temps_fige){
        return teleplote_temps_ms;
    }
    return (long) (micros()/1000);
}

/// @brief Permet de "bloquer le temps" pour recevoir toutes les données datées à la même milliseconde
/// Simplifie beaucoup le traitement des données en CSV lors d'un import dans un tableur.
void Teleplot_fige_temps(void){
    teleplot_temps_fige = false;
    teleplote_temps_ms = Teleplot_get_temps();
    teleplot_temps_fige = true;
}
void Teleplot_relache_temps(void){
    teleplot_temps_fige = false;
}


void Teleplot_envoie_tampon(void){
    Teleplot_send_string();
    teleplot_tampon[0]='\0'; // On "vide" le tampon
}


void Teleplot_ajout_ou_envoie_tampon(char * message){
    // Si le tampon ne peut pas accueillir le prochain message
    // On envoie et on vide le tampon
    if(strlen(message) + strlen(teleplot_tampon) > BEACON_MSG_LEN_MAX){
        Teleplot_envoie_tampon();
    }
    // On ajoute le message au tampon
    strcat(teleplot_tampon, message);

}

void Teleplot_add_variable_float_2decimal(const char * nom_variable, float valeur){
    char tampon[100];
    sprintf(tampon, ">%s:%lu:%.2f\n", nom_variable, Teleplot_get_temps(), valeur);
    Teleplot_ajout_ou_envoie_tampon(tampon);
}

void Teleplot_add_variable_int(char * nom_variable, int valeur){
    char tampon[100];
    sprintf(tampon, ">%s:%lu:%d\n", nom_variable, Teleplot_get_temps(), valeur);
    Teleplot_ajout_ou_envoie_tampon(tampon);
}

void Teleplot_add_variable_2d(char * nom_variable, float x, float y){
    char tampon[100];
    sprintf(tampon, ">%s:%.2f:%.2f:%lu|xy\n", nom_variable, x, y, Teleplot_get_temps());
    Teleplot_ajout_ou_envoie_tampon(tampon);
}