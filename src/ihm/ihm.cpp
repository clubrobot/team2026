//
// Created by boris on 5/1/25.
//

#include "ihm.h"

static LedButton bleu = LedButton(BLEU_BTN_PIN, INPUT_PULLUP, BLEU_LED_PIN);
static LedButton jaune = LedButton(JAUNE_BTN_PIN, INPUT_PULLUP, JAUNE_LED_PIN);
static LedButton vert = LedButton(VERT_BTN_PIN, INPUT_PULLUP, VERT_LED_PIN);
static LedButton rouge = LedButton(ROUGE_BTN_PIN, INPUT_PULLUP, ROUGE_LED_PIN);

bool ihm::etat_bleu(){return bleu.getState();}
bool ihm::etat_jaune(){return jaune.getState();}
bool ihm::etat_vert(){return vert.getState();}
bool ihm::etat_rouge(){return rouge.getState();}

void ihm::led_bleu(bool etat){bleu.setLedState(etat);}
void ihm::led_jaune(bool etat){jaune.setLedState(etat);}
void ihm::led_vert(bool etat){vert.setLedState(etat);}
void ihm::led_rouge(bool etat){rouge.setLedState(etat);}

void ihm::led_bleu(){bleu.toggleLedState();}
void ihm::led_jaune(){jaune.toggleLedState();}
void ihm::led_vert(){vert.toggleLedState();}
void ihm::led_rouge(){rouge.toggleLedState();}