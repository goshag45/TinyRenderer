#include <fstream>
#include <sstream>
#include <vector>

// shitfuck
class Verts2d {
private:
    std::vector<std::pair<float, float>> verts;
public:
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
            if (prefix == "v ") {
                float x, y;
                iss >> x >> y;
                verts.emplace_back(x, y);
            }
            if (prefix == "f ") {
                // todo
            }
        }
    }; 
};