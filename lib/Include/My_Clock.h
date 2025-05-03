#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <Arduino.h>
#include <FreeRTOS.h>
#include <FreeRTOS/Source/include/task.h>

/** class Clock
 *  \brief Utilitaire pour gérer le temps dans vos programmes Arduino.
 *	\author Ulysse Darmet & Boris Hilkens
 *  est un outil permettant à vos programmes d'utiliser plus simplement la méthode micros() de <Arduino.h>.
 * Cette objet vous permettera de mesurer le temps écoulé depuis le dernier appel de la méthode Clock::restart .
 * 
 */

/**
 *@brief  initalise le compteur de cycle
 */
__STATIC_INLINE void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать счётчик
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; // запускаем счётчик
}
/**
 *@brief  Applique un delai en microsecondes
 */
__STATIC_INLINE void DWT_delay_us(uint32_t us) {
    uint32_t us_count_tic = us * (SystemCoreClock / 1000000U);
    DWT->CYCCNT = 0U;
    while (DWT->CYCCNT < us_count_tic);
}
/**
 *@brief  Renvoie la valeur du compteur de cycle en microsecondes
 *@return microsecondes convertie du compteur de cycle
 */
__STATIC_INLINE uint32_t DWT_micros(void) {
    return DWT->CYCCNT / (SystemCoreClock / 1000000U);
}
/**
 *@brief  Renvoie la valeur du compteur de cycle
 *@return compteur de cycle
 */
__STATIC_INLINE uint32_t DWT_value(void) {
    return DWT->CYCCNT ;
}

static void poly_delay(uint32_t ms) {
    if (xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
        delay(ms);
    } else {
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
}

class Clock {
private:
    unsigned long m_startTime; //!< temps en microsecondes du microcontroleur utilisé comme repère.
public:
    //! Constructeur de  Clock
    /*!
    * Le constructeur de Clock en plus de construire l'objet fait un premier marqueur qui vous permettra d'utiliser Clock::getElapsedTime pour avoir le temps écoulé depuis la création de l'objet.
    */
    Clock()
    :
    m_startTime(DWT_micros())
    {
    }

    //! Récupère le temps depuis le dernier reset.
    /*!
    * Récupère le temps écoulé en secondes depuis la construction de l'objet ou depuis le dernier Clock::restart.
    * \return Temps écoulé en secondes.
    */
    float getElapsedTime()
    {
        unsigned long currentTime = DWT_value();
        float elapsedTimeInSeconds = (currentTime - m_startTime)/ (SystemCoreClock / 1000000U) / float(1e6);
        if(currentTime<m_startTime) {
            unsigned long dp=-m_startTime;
            //printf("%lu \n",dp);
            elapsedTimeInSeconds=(currentTime + dp)/ (SystemCoreClock / 1000000U) / float(1e6);
        }
        return elapsedTimeInSeconds;
    }

    //! Reset le temps.
    /*!
    * Réinitialise le temps à 0s.
    * \return Temps écoulé en secondes depuis le dernier reset.
    */
    float restart()
    {
        unsigned long currentTime = DWT_value();
        float elapsedTimeInSeconds = (currentTime - m_startTime)/ (SystemCoreClock / 1000000U) / float(1e6);
        if(currentTime<m_startTime) {
            unsigned long dp=-m_startTime;
            //printf("%lu %lu %lu \n",dp,-m_startTime,m_startTime);
            elapsedTimeInSeconds=(currentTime + dp)/ (SystemCoreClock / 1000000U) / float(1e6);
        }
        m_startTime = currentTime;
        return elapsedTimeInSeconds;
    }
};


#endif // __CLOCK_H__
