//
// Created by boris on 5/1/25.
//

#include "ihm.h"

#include <FreeRTOS.h>
#include <My_Clock.h>
#include <FreeRTOS/Source/include/task.h>

static LedButton bleu = LedButton(BLEU_BTN_PIN, INPUT_PULLUP, BLEU_LED_PIN);
static LedButton jaune = LedButton(JAUNE_BTN_PIN, INPUT_PULLUP, JAUNE_LED_PIN);
static LedButton vert = LedButton(VERT_BTN_PIN, INPUT_PULLUP, VERT_LED_PIN);
static LedButton rouge = LedButton(ROUGE_BTN_PIN, INPUT_PULLUP, ROUGE_LED_PIN);
static Buttons endstop_bas = Buttons(END_STOP_BAS_PIN, INPUT_PULLUP);
static Buttons tirette = Buttons(TIRETTE_PIN, INPUT_PULLUP);

void ihm::init(){
    pinMode(POMPE_PIN, OUTPUT);
}


bool ihm::etat_bleu(){return bleu.getState();}
bool ihm::etat_jaune(){return jaune.getState();}
bool ihm::etat_vert(){return vert.getState();}
bool ihm::etat_rouge(){return rouge.getState();}
bool ihm::etat_lim_bas(){return endstop_bas.getState();}
bool ihm::etat_tirette(){return tirette.getState();}

void ihm::set_pompe(bool state){
    if (state==HIGH){
        portENTER_CRITICAL();
        for (int i=0; i<1023; i++){
            analogWrite(POMPE_PIN, i);
            poly_delay(1);
        }
        portEXIT_CRITICAL();
    }else{
        analogWrite(POMPE_PIN, 0);
    }
}


void ihm::led_bleu(bool etat){bleu.setLedState(etat);}
void ihm::led_jaune(bool etat){jaune.setLedState(etat);}
void ihm::led_vert(bool etat){vert.setLedState(etat);}
void ihm::led_rouge(bool etat){rouge.setLedState(etat);}

void ihm::led_bleu(){bleu.toggleLedState();}
void ihm::led_jaune(){jaune.toggleLedState();}
void ihm::led_vert(){vert.toggleLedState();}
void ihm::led_rouge(){rouge.toggleLedState();}