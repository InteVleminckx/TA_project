//
// Created by Maksim Karnaukh on 12/05/2021.
//

#ifndef PROJECTTA_ENGINE_H
#define PROJECTTA_ENGINE_H


#include "easy_image.h"
#include "ini_configuration.h"
#include "Lsysteem.h"
#include "L2Dsysteem.h"
#include "L3Dsysteem.h"
#include "ZBuffer.h"
#include "drawTriangles.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

img::EasyImage generate_2DImage(const ini::Configuration &configuration);

img::EasyImage generate_3DImage(const ini::Configuration &configuration);

img::EasyImage generate_image(const ini::Configuration &configuration);

void save_image(std::string iniFilename);


#endif //PROJECTTA_ENGINE_H
