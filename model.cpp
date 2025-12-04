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
                int v1, v2, v3;
                Face face = {v1, v2, v3};
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