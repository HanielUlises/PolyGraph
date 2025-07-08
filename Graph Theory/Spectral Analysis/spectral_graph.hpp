#ifndef SPECTRAL_GRAPH_HPP
#define SPECTRAL_GRAPH_HPP

#include <vector>
#include <tuple>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <queue>
#include <Eigen/Dense>
#include <Eigen/Sparse>

struct edge {
    int from;
    int to;
    double weight;

    edge(int f, int t, double w) : from(f), to(t), weight(w) {}
};

class SpectralGraph {
public:
    using matrix = std::vector<std::vector<double>>;
    using edge = std::tuple<int, int, double>;
    using vector = std::vector<double>;

    // Construct graph from adjacency matrix
    SpectralGraph(matrix adj, bool is_directed = false)
        : adjacency_(std::move(adj)), 
          size_(adjacency_.size()), 
          is_directed_(is_directed),
          laplacian_(compute_laplacian(adjacency_, is_directed)),
          degree_matrix_(compute_degree_matrix(adjacency_)) {
        validate_adjacency_matrix();
    }

    // Construct graph from edge list
    static SpectralGraph from_edges(const std::vector<edge>& edges, int n, bool is_directed = false) {
        matrix adj(n, std::vector<double>(n, 0.0));
        for (const auto& [u, v, w] : edges) {
            if (u < 0 || u >= n || v < 0 || v >= n) {
                throw std::out_of_range("Vertex index out of bounds");
            }
            if (w < 0) {
                throw std::invalid_argument("Negative edge weights not supported");
            }
            adj[u][v] = w;
            if (!is_directed) {
                adj[v][u] = w;
            }
        }
        return SpectralGraph(std::move(adj), is_directed);
    }

    // Compute eigenvalues of Laplacian matrix
    std::vector<double> eigenvalues() const {
        Eigen::MatrixXd L = to_eigen_matrix(laplacian_);
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(L);
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("Eigenvalue computation failed");
        }
        auto evals = solver.eigenvalues();
        std::vector<double> result(evals.size());
        std::copy(evals.data(), evals.data() + evals.size(), result.begin());
        std::sort(result.begin(), result.end());
        return result;
    }

    // Compute eigenvectors of Laplacian matrix
    std::vector<vector> eigenvectors() const {
        Eigen::MatrixXd L = to_eigen_matrix(laplacian_);
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(L);
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("Eigenvector computation failed");
        }
        auto evecs = solver.eigenvectors();
        std::vector<vector> result(size_);
        for (size_t i = 0; i < size_; ++i) {
            result[i].resize(size_);
            for (size_t j = 0; j < size_; ++j) {
                result[i][j] = evecs(j, i);
            }
        }
        return result;
    }

    // Compute algebraic connectivity (second smallest eigenvalue)
    double algebraic_connectivity() const {
        auto evals = eigenvalues();
        return evals.size() < 2 ? 0.0 : evals[1];
    }

    // Compute number of connected components
    size_t number_of_components() const {
        auto evals = eigenvalues();
        return std::count_if(evals.begin(), evals.end(), 
                            [](double val) { return std::abs(val) < 1e-10; });
    }

    // Compute normalized Laplacian matrix
    matrix normalized_laplacian() const {
        matrix norm_lap(size_, std::vector<double>(size_, 0.0));
        for (size_t i = 0; i < size_; ++i) {
            double deg_i = degree_matrix_[i][i];
            if (deg_i == 0.0) continue;
            for (size_t j = 0; j < size_; ++j) {
                if (i == j) {
                    norm_lap[i][j] = 1.0;
                } else if (adjacency_[i][j] != 0.0) {
                    double deg_j = degree_matrix_[j][j];
                    if (deg_j == 0.0) continue;
                    norm_lap[i][j] = -adjacency_[i][j] / std::sqrt(deg_i * deg_j);
                }
            }
        }
        return norm_lap;
    }

    // Check graph connectivity via BFS
    bool is_connected() const {
        if (size_ == 0) return true;
        std::vector<bool> visited(size_, false);
        std::queue<int> queue;
        queue.push(0);
        visited[0] = true;
        size_t count = 1;

        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            for (size_t v = 0; v < size_; ++v) {
                if (adjacency_[u][v] != 0.0 && !visited[v]) {
                    visited[v] = true;
                    queue.push(v);
                    ++count;
                }
            }
        }
        return count == size_;
    }

    // Get graph properties
    size_t vertex_count() const { return size_; }
    size_t edge_count() const {
        double total = 0.0;
        for (const auto& row : adjacency_) {
            total += std::accumulate(row.begin(), row.end(), 0.0);
        }
        return static_cast<size_t>(is_directed_ ? total : total / 2);
    }

    // Getters
    const matrix& get_adjacency() const { return adjacency_; }
    const matrix& get_laplacian() const { return laplacian_; }
    const matrix& get_degree_matrix() const { return degree_matrix_; }
    bool is_directed_graph() const { return is_directed_; }

private:
    matrix adjacency_;
    matrix laplacian_;
    matrix degree_matrix_;
    size_t size_;
    bool is_directed_;

    // Validate adjacency matrix properties
    void validate_adjacency_matrix() const {
        if (size_ == 0) {
            throw std::invalid_argument("Adjacency matrix cannot be empty");
        }
        for (const auto& row : adjacency_) {
            if (row.size() != size_) {
                throw std::invalid_argument("Adjacency matrix must be square");
            }
            for (double w : row) {
                if (w < 0) {
                    throw std::invalid_argument("Negative edge weights not supported");
                }
            }
        }
        if (!is_directed_) {
            for (size_t i = 0; i < size_; ++i) {
                for (size_t j = 0; j < size_; ++j) {
                    if (adjacency_[i][j] != adjacency_[j][i]) {
                        throw std::invalid_argument("Adjacency matrix must be symmetric for undirected graph");
                    }
                }
            }
        }
    }

    // Compute degree matrix D where D_{ii} = sum of weights of edges incident to vertex i
    static matrix compute_degree_matrix(const matrix& adj) {
        size_t n = adj.size();
        matrix deg(n, std::vector<double>(n, 0.0));
        for (size_t i = 0; i < n; ++i) {
            deg[i][i] = std::accumulate(adj[i].begin(), adj[i].end(), 0.0);
        }
        return deg;
    }

    // Compute Laplacian matrix L = D - A
    static matrix compute_laplacian(const matrix& adj, bool is_directed) {
        size_t n = adj.size();
        matrix lap(n, std::vector<double>(n, 0.0));
        for (size_t i = 0; i < n; ++i) {
            double degree = std::accumulate(adj[i].begin(), adj[i].end(), 0.0);
            for (size_t j = 0; j < n; ++j) {
                lap[i][j] = (i == j) ? degree : -adj[i][j];
            }
        }
        return lap;
    }

    // Convert matrix to Eigen format for spectral computations
    static Eigen::MatrixXd to_eigen_matrix(const matrix& mat) {
        size_t n = mat.size();
        Eigen::MatrixXd eigen_mat(n, n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                eigen_mat(i, j) = mat[i][j];
            }
        }
        return eigen_mat;
    }
};

// Sparse graph implementation for large-scale spectral analysis
class SparseSpectralGraph {
public:
    using sparse_matrix = Eigen::SparseMatrix<double>;

    SparseSpectralGraph(const std::vector<edge>& edges, int n, bool is_directed = false)
        : size_(n), is_directed_(is_directed) {
        std::vector<Eigen::Triplet<double>> triplets;
        for (const auto& [u, v, w] : edges) {
            if (u < 0 || u >= n || v < 0 || v >= n) {
                throw std::out_of_range("Vertex index out of bounds");
            }
            triplets.emplace_back(u, v, w);
            if (!is_directed) {
                triplets.emplace_back(v, u, w);
            }
        }

        adjacency_.resize(n, n);
        adjacency_.setFromTriplets(triplets.begin(), triplets.end());

        // Compute degree matrix D
        degree_matrix_.resize(n, n);
        std::vector<Eigen::Triplet<double>> deg_triplets;
        for (int i = 0; i < n; ++i) {
            double deg = 0.0;
            for (Eigen::SparseMatrix<double>::InnerIterator it(adjacency_, i); it; ++it) {
                deg += it.value();
            }
            deg_triplets.emplace_back(i, i, deg);
        }
        degree_matrix_.setFromTriplets(deg_triplets.begin(), deg_triplets.end());

        // Compute Laplacian L = D - A
        laplacian_ = degree_matrix_ - adjacency_;
    }

    // Compute eigenvalues of sparse Laplacian
    std::vector<double> eigenvalues() const {
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(laplacian_);
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("Eigenvalue computation failed");
        }
        auto evals = solver.eigenvalues();
        std::vector<double> result(evals.size());
        std::copy(evals.data(), evals.data() + evals.size(), result.begin());
        std::sort(result.begin(), result.end());
        return result;
    }

private:
    sparse_matrix adjacency_;
    sparse_matrix degree_matrix_;
    sparse_matrix laplacian_;
    size_t size_;
    bool is_directed_;
};

#endif