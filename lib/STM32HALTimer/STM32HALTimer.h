//
// Created by awing on 6/28/26.
//

#ifndef TEAM2026_STM32HALTIMER_H
#define TEAM2026_STM32HALTIMER_H
#include <Arduino.h>
#include "Components/AbstractTimer.h"

class STM32HALTimer : public AbstractTimer {
public:
    explicit STM32HALTimer(TIM_HandleTypeDef* htim) : htim(htim) {}

    [[nodiscard]] unsigned long getCounter() const override {
        return __HAL_TIM_GET_COUNTER(htim);
    }
private:
    TIM_HandleTypeDef* htim;

};

#endif // TEAM2026_STM32HALTIMER_H
