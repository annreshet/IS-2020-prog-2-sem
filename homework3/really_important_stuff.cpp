#include "really_important_stuff.h"

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
        tss.coordinates = std::make_pair(std::stod(r), std::stod(str));
        TSs.push_back(tss);
    }
    return TSs;
}



void MaximumAmountOfRoutes(std::vector<TS> &tss) {
    std::vector <std::string> nameForRoute_Bus;
    std::vector <std::string> nameForRoute_Tram;
    std::vector <std::string> nameForRoute_Trolley;
    std::vector <int> numberOfStoppings_Bus;
    std::vector <int> numberOfStoppings_Tram;
    std::vector <int> numberOfStoppings_Trolley;
    for (int i = 0; i < tss.size(); i++) {
        if (tss[i].type_of_vehicle == "Автобус") {
            for (int j = 0; j < tss[i].routes.size(); j++) {
                if (std::find(nameForRoute_Bus.begin(), nameForRoute_Bus.end(), tss[i].routes[j]) == nameForRoute_Bus.end()) {
                    nameForRoute_Bus.push_back(tss[i].routes[j]);
                    numberOfStoppings_Bus.push_back(1);
                }
                else {
                    int t = std::find(nameForRoute_Bus.begin(), nameForRoute_Bus.end(), tss[i].routes[j]) - nameForRoute_Bus.begin();
                    numberOfStoppings_Bus[t]++;
                }
            }
        }
        if (tss[i].type_of_vehicle == "Трамвай") {
            for (int j = 0; j < tss[i].routes.size(); j++) {
                if (std::find(nameForRoute_Tram.begin(), nameForRoute_Tram.end(), tss[i].routes[j]) == nameForRoute_Tram.end()) {
                    nameForRoute_Tram.push_back(tss[i].routes[j]);
                    numberOfStoppings_Tram.push_back(1);
                }
                else {
                    int t = std::find(nameForRoute_Tram.begin(), nameForRoute_Tram.end(), tss[i].routes[j]) - nameForRoute_Tram.begin();
                    numberOfStoppings_Tram[t]++;
                }
            }
        }
        if (tss[i].type_of_vehicle == "Троллейбус") {
            for (int j = 0; j < tss[i].routes.size(); j++) {
                if (std::find(nameForRoute_Trolley.begin(), nameForRoute_Trolley.end(), tss[i].routes[j]) == nameForRoute_Trolley.end()) {
                    nameForRoute_Trolley.push_back(tss[i].routes[j]);
                    numberOfStoppings_Trolley.push_back(1);
                }
                else {
                    int t = std::find(nameForRoute_Trolley.begin(), nameForRoute_Trolley.end(), tss[i].routes[j]) - nameForRoute_Trolley.begin();
                    numberOfStoppings_Trolley[t]++;
                }
            }
        }
    }
    int max = 0;
    std::string ans_Bus;
    std::string ans_Tram;
    std::string ans_Trolley;
    for (int i = 0; i < numberOfStoppings_Bus.size(); i++) {
        if (numberOfStoppings_Bus[i] > max) {
            ans_Bus = nameForRoute_Bus[i];
            max = numberOfStoppings_Bus[i];
        }
    }
    max = 0;
    for (int i = 0; i < numberOfStoppings_Tram.size(); i++) {
        if (numberOfStoppings_Tram[i] > max) {
            ans_Tram = nameForRoute_Tram[i];
            max = numberOfStoppings_Tram[i];
        }
    }
    max = 0;
    for (int i = 0; i < numberOfStoppings_Trolley.size(); i++) {
        if (numberOfStoppings_Trolley[i] > max) {
            ans_Trolley = nameForRoute_Trolley[i];
            max = numberOfStoppings_Trolley[i];
        }
    }
    std::cout << "Маршрут автобуса с наибольшим количеством остановок " << ans_Bus << std::endl;
    std::cout << "Маршрут трамвая с наибольшим количеством остановок " << ans_Tram << std::endl;
    std::cout << "Маршрут троллейбуса с наибольшим количеством остановок " << ans_Trolley << std::endl;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2,  2));
}

void MaximumPathOfRoutes(std::vector<TS> &tss) {
    std::vector <std::string> nameForRoute_Bus;
    std::vector <std::string> nameForRoute_Tram;
    std::vector <std::string> nameForRoute_Trolley;
    std::vector <std::vector <std::pair <double, double>>> coordsForBus;
    std::vector <std::vector <std::pair <double, double>>> coordsForTram;
    std::vector <std::vector <std::pair <double, double>>> coordsForTrolley;
    for (int i = 0; i < tss.size(); i++) {
        if (tss[i].type_of_vehicle == "Автобус") {
            for (int j = 0; j < tss[i].routes.size(); j++) {
                auto iter = std::find(nameForRoute_Bus.begin(), nameForRoute_Bus.end(), tss[i].routes[j]);
                if (iter == nameForRoute_Bus.end()) {
                    nameForRoute_Bus.push_back(tss[i].routes[j]);
                    coordsForBus.resize(nameForRoute_Bus.size());
                    coordsForBus[nameForRoute_Bus.size() - 1].push_back(tss[i].coordinates);
                } else {
                    int t = iter - nameForRoute_Bus.begin();
                    coordsForBus[t].push_back(tss[i].coordinates);
                }
            }
        }
        if (tss[i].type_of_vehicle == "Трамвай") {
            for (int j = 0; j < tss[i].routes.size(); j++) {
                auto iter = std::find(nameForRoute_Tram.begin(), nameForRoute_Tram.end(), tss[i].routes[j]);
                if (iter == nameForRoute_Tram.end()) {
                    nameForRoute_Tram.push_back(tss[i].routes[j]);
                    coordsForTram.resize(nameForRoute_Tram.size());
                    coordsForTram[nameForRoute_Tram.size() - 1].push_back(tss[i].coordinates);
                } else {
                    int t = iter - nameForRoute_Tram.begin();
                    coordsForTram[t].push_back(tss[i].coordinates);
                }
            }
        }
        if (tss[i].type_of_vehicle == "Троллейбус") {
            for (int j = 0; j < tss[i].routes.size(); j++) {
                auto iter = std::find(nameForRoute_Trolley.begin(), nameForRoute_Trolley.end(), tss[i].routes[j]);
                if (iter == nameForRoute_Trolley.end()) {
                    nameForRoute_Trolley.push_back(tss[i].routes[j]);
                    coordsForTrolley.resize(nameForRoute_Trolley.size());
                    coordsForTrolley[nameForRoute_Trolley.size() - 1].push_back(tss[i].coordinates);
                } else {
                    int t = iter - nameForRoute_Trolley.begin();
                    coordsForTrolley[t].push_back(tss[i].coordinates);
                }
            }
        }
    }
    std::string ansForBus, ansForTram,ansForTrolley;
    double distOfBus = 0;
    double distOfTram = 0;
    double distOfTrolley = 0;
    for (int j = 0; j < nameForRoute_Bus.size(); j++) {
        std::sort(coordsForBus[j].begin(), coordsForBus[j].end());
        double currDist = 0;
        for (int k = 0; k < coordsForBus[j].size() - 1; k++) {
            currDist += distance(coordsForBus[j][k].first, coordsForBus[j][k].second, coordsForBus[j][k + 1].first, coordsForBus[j][k + 1].second);
        }
        if (currDist > distOfBus) {
            distOfBus = currDist;
            ansForBus = nameForRoute_Bus[j];
        }
    }
    for (int j = 0; j < nameForRoute_Tram.size(); j++) {
        std::sort(coordsForTram[j].begin(), coordsForTram[j].end());
        double currDist = 0;
        for (int k = 0; k < coordsForTram[j].size() - 1; k++) {
            currDist += distance(coordsForTram[j][k].first, coordsForTram[j][k].second, coordsForTram[j][k + 1].first, coordsForTram[j][k + 1].second);
        }
        if (currDist > distOfTram) {
            distOfTram = currDist;
            ansForTram = nameForRoute_Tram[j];
        }
    }
    for (int j = 0; j < nameForRoute_Trolley.size(); j++) {
        std::sort(coordsForTrolley[j].begin(), coordsForTrolley[j].end());
        double currDist = 0;
        for (int k = 0; k < coordsForTrolley[j].size() - 1; k++) {
            currDist += distance(coordsForTrolley[j][k].first, coordsForTrolley[j][k].second, coordsForTrolley[j][k + 1].first, coordsForTrolley[j][k + 1].second);
        }
        if (currDist > distOfTrolley) {
            distOfTrolley = currDist;
            ansForTrolley = nameForRoute_Trolley[j];
        }
    }
    std::cout << "Наиболее длинный маршрут у автобуса с номером " << ansForBus << std::endl;
    std::cout << "Наиболее длинный маршрут у трамвая с номером " << ansForTram << std::endl;
    std::cout << "Наиболее длинный маршрут у троллейбуса с номером " << ansForTrolley << std::endl;
}

void Location(std::vector<TS> &tss) {
    std::vector <std::string> nameForLocation;
    std::vector <int> numberOfStoppings;
    for (int i = 0; i < tss.size(); i++) {
        if (tss[i].location[0] != "") {
            for (int j = 0; j < tss[i].location.size(); j++) {
                if (std::find(nameForLocation.begin(), nameForLocation.end(), tss[i].location[j]) == nameForLocation.end()) {
                    nameForLocation.push_back(tss[i].location[j]);
                    numberOfStoppings.push_back(1);
                } else {
                    int t = std::find(nameForLocation.begin(), nameForLocation.end(), tss[i].location[j]) - nameForLocation.begin();
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
    std::cout << "Улица с наибольшим количеством остановок: " << ans << std::endl;
}