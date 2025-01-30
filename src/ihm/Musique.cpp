//
// Created by boris on 28/01/2025.
//

#include "Musique.h"



Musique::Musique(uint32_t pin) {
    _buzzerPin = pin;
    pinMode(_buzzerPin, OUTPUT);
    _buzzerVolume = 50;
}

Musique::Musique(uint32_t pin, uint8_t defaultVolume) {
    _buzzerPin = pin;
    pinMode(_buzzerPin, OUTPUT);
    _buzzerVolume = defaultVolume;
}

void Musique::beep(uint32_t tone, uint16_t duration) {
    analogWriteFrequency(tone);
    analogWrite(_buzzerPin, _buzzerVolume);
    delay(duration);
    analogWrite(_buzzerPin, 0);
}

void Musique::setVolume(uint8_t volume) {
    _buzzerVolume = volume;
}

void Musique::playSheetMusic(const int16_t* ToneTab) {
    uint16_t nbNotes = ToneTab[0];
    uint16_t tempo = ToneTab[1];
    uint16_t wholenote = (60000 * ToneTab[2]) / tempo;

    for (int thisNote = 3; thisNote <= nbNotes * 2; thisNote = thisNote + 2) {
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