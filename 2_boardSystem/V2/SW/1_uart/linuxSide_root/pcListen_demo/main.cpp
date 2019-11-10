//
// Created by alfyhack on 09/11/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "../src/DataTransfertPackge/DataPrimitive.h"
#include "../../DataTransfertPackge/DataManipolation/SpeedMot.h"

DataPrimitive::data2Ard d;
DataPrimitive::mSpeed speed;
DataManipolation::SpeedMot *Speed;

int main(int argc, char *argv[]) {
    d.up.speed[0] = 5;
    Speed = new DataManipolation::SpeedMot(speed);
    Speed->printSpeed();
    std::cout << "hello world" << version_D << "\n";
    return 0;
}