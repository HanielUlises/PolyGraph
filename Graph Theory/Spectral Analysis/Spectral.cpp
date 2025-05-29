#ifndef SPECTRAL_GRAPH_HPP
#define SPECTRAL_GRAPH_HPP

#include <vector>
#include <functional>
#include <numeric>
#include <Eigen/Dense>

class SpectralGraph {
public:
    using Matrix = std::vector<std::vector<double>>;

    SpectralGraph(Matrix adj)
        : adjacency(std::move(adj)), size(adjacency.size()), laplacian(computeLaplacian(adjacency)) {}

    std::vector<double> eigenvalues() const {
        Eigen::MatrixXd L = toEigenMatrix(laplacian);
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(L);
        auto evals = solver.eigenvalues();

        std::vector<double> result(evals.size());
        std::transform(evals.data(), evals.data() + evals.size(), result.begin(),
                       [](double val) { return val; });
        return result;
    }

    static SpectralGraph from_edges(const std::vector<std::tuple<int, int, double>>& edges, int n) {
        Matrix adj(n, std::vector<double>(n, 0.0));
        for (const auto& [u, v, w] : edges) {
            adj[u][v] = w;
            adj[v][u] = w; // undirected
        }
        return SpectralGraph(adj);
    }

    const Matrix& getAdjacency() const { return adjacency; }
    const Matrix& getLaplacian() const { return laplacian; }

private:
    Matrix adjacency;
    Matrix laplacian;
    size_t size;

    static Matrix compute_laplacian(const Matrix& adj) {
        size_t n = adj.size();
        Matrix lap(n, std::vector<double>(n, 0.0));

        for (size_t i = 0; i < n; ++i) {
            double degree = std::accumulate(adj[i].begin(), adj[i].end(), 0.0);
            for (size_t j = 0; j < n; ++j) {
                if (i == j) lap[i][j] = degree;
                else lap[i][j] = -adj[i][j];
            }
        }
        return lap;
    }

    static Eigen::MatrixXd to_eigen_matrix(const Matrix& mat) {
        size_t n = mat.size();
        Eigen::MatrixXd emat(n, n);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                emat(i, j) = mat[i][j];
        return emat;
    }
};

#endif
