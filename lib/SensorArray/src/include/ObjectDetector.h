//
// Created by romain on 5/26/25.
//

#ifndef OBJECTDETECTOR_H
#define OBJECTDETECTOR_H
#include "SensorArray.h"


class ObjectDetector {

public:

    struct AnchorBox
    {
        //Top corner
        Point tc;
        //Lower Corner
        Point lc;

        /**
        * @brief Anchor box is used to detect point in certain areas
        * @param (Point) origin : The origin point of the hitbox
        * @param (double) x_size : Dimention on x-axis of the bouding box in mm, should be > 0
        * @param (double) y_size : Dimention on y-axis of the bouding box in mm, should be > 0
        * @param (double) z_size : Dimention on z-axis of the bouding box in mm, should be > 0
        */
        //AnchorBox(Point origin, double x_size, double y_size, double z_size);
        //bool contains(Point p) const;
    };

    struct Detector
    {
        AnchorBox box;

        //Last ping in ms
        uint64_t last_ping;

        bool wasInFOV;
    };

    /**
    * @brief Current driver version.
    * @param (AnchorBox) env : The table where the match occurs and where data should be processed
    */

    ObjectDetector(SensorArray *array, AnchorBox env);

    uint8_t Update();


private:
    SensorArray *sensors;
    AnchorBox arena;

    std::vector<Point> points;

    std::vector<Detector> detectors;

    uint8_t KeepArena();

};



#endif //OBJECTDETECTOR_H
