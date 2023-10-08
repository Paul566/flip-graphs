#include <iostream>
#include <unordered_set>
#include <fstream>

#include "Triangulation.h"
#include "Triangle.h"
#include "Point.h"

Triangulation ReadInitialTriangulation(const std::string& path) {
    std::unordered_set<Triangle, HashTriangle> triangles;
    std::fstream triangulation_file(path);

    if (triangulation_file.is_open()) {
        int num_triangles;
        triangulation_file >> num_triangles;
        for (int i = 0; i < num_triangles; ++i) {
            double ax, ay, bx, by, cx, cy;
            triangulation_file >> ax >> ay >> bx >> by >> cx >> cy;
            triangles.insert(Triangle(Point(ax, ay), Point(bx, by), Point(cx, cy)));
        }
    }

    return Triangulation(triangles);
}


int main() {
    auto tr = ReadInitialTriangulation("/home/paul/Documents/Experiments/flip-graphs/instances/convex-5/initial-triangulation");

    auto children = tr.GetChildren();

    std::cout << children.size() << "\n";

    return 0;
}
