//
// Created by boris on 28/01/2025.
//

#include "Musique.h"


/**
 * @brief Déclare un nouveau buzzer sur un pin
 * @param pin pin du buzzer
 */
Musique::Musique(uint32_t pin) {
    _buzzerPin = pin;
    pinMode(_buzzerPin, OUTPUT);
    _buzzerVolume = 50;
}

/**
 * @brief Déclare un nouveau buzzer sur un pin et un volume par default
 * @param pin pin du buzzer
 * @param defaultVolume volume par default [0;255]
 */
Musique::Musique(uint32_t pin, uint8_t defaultVolume) {
    _buzzerPin = pin;
    pinMode(_buzzerPin, OUTPUT);
    _buzzerVolume = defaultVolume;
}

/**
 * @brief Sonne une tonalité pendant quelques secondes
 * @param tone Toalité
 * @param duration Temps de la tonalité en millis
 */
void Musique::beep(uint32_t tone, uint16_t duration) {
    analogWriteFrequency(tone);
    analogWrite(_buzzerPin, _buzzerVolume);
    delay(duration);
    analogWrite(_buzzerPin, 0);
}

/**
 * @brief Changement du volume du Buzzer
 * @param volume volume compris dans 0 & 255
 */
void Musique::setVolume(uint8_t volume) {
    _buzzerVolume = volume;
}

/**
 * @brief Lis une partition de musique
 * @param ToneTab tableau de la partition
 */
void Musique::playSheetMusic(const int16_t* ToneTab) {
    uint16_t nbNotes = ToneTab[0];
    uint16_t tempo = ToneTab[1];
    uint16_t wholenote = (60000 * ToneTab[2]) / tempo;

    for (int thisNote = 3; thisNote <= (nbNotes * 2)+3; thisNote = thisNote + 2) {
        uint16_t noteDuration = 0;
        // calculates the duration of each note
        int16_t divider = ToneTab[thisNote + 1];
        if (divider > 0) {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        if(ToneTab[thisNote]!=REST) {
            analogWriteFrequency(ToneTab[thisNote]);
            analogWrite(_buzzerPin, _buzzerVolume);
        }
        delay(noteDuration);
        analogWrite(_buzzerPin,0);
    }
}