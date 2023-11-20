#ifndef BFS_GENERATOR
#define BFS_GENERATOR

#include "transportation_matrix.cpp"
class BFS_Generator {
public:
  virtual void generate_bfs(TransportationMatrix &matrix) = 0;
};

#endif // !BFS_GENERATOR
