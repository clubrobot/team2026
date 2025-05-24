// Teleplot
// Source: https://github.com/nesnes/teleplot

#ifndef TELEPLOT_H
#define TELEPLOT_H

#include <Arduino.h>
#include <Logger.h>

void Teleplot_send_string();
long Teleplot_get_temps(void);
void Teleplot_fige_temps(void);
void Teleplot_relache_temps(void);
void Teleplot_envoie_tampon(void);
void Teleplot_ajout_ou_envoie_tampon(char * message);
void Teleplot_ajout_ou_envoie_tampon(char * message);

void Teleplot_add_variable_float_2decimal(const char * nom_variable, float valeur);
void Teleplot_add_variable_int(char * nom_variable, int valeur);
void Teleplot_add_variable_2d(char * nom_variable, float x, float y);
//void Teleplot_add_status(char* )

#endif
