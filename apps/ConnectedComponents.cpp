//
// Created by victor on 6/20/22.
//

#include "../core/common/utils.h"
#include "../core/graphBolt/KickStarterEngine.h"
#include "../core/main.h"

// ======================================================================
// CCINFO
// ======================================================================
class CCInfo {
public:
  CCInfo() = default;

  void copy(const CCInfo &object) {}

  void processUpdates(edgeArray &edge_additions, edgeArray &edge_deletions) {}

  void cleanup() {}

  void init() {}
};

// ======================================================================
// VERTEXVALUE INITIALIZATION
// ======================================================================
template <class VertexValueType, class GlobalInfoType>
inline void initializeVertexValue(const uintV &v,
                                  VertexValueType &v_vertex_value,
                                  const GlobalInfoType &global_info) {
  v_vertex_value = v;
}

// ======================================================================
// ACTIVATE VERTEX FOR FIRST ITERATION
// ======================================================================
template <class GlobalInfoType>
inline bool frontierVertex(const uintV &v, const GlobalInfoType &global_info) {
  return true;
}

// ======================================================================
// EDGE FUNCTION
// ======================================================================
template <class VertexValueType, class EdgeDataType, class GlobalInfoType>
inline bool
edgeFunction(const uintV &u, const uintV &v, const EdgeDataType &edge_weight,
             const VertexValueType &u_value, VertexValueType &v_value,
             GlobalInfoType &global_info) {
//  std::cout << "edge " << u << "\t" << v << "\n";
  v_value = u_value;
  return true;
}

// ======================================================================
// SHOULDPROPAGATE
// ======================================================================
// shouldPropagate condition for deciding if the value change in
// updated graph violates monotonicity
template <class VertexValueType, class GlobalInfoType>
inline bool shouldPropagate(const VertexValueType &old_value,
                            const VertexValueType &new_value,
                            GlobalInfoType &global_info) {
//  std::cout << "prop " << old_value << "\t" << new_value << "\n";
  return new_value > old_value;
}

// ======================================================================
// HELPER FUNCTIONS
// ======================================================================
template <class GlobalInfoType>
void printAdditionalData(ofstream &output_file, const uintV &v,
                         GlobalInfoType &info) {}

// ======================================================================
// COMPUTE FUNCTION
// ======================================================================
template <class vertex> void compute(graph<vertex> &G, commandLine config) {
  CCInfo global_info {};

  cout << "Initializing engine ....\n";
  KickStarterEngine<vertex, uint16_t, CCInfo> engine(G, global_info, config);
  engine.init();
  cout << "Finished initializing engine\n";
  engine.run();
}
