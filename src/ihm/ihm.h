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

#define END_STOP_BAS_PIN PE5
#define END_STOP_HAUT_PIN PE4
#define TIRETTE_PIN PA5


namespace ihm {
    void init();

    /** @brief blue button state
     * @return true if blue button is pressed, false otherwise
     */
    bool etat_bleu();
    /** @brief yellow button state
     * @return true if yellow button is pressed, false otherwise
     */
    bool etat_jaune();
    /** @brief green button state
     * @return true if green button is pressed, false otherwise
     */
    bool etat_vert();
    /** @brief red button state
     * @return true if red button is pressed, false otherwise
     */
    bool etat_rouge();

    bool etat_lim_haut();
    bool etat_lim_bas();
    /** @brief tirette state
     * @return true if tirette is pulled, false otherwise
     */
    bool etat_tirette();

    /// @brief set blue led state
    void led_bleu(bool etat);
    /// @brief set yellow led state
    void led_jaune(bool etat);
    /// @brief set green led state
    void led_vert(bool etat);
    /// @brief set blue led state
    void led_rouge(bool etat);

    /// @brief toggle blue led
    void led_bleu();
    /// @brief toggle yellow led
    void led_jaune();
    /// @brief toggle green led
    void led_vert();
    /// @brief toggle red led
    void led_rouge();

} // ihm

#endif //IHM_H
