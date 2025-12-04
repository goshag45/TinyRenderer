#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// shitfuck
class Verts2d {
public:
    struct Face {
        int v1, v2, v3;
    };
    
    Verts2d(std::string filename) {
        std::ifstream file(filename);

        // ok copilot fine i will throw an error
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                float x, y;
                iss >> x >> y;
                verts.emplace_back(x, y);
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
            }
        }
    }; 

    std::vector<Face> getfaces() { return faces; }
    std::vector<std::pair<float, float>> getverts() { return verts; }

private:
    std::vector<std::pair<float, float>> verts;
    std::vector<Face> faces;
};