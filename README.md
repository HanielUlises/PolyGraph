# PolyGraph

Computational geometry and graph theory in C++20. The project aims to become a
templated, header-only library: geometric primitives parameterized over the
coordinate field and the ambient dimension, and graph structures parameterized
over the node and edge-data types, so that predicates and algorithms are
instantiated rather than duplicated. The implementations follow the standard
academic literature closely: de Berg et al. on computational geometry,
Preparata and Shamos, O'Rourke on polygon triangulation, Chung on spectral
graph theory, and Edelsbrunner and Harer on computational topology. The source
is written to be read alongside it.

## Computational geometry

Everything lives in namespace `GeomCore`. Primitives are templates over a
coordinate type constrained by the concept `Real` (floating point) and a
compile-time dimension: `Vector<T, dim>`, `Point<T, dim>`, `Line`, `Plane`,
`Vertex<T, dim>`, `Polygon<T, dim>`, `Edge`.

- **Predicates.** Signed area of a triangle, orientation of a point triple, and
  the derived classification `RELATIVE_POSITION` (left, right, behind, beyond,
  between, origin, destination); collinearity and coplanarity via cross and
  triple products.
- **Intersection.** Segment–segment (proper and improper), line–line in the
  plane, line–plane and plane–plane in space.
- **Distance.** Point to line and point to plane, from the orthogonal
  decomposition of the connecting vector.
- **Angles.** Between two lines in R² and R³, between a line and a plane, and
  the dihedral angle between two planes.
- **Triangulation.** Ear clipping on simple polygons: a diagonal test built on
  the orientation predicate plus internal-visibility, yielding n−2 triangles in
  O(n²).

Exact arithmetic is not assumed; degeneracy is resolved against a fixed
tolerance, so the predicates are robust only up to that threshold.

## Graph theory

`graph<node_type, edge_data>` is an adjacency-list structure over any node type
satisfying `Hashable` and `EqualityComparable`, with a partial specialization
`graph<node_type, void>` for unweighted, unlabelled graphs.

Spectral analysis (`Spectral_Graph`, `Sparse_Spectral_Graph`) builds the
combinatorial Laplacian L = D − A and the normalized Laplacian
L_sym = D^(−1/2) L D^(−1/2) from a weighted adjacency matrix, and exposes the
spectrum via a self-adjoint eigensolver (Eigen). The multiplicity of the zero
eigenvalue counts connected components, and the second smallest eigenvalue,
the algebraic connectivity or Fiedler value, bounds the graph's expansion;
its eigenvector gives the standard spectral bipartition.

## Computational topology

Planned for the next iterations, built on the geometry primitives above:

- **Simplicial complexes.** A templated complex over abstract simplices, with
  boundary operators ∂_k and the chain groups they act on.
- **Homology.** Betti numbers β_k = dim ker ∂_k − rank ∂_(k+1), computed by
  reduction of the boundary matrices over a field.
- **Persistent homology.** Vietoris–Rips and Čech filtrations of a point cloud,
  the standard reduction algorithm for persistence pairs, and barcode /
  persistence-diagram output.
- **Alpha complexes.** Delaunay-based filtrations, once the triangulation
  module supports the incremental Delaunay construction.

## Status

Work in progress. Parts of the geometry module still carry separate translation
units; these are being folded back into headers as the templated interfaces
stabilize.
