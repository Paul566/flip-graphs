#include <cmath>
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <unordered_map>
#include <deque>
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Spectra/SymEigsSolver.h>
#include <Spectra/MatOp/SparseSymMatProd.h>

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
            float ax, ay, bx, by, cx, cy;
            triangulation_file >> ax >> ay >> bx >> by >> cx >> cy;
            triangles.insert(Triangle(Point(ax, ay), Point(bx, by), Point(cx, cy)));
        }
    }

    triangulation_file.close();

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

                if (vertex_numbers.size() % 1000 == 0) {
                    std::cout << "visited " << vertex_numbers.size() << " vertices and " << edge_list.size() << " edges" << std::endl;
                }
            } else {
                edge_list.emplace_back(vertex_numbers[child], vertex_numbers[current_vertex]);
            }
        }
    }

    std::cout << "FOUND " << vertex_numbers.size() << " VERTICES AND " << edge_list.size() << " EDGES" << std::endl;

    return edge_list;
}

void ExportEdgeList(const std::vector<std::pair<int, int>>& edge_list, const std::string& path) {
    std::ofstream output(path);

    output << edge_list.size() << "\n";
    for (auto edge : edge_list) {
        output << edge.first << " " << edge.second << "\n";
    }

    output.close();
}

std::vector<std::pair<int, int>> ReadEdgeList(const std::string& path) {
    std::vector<std::pair<int, int>> edge_list;
    std::fstream edge_list_file(path);

    if (edge_list_file.is_open()) {
        int num_edges;
        edge_list_file >> num_edges;
        for (int i = 0; i < num_edges; ++i) {
            int from, to;
            edge_list_file >> from >> to;
            edge_list.emplace_back(from, to);
        }
    }

    edge_list_file.close();

    return edge_list;
}

std::vector<std::vector<int>> AdjList(const std::vector<std::pair<int, int>>& edge_list) {
    int num_vertices = 0;
    for (auto edge: edge_list) {
        if (num_vertices < edge.first) {
            num_vertices = edge.first;
        }
    }
    num_vertices++;

    std::vector<std::vector<int>> adj_list(num_vertices);
    for (auto edge: edge_list) {
        if (std::find(adj_list[edge.first].begin(), adj_list[edge.first].end(), edge.second) ==
            adj_list[edge.first].end()) {
            adj_list[edge.first].push_back(edge.second);
        }
        if (std::find(adj_list[edge.second].begin(), adj_list[edge.second].end(), edge.first) ==
            adj_list[edge.second].end()) {
            adj_list[edge.second].push_back(edge.first);
        }
    }

    return adj_list;
}

Eigen::SparseMatrix<float> NormalizedLaplacian(std::vector<std::vector<int>> adj_list) {
    int max_degree = 0;
    for (const auto &connections: adj_list) {
        if (max_degree < static_cast<int>(connections.size())) {
            max_degree = static_cast<int>(connections.size());
        }
    }

    int num_vertices = static_cast<int>(adj_list.size());
    Eigen::SparseMatrix<float> L(num_vertices, num_vertices);
    L.reserve(Eigen::VectorXi::Constant(L.cols(), max_degree + 1));
    for (int i = 0; i < num_vertices; i++) {
        L.insert(i, i) = 1;
        for (int to: adj_list[i]) {
            L.insert(i, to) = static_cast<float>(-1. / std::sqrt(adj_list[i].size() * adj_list[to].size()));
        }
    }

    return L;
}

float SpectralGap(const Eigen::SparseMatrix<float>& L) {
    Spectra::SparseSymMatProd<float> op(L);
    Spectra::SymEigsSolver<float, Spectra::SMALLEST_ALGE, Spectra::SparseSymMatProd<float>> eigs(&op, 2, 100);
    eigs.init();
    eigs.compute(100, 1e-7);

    auto two_eigenvalues = eigs.eigenvalues();
    std::cout << two_eigenvalues << std::endl;
    std::cout << "two smallest eigenvalues: " << two_eigenvalues(0) << " " << two_eigenvalues(1) << std::endl;
    float lambda2 = two_eigenvalues(0);
    return lambda2;
}

std::vector<float> Spectrum(const Eigen::SparseMatrix<float>& L) {
    Spectra::SparseSymMatProd<float> op(L);
    Spectra::SymEigsSolver<float, Spectra::LARGEST_ALGE, Spectra::SparseSymMatProd<float>> eigs(&op, L.cols() - 1, L.cols());
    eigs.init();
    eigs.compute();
    auto eigenvalues = eigs.eigenvalues();

    std::vector<float> spectrum(L.cols());
    for (int i = 0; i < L.cols() - 1; ++i) {
        spectrum[i] = eigenvalues(i);
    }
    spectrum[L.cols() - 1] = 0.;

    return spectrum;
}

void ExportGap(float spectral_gap, int num_vertices, const std::string& path) {
    std::ofstream output(path);

    output << "number of vertices:\n";
    output << num_vertices << "\n";
    output << "spectral gap:\n";
    output << spectral_gap;

    output.close();
}

void ExportSpectrum(const std::vector<float>& spectrum, const std::string& path) {
    std::ofstream output(path);

    for (float eigenvalue : spectrum) {
        output << eigenvalue << "\n";
    }

    output.close();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int i = 10; i <= 10; ++i) {
        std::string directory = "/home/paul/Documents/Experiments/flip-graphs/instances/uniform-" + std::to_string(i) + "/";

        /*
        std::cout << "reading the initial triangulation..." << std::endl;
        auto initial_triangulation = ReadInitialTriangulation(directory + "initial-triangulation");

        std::cout << "constructing the flip-graph..." << std::endl;
        auto edge_list = FlipGraphEdgeList(initial_triangulation);

        std::cout << "exporting the edge list..." << std::endl;
        ExportEdgeList(edge_list, directory + "edge-list");
        */

        auto edge_list = ReadEdgeList(directory + "edge-list");

        std::cout << "creating the adjacency list..." << std::endl;
        auto adj_list = AdjList(edge_list);

        std::cout << "creating the normalized Laplacian..." << std::endl;
        auto L = NormalizedLaplacian(adj_list);

        // std::cout << "computing the spectral gap..." << std::endl;
        // float gap = SpectralGap(L);
        // std::cout << gap << "\n";

        std::cout << "computing the spectrum..." << std::endl;
        auto spectrum = Spectrum(L);

        std::cout << "exporting spectral data..." << std::endl;
        // ExportGap(gap, static_cast<int>(adj_list.size()), directory + "gap");
        ExportSpectrum(spectrum, directory + "spectrum");
    }



    return 0;
}
