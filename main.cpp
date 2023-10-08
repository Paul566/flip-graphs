#include <iostream>
#include <unordered_set>
#include <fstream>
#include <unordered_map>
#include <deque>

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

std::vector<std::pair<int, int>> FlipGraphEdgeList(Triangulation& initial_triangulation) {
    std::vector<std::pair<int, int>> edge_list;
    std::unordered_map<Triangulation, int, HashTriangulation> vertex_numbers;
    vertex_numbers[initial_triangulation] = 0;
    std::deque<Triangulation> queue;
    queue.push_back(initial_triangulation);
    while(!queue.empty()) {
        Triangulation current_vertex = queue.front();
        queue.pop_front();
        auto children = current_vertex.GetChildren();
        for (const auto& child : children) {
            if (vertex_numbers.find(child) == vertex_numbers.end()) {
                edge_list.emplace_back(vertex_numbers.size(), vertex_numbers[current_vertex]);
                vertex_numbers[child] = static_cast<int>(vertex_numbers.size());
                queue.push_back(child);
            } else {
                edge_list.emplace_back(vertex_numbers[child], vertex_numbers[current_vertex]);
            }
        }
    }
    return edge_list;
}

int main() {
    auto initial_triangulation = ReadInitialTriangulation("/home/paul/Documents/Experiments/flip-graphs/instances/convex-5/initial-triangulation");

    auto el = FlipGraphEdgeList(initial_triangulation);
    for (auto p : el) {
        std::cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
