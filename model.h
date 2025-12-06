#include <fstream>
#include <sstream>
#include <vector>

class Verts2d {
public:
    struct Face { int v1, v2, v3; };
    Verts2d(std::string filename);
    std::vector<Face> getfaces() {  return faces; };
    std::vector<std::pair<float, float>> getverts() {   return verts; };
private:
    std::vector<std::pair<float, float>> verts;
    std::vector<Face> faces;
};