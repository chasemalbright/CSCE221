#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees) {
    // auto it = indegrees.begin();
    // while (it != indegrees.end()){
    //     for(T elementLabel : it->second.)
    // }
    for (size_type<T> i = 0; i < graph.size(); i++){
        indegrees[i] = 0;
    }

    for (size_type<T> i = 0; i < graph.size(); i++){
        for (size_type<T> j = 0; j < graph.size(i); j++){
            indegrees[j] = indegrees[j] +1;
        }
    }
}
