//
// Created by boris on 5/1/25.
//

#ifndef IHM_H
#define IHM_H

#include <Arduino.h>
#include <Buttons.h>

#define BLEU_BTN_PIN PC12
#define JAUNE_BTN_PIN PC8
#define VERT_BTN_PIN PD2
#define ROUGE_BTN_PIN PD4

#define BLEU_LED_PIN PG3
#define JAUNE_LED_PIN PG2
#define VERT_LED_PIN PD5
#define ROUGE_LED_PIN PC9

#define END_STOP_BAS_PIN PA5
#define TIRETTE_PIN PD2 //TEMP!


namespace ihm {
    void init();

    bool etat_bleu();
    bool etat_jaune();
    bool etat_vert();
    bool etat_rouge();
    bool etat_lim_bas();
    bool etat_tirette();

    void led_bleu(bool etat);
    void led_jaune(bool etat);
    void led_vert(bool etat);
    void led_rouge(bool etat);

    void led_bleu();///Toggles
    void led_jaune();///Toggles
    void led_vert();///Toggles
    void led_rouge();///Toggles
} // ihm

#endif //IHM_H
