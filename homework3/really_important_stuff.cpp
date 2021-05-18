#include "really_important_stuff.h"

//fixed very much copy-paste
//fixed use range-based for
//fixed dont use first second: auto [x, y]

std::vector<std::string> CreateArr(std::string r) {
    std::replace(r.begin(), r.end(), '.', ',');
    std::vector<std::string> add;
    std::string str;
    for (int j = 0; j < r.size(); j++) {
        if (r[j] == ',') {
            add.push_back(str);
            str = "";
        } else {
            str += r[j];
        }
    }
    add.push_back(str);
    return add;
}

std::string RemovingSpaces (std::string str) {
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}


std::vector<TS> Parsing() {
    system("chcp 65001");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("new_data.xml");
    if (!result) std::cout << -1;
    pugi::xml_node stations = doc.child("dataset");
    std::vector <TS> TSs;
    for (pugi::xml_node i = stations.first_child(); i; i = i.next_sibling()) {
        TS tss;
        tss.number = RemovingSpaces((std::string) i.child_value("number"));
        tss.type_of_vehicle = i.child_value("type_of_vehicle");
        tss.name_stopping = RemovingSpaces((std::string) i.child_value("name_stopping"));;
        tss.the_official_name = RemovingSpaces((std::string) i.child_value("the_official_name"));
        tss.routes = CreateArr(RemovingSpaces((std::string) i.child_value("routes")));
        std::string str = i.child_value("location");
        std::string r;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == ',') {
                tss.location.push_back(r);
                i++;
                r = "";
            } else {
                r += str[i];
            }
        }
        tss.location.push_back(r);
        str = i.child_value("coordinates");
        r = "";
        int k;
        for (int j = 0; j < str.size(); j++) {
            if (str[j] == ',') {
                k = j + 1;
                break;
            } else {
                r += str[j];
            }
        }
        str.substr(k);
        tss.coordinates.x =std::stod(r);
        tss.coordinates.y = std::stod(str);
        TSs.push_back(tss);
    }
    return TSs;
}

std::string MaxAmOfRoutes(std::vector <TS> &tss, std::string typeOfVehicle) {
    std::vector <std::string> nameForRoute;
    std::vector <int> amountOfStoppings;
    for (auto ts: tss) {
        if (ts.type_of_vehicle == typeOfVehicle) {
            for (auto route: ts.routes) {
                if (std::find(nameForRoute.begin(), nameForRoute.end(), route) == nameForRoute.end()) {
                    nameForRoute.push_back(route);
                    amountOfStoppings.push_back(1);
                }
                else {
                    int t = std::find(nameForRoute.begin(), nameForRoute.end(), route) - nameForRoute.begin();
                    amountOfStoppings[t]++;
                }
            }
        }
    }
    int max = 0;
    std::string ans;
    for (int i = 0; i < amountOfStoppings.size(); i++) {
        if (amountOfStoppings[i] > max) {
            ans = nameForRoute[i];
            max = amountOfStoppings[i];
        }
    }
    return ans;
}

void MaximumAmountOfRoutes(std::vector<TS> &tss) {
    std::cout << "Маршрут автобуса с наибольшим количеством остановок " << MaxAmOfRoutes(tss, "Автобус") << std::endl;
    std::cout << "Маршрут трамвая с наибольшим количеством остановок " << MaxAmOfRoutes(tss, "Трамвай") << std::endl;
    std::cout << "Маршрут троллейбуса с наибольшим количеством остановок " << MaxAmOfRoutes(tss, "Троллейбус") << std::endl;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2,  2));
}

std::string MaxPathOfRoutes(std::vector <TS> &tss, std::string typeOfVehicle) {
    std::vector <std::string> nameForRoute;
    std::vector <std::vector <XY>> coords;
    for (auto ts: tss) {
        if (ts.type_of_vehicle == typeOfVehicle) {
            for (auto route: ts.routes) {
                auto iter = std::find(nameForRoute.begin(), nameForRoute.end(), route);
                if (iter == nameForRoute.end()) {
                    nameForRoute.push_back(route);
                    coords.resize(nameForRoute.size());
                    coords[nameForRoute.size() - 1].push_back(ts.coordinates);
                } else {
                    int t = iter - nameForRoute.begin();
                    coords[t].push_back(ts.coordinates);
                }
            }
        }
    }
    std::string ans;
    double dist = 0;
    for (int i = 0; i < nameForRoute.size(); i++) {
        double currDist = 0;
        for (int j = 0; j < coords[i].size() - 1; j++) {
            currDist += distance(coords[i][j].x, coords[i][j].y, coords[i][j + 1].x, coords[i][j + 1].y);
        }
        if (currDist > dist) {
            dist = currDist;
            ans = nameForRoute[i];
        }
    }
    return ans;
}

void MaximumPathOfRoutes(std::vector<TS> &tss) {
    std::cout << "Наиболее длинный маршрут у автобуса с номером " << MaxPathOfRoutes(tss, "Автобус") << std::endl;
    std::cout << "Наиболее длинный маршрут у трамвая с номером " << MaxPathOfRoutes(tss, "Трамвай") << std::endl;
    std::cout << "Наиболее длинный маршрут у троллейбуса с номером " << MaxPathOfRoutes(tss, "Троллейбус") << std::endl;
}

void Location(std::vector<TS> &tss) {
    std::vector <std::string> nameForLocation;
    std::vector <int> numberOfStoppings;
    for (auto ts: tss) {
        if (ts.location[0] != "") {
            for (auto location: ts.location) {
                if (std::find(nameForLocation.begin(), nameForLocation.end(), location) == nameForLocation.end()) {
                    nameForLocation.push_back(location);
                    numberOfStoppings.push_back(1);
                } else {
                    int t = std::find(nameForLocation.begin(), nameForLocation.end(), location) - nameForLocation.begin();
                    numberOfStoppings[t]++;
                }
            }
        }
    }
    int max = 0;
    std::string ans;
    for (int i = 0; i < nameForLocation.size(); i++) {
        if (numberOfStoppings[i] > max) {
            max = numberOfStoppings[i];
            ans = nameForLocation[i];
        }
    }
    std::cout << "Улица с наибольшим количеством остановок: " << ans;
}
