//
// Created by romain on 5/26/25.
//

#include "include/ObjectDetector.h"

ObjectDetector::ObjectDetector(SensorArray *array, AnchorBox env)
{
    this->sensors = array;
    this->arena = env;
}
/*
ObjectDetector::AnchorBox::AnchorBox(Point origin, double x_size, double y_size, double z_size)
{
    this->lc = origin;
    this->tc = {.x = origin.x + abs(x_size), .y = origin.y + abs(y_size), .z = origin.z + abs(z_size)};
}


bool ObjectDetector::AnchorBox::contains(Point p) const
{
    return (p.x > this->lc.x && p.x < this->lc.x) || (p.y > this->lc.y && p.y < this->lc.y) || (p.z > this->lc.z && p.z < this->lc.z);
}*/

uint8_t Update()
{
    return 1;
}

uint8_t ObjectDetector::KeepArena()
{

    for (auto point : this->sensors->points)
    {
        /*if (this->arena.contains(point))
        {

        }*/
    }
    return 1;
}
