#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "model.h"

// shitfuck

Verts2d::Verts2d(std::string filename) {
    std::cout << "WORKING" << '\n';
    std::ifstream file(filename);

    // ok copilot fine i will throw an error
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        std::cout << "Line prefix: '" << prefix << "'\n";

        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            verts.emplace_back(x, y);
            std::cout << "Added vertex: " << x << ", " << y << "\n";
        }

        if (prefix == "f") {
            std::string s1, s2, s3;
            iss >> s1 >> s2 >> s3;

            auto parseIndex = [](const std::string& token) {
                return std::stoi(token.substr(0, token.find('/')));
            };

            Face face;
            face.v1 = parseIndex(s1);
            face.v2 = parseIndex(s2);
            face.v3 = parseIndex(s3);
            faces.push_back(face);
            std::cout << "Added face: " << face.v1 << ", " << face.v2 << ", " << face.v3 << "\n";
        }
    }
};