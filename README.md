# SmartRoute: Optimizing Urban Navigation with Pathfinding Algorithms

This project demonstrates the efficiency and effectiveness of four advanced pathfinding algorithms in finding optimal routes between cities, considering factors such as distance and time:

- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Uniform Cost Search (UCS)
- A* Search

## Comparison: Chicago to Champaign Route

### Breadth-First Search (BFS)
- **Path:** Chicago → Joliet → Kankakee → Watseka → Hoopeston → Danville → Champaign
- **Distance:** 224 miles
- **Cities visited:** 35
- **Time taken:** 1,147,000 nanoseconds
- **Characteristics:**
  - Not an optimal solution (longer than UCS and A*)
  - Larger space occupied due to exploring all directions equally
  - Takes more time compared to other algorithms

### Depth-First Search (DFS)
- **Path:** Chicago → Aurora → Ottawa → Streator → Pontiac → Bloomington → Champaign
- **Distance:** 228 miles
- **Cities visited:** 18
- **Time taken:** 0 nanoseconds (likely due to measurement precision)
- **Characteristics:**
  - Non-optimal solution (longest path found)
  - Small space occupied as it explores deeply before backtracking
  - Potentially fastest execution (though timing seems inaccurate)

### Uniform Cost Search (UCS)
- **Path:** Chicago → Joliet → Morris → Dwight → Pontiac → Bloomington → Champaign
- **Distance:** 211 miles
- **Cities visited:** 44
- **Time taken:** 9,644,000 nanoseconds
- **Characteristics:**
  - Optimal solution (shortest path found)
  - Larger space occupied (visits some unwanted nodes)
  - Medium execution time

### A* Search
- **Path:** Chicago → Joliet → Morris → Dwight → Pontiac → Bloomington → Champaign
- **Distance:** 211 miles
- **Cities visited:** 39
- **Time taken:** 0 nanoseconds (likely due to measurement precision)
- **Characteristics:**
  - Optimal solution (matches UCS for shortest path)
  - Smaller space occupied compared to UCS (visits fewer unwanted nodes)
  - Potentially fastest execution among optimal algorithms (though timing seems inaccurate)

## Analysis

### Comparison
- BFS and DFS found non-optimal paths, while UCS and A* found the optimal (shortest) path.
- DFS visited the fewest cities, followed by A*, then BFS, with UCS visiting the most.
- UCS took the longest time, followed by BFS. DFS and A* timings are inconclusive due to measurement issues.

### Note on Timing
As C++ execution is very fast, we are running each algorithm 10 times to get more accurate timing in nanoseconds. However, the results for DFS and A* still show 0 nanoseconds, which suggests that the timing measurement might need further refinement or that these algorithms are executing extremely quickly for this particular graph.

## Conclusion

For this specific problem:
- If memory is a constraint and optimality is not required, DFS might be preferred.
- If guaranteed optimality is needed and extra time/space is acceptable, UCS is a solid choice.
- A* seems to offer the best balance, providing an optimal solution while visiting fewer cities than UCS. However, its timing needs verification.
- BFS, while simple to implement, doesn't offer any particular advantages for this weighted graph problem.
