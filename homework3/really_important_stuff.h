#pragma once
#include <iostream>
#include "pugixml.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

struct XY {
    double x, y;
};

class TS
{
public:
    std::string number, type_of_vehicle, name_stopping, the_official_name;
    std::vector <std::string> routes, location;
    XY coordinates;
};

std::vector<TS> Parsing();
void MaximumAmountOfRoutes(std::vector<TS> &tss);
void MaximumPathOfRoutes(std::vector<TS> &tss);
void Location(std::vector<TS> &tss);
