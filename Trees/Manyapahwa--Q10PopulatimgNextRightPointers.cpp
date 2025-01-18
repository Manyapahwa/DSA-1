#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Directions (right, left, down, up)
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        // Priority queue to simulate a Dijkstra-like approach
        // It stores (cost, x, y) where cost is the current cost to reach (x, y)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        
        // Cost matrix initialized to infinity
        vector<vector<int>> cost(m, vector<int>(n, INT_MAX));
        cost[0][0] = 0;
        
        // Start from the top-left corner (0, 0)
        pq.push({0, 0, 0});
        
        while (!pq.empty()) {
            auto [curCost, x, y] = pq.top();
            pq.pop();
            
            // If we reached the bottom-right corner, return the cost
            if (x == m - 1 && y == n - 1) {
                return curCost;
            }
            
            // If the current cost is already higher than the stored cost, skip
            if (curCost > cost[x][y]) continue;
            
            // Try moving in all 4 directions
            for (int i = 0; i < 4; i++) {
                int nx = x + directions[i].first;
                int ny = y + directions[i].second;
                
                // Check if the next move is within bounds
                if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                    int newCost = curCost + (grid[x][y] != i + 1);  // If the direction doesn't match, cost + 1
                    if (newCost < cost[nx][ny]) {
                        cost[nx][ny] = newCost;
                        pq.push({newCost, nx, ny});
                    }
                }
            }
        }
        
        return -1;  // If no valid path exists (which shouldn't happen as per the problem description)
    }
};
