#include <iostream>
#include <vector>
#include <iomanip>
#include "spectral_graph.hpp"

void print_matrix(const SpectralGraph::matrix& matrix, const std::string& label) {
    std::cout << label << ":\n";
    for (const auto& row : matrix) {
        for (double value : row) {
            std::cout << std::fixed << std::setprecision(2) << std::setw(8) << value << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Print vector with fixed precision
void print_vector(const std::vector<double>& vector, const std::string& label) {
    std::cout << label << ": ";
    for (double value : vector) {
        std::cout << std::fixed << std::setprecision(4) << value << " ";
    }
    std::cout << "\n\n";
}

int main() {
    try {
        // Undirected graph with SpectralGraph::edge
        std::vector<SpectralGraph::edge> edges = {
            {0, 1, 1.0}, {1, 2, 2.0}, {2, 0, 1.5}, {2, 3, 1.0}
        };
        int vertex_count = 4;
        SpectralGraph graph = SpectralGraph::from_edges(edges, vertex_count);

        print_matrix(graph.get_adjacency(), "Adjacency Matrix");
        print_matrix(graph.get_laplacian(), "Laplacian Matrix");
        print_matrix(graph.get_degree_matrix(), "Degree Matrix");
        print_matrix(graph.normalized_laplacian(), "Normalized Laplacian");

        auto eigenvalues = graph.eigenvalues();
        print_vector(eigenvalues, "Laplacian Eigenvalues");

        auto eigenvectors = graph.eigenvectors();
        for (size_t i = 0; i < eigenvectors.size(); ++i) {
            std::cout << "Eigenvector " << i + 1 << ": ";
            for (double value : eigenvectors[i]) {
                std::cout << std::fixed << std::setprecision(4) << value << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";

        std::cout << "Vertex count: " << graph.vertex_count() << "\n";
        std::cout << "Edge count: " << graph.edge_count() << "\n";
        std::cout << "Algebraic connectivity: " << std::fixed << std::setprecision(4)
                  << graph.algebraic_connectivity() << "\n";
        std::cout << "Connected components: " << graph.number_of_components() << "\n";
        std::cout << "Is connected: " << (graph.is_connected() ? "Yes" : "No") << "\n\n";

        // Directed graph
        std::vector<SpectralGraph::edge> directed_edges = {
            {0, 1, 1.0}, {1, 2, 1.0}, {2, 0, 1.0}
        };
        SpectralGraph directed_graph = SpectralGraph::from_edges(directed_edges, 3, true);
        print_matrix(directed_graph.get_adjacency(), "Directed Graph Adjacency Matrix");
        print_vector(directed_graph.eigenvalues(), "Directed Graph Laplacian Eigenvalues");

        try {
            std::vector<SpectralGraph::edge> invalid_edges = {{0, 1, -1.0}};
            SpectralGraph invalid_graph = SpectralGraph::from_edges(invalid_edges, 2);
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }

        // Sparse graph using global edge type
        std::vector<edge> large_edges;
        int large_vertex_count = 100;
        for (int i = 0; i < large_vertex_count - 1; ++i) {
            large_edges.emplace_back(i, i + 1, 1.0);
        }
        SparseSpectralGraph sparse_graph(large_edges, large_vertex_count);
        auto sparse_eigenvalues = sparse_graph.eigenvalues();
        std::cout << "Sparse Graph Eigenvalues (first 5): ";
        for (size_t i = 0; i < std::min<size_t>(5, sparse_eigenvalues.size()); ++i) {
            std::cout << std::fixed << std::setprecision(4) << sparse_eigenvalues[i] << " ";
        }
        std::cout << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}