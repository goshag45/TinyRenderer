#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "model.h"
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void line(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {
    bool steep = std::abs(ax-bx) < std::abs(ay-by);
    if (steep) { // if the line is steep, we transpose the image
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    if (ax>bx) { // make it left−to−right
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    int y = ay;
    float ierror = 0;
    for (int x=ax; x<=bx; x++) {
        if (steep) // if transposed, de−transpose
            framebuffer.set(y, x, color);
        else
            framebuffer.set(x, y, color);
        ierror += 2 * std::abs(by-ay);
        y += (by < ay ? 1 : -1)  * (ierror > bx - ax);
        ierror -= 2 * (bx - ax)  * (ierror > bx - ax);
    }
}

int main(int argc, char** argv) {
    constexpr int width  = 640;
    constexpr int height = 640;

    TGAImage framebuffer(width, height, TGAImage::RGB);

    Verts2d verts2d("obj/diablo3_pose/diablo3_pose.obj");
    std::cout << "verts: " << verts2d.getverts().size() << "\n";
    std::cout << "faces: " << verts2d.getfaces().size() << "\n";

    // need to convert coordinates!!!!
    for (Verts2d::Face face : verts2d.getfaces()) {
        std::pair<float, float> a = verts2d.getverts()[face.v1 - 1];
        std::pair<float, float> b = verts2d.getverts()[face.v2 - 1];
        std::pair<float, float> c = verts2d.getverts()[face.v3 - 1];
        a = std::pair((a.first+1.) * width/2, (a.second+1.) * height / 2);
        b = std::pair((b.first+1.) * width/2, (b.second+1.) * height / 2);
        c = std::pair((c.first+1.) * width / 2, (c.second+1.) * height / 2);
        line(a.first , a.second, b.first, b.second, framebuffer, red);
        line(b.first, b.second, c.first, c.second, framebuffer, red);
        line(c.first, c.second, a.first, a.second, framebuffer, red);
    }

    

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}
