#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <type_traits>

// To use a directed graph, define DIRECTED_GRAPH before including this header.
// Otherwise, the graph will be undirected.
// Example: #define DIRECTED_GRAPH

// Note: NodeType must be hashable for std::unordered_map and std::unordered_set.

// Primary template for weighted graphs
template<typename node_type, typename edge_data>
class graph {
public:
    void add_node(const node_type& node);
    void remove_node(const node_type& node);
    void add_edge(const node_type& from, const node_type& to, const edge_data& data);
    void remove_edge(const node_type& from, const node_type& to);
    bool has_node(const node_type& node) const;
    bool has_edge(const node_type& from, const node_type& to) const;
    const std::unordered_map<node_type, edge_data>& get_adjacent(const node_type& node) const;
    const edge_data& get_edge_data(const node_type& from, const node_type& to) const;

private:
    std::unordered_map<node_type, std::unordered_map<node_type, edge_data>> adj_list;
};

// Specialization for unweighted graphs
template<typename node_type>
class graph<node_type, void> {
public:
    void add_node(const node_type& node);
    void remove_node(const node_type& node);
    void add_edge(const node_type& from, const node_type& to);
    void remove_edge(const node_type& from, const node_type& to);
    bool has_node(const node_type& node) const;
    bool has_edge(const node_type& from, const node_type& to) const;
    const std::unordered_set<node_type>& get_adjacent(const node_type& node) const;

private:
    std::unordered_map<node_type, std::unordered_set<node_type>> adj_list;
};

// Method definitions for weighted graphs
template<typename node_type, typename edge_data>
void graph<node_type, edge_data>::add_node(const node_type& node) {
    if (!adj_list.count(node)) {
        adj_list[node] = {};
    }
}

template<typename node_type, typename edge_data>
void graph<node_type, edge_data>::remove_node(const node_type& node) {
    adj_list.erase(node);
    for (auto& pair : adj_list) {
        pair.second.erase(node);
    }
}

template<typename node_type, typename edge_data>
void graph<node_type, edge_data>::add_edge(const node_type& from, const node_type& to, const edge_data& data) {
    adj_list[from][to] = data;
#ifndef DIRECTED_GRAPH
    adj_list[to][from] = data;
#endif
}

template<typename node_type, typename edge_data>
void graph<node_type, edge_data>::remove_edge(const node_type& from, const node_type& to) {
    if (adj_list.count(from)) {
        adj_list[from].erase(to);
    }
#ifndef DIRECTED_GRAPH
    if (adj_list.count(to)) {
        adj_list[to].erase(from);
    }
#endif
}

template<typename node_type, typename edge_data>
bool graph<node_type, edge_data>::has_node(const node_type& node) const {
    return adj_list.count(node) > 0;
}

template<typename node_type, typename edge_data>
bool graph<node_type, edge_data>::has_edge(const node_type& from, const node_type& to) const {
    auto it = adj_list.find(from);
    if (it == adj_list.end()) return false;
    return it->second.count(to) > 0;
}

template<typename node_type, typename edge_data>
const std::unordered_map<node_type, edge_data>& graph<node_type, edge_data>::get_adjacent(const node_type& node) const {
    return adj_list.at(node);
}

template<typename node_type, typename edge_data>
const edge_data& graph<node_type, edge_data>::get_edge_data(const node_type& from, const node_type& to) const {
    return adj_list.at(from).at(to);
}

// Method definitions for unweighted graphs
template<typename node_type>
void graph<node_type, void>::add_node(const node_type& node) {
    if (!adj_list.count(node)) {
        adj_list[node] = {};
    }
}

template<typename node_type>
void graph<node_type, void>::remove_node(const node_type& node) {
    adj_list.erase(node);
    for (auto& pair : adj_list) {
        pair.second.erase(node);
    }
}

template<typename node_type>
void graph<node_type, void>::add_edge(const node_type& from, const node_type& to) {
    adj_list[from].insert(to);
#ifndef DIRECTED_GRAPH
    adj_list[to].insert(from);
#endif
}

template<typename node_type>
void graph<node_type, void>::remove_edge(const node_type& from, const node_type& to) {
    if (adj_list.count(from)) {
        adj_list[from].erase(to);
    }
#ifndef DIRECTED_GRAPH
    if (adj_list.count(to)) {
        adj_list[to].erase(from);
    }
#endif
}

template<typename node_type>
bool graph<node_type, void>::has_node(const node_type& node) const {
    return adj_list.count(node) > 0;
}

template<typename node_type>
bool graph<node_type, void>::has_edge(const node_type& from, const node_type& to) const {
    auto it = adj_list.find(from);
    if (it == adj_list.end()) return false;
    return it->second.count(to) > 0;
}

template<typename node_type>
const std::unordered_set<node_type>& graph<node_type, void>::get_adjacent(const node_type& node) const {
    return adj_list.at(node);
}

#endif // GRAPH_H