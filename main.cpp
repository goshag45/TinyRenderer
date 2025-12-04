#include <cmath>
#include <cstdlib>
#include <ctime>

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
    constexpr int width  = 64;
    constexpr int height = 64;

    TGAImage framebuffer(width, height, TGAImage::RGB);

    Verts2d verts2d("obj/diablo3_pose/diablo3_pose.obj");

    for (Verts2d::Face face : verts2d.getfaces()) {
        std::pair<float, float> a = verts2d.getverts()[face.v1 - 1];
        std::pair<float, float> b = verts2d.getverts()[face.v2 - 1];
        std::pair<float, float> c = verts2d.getverts()[face.v3 - 1];
        line(a.first , a.second, b.first, b.second, framebuffer, red);
        line(b.first, b.second, c.first, c.second, framebuffer, red);
        line(c.first, c.second, a.first, a.second, framebuffer, red);
    }
    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}
