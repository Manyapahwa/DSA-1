class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        //number of rows in grid
        int n = grid.size();
        //number of columns in the grid 
        int m = grid[0].size(); 

        //queue stores the position of the rotten oranges and time ellapsed
        queue<pair<pair<int, int>, int>> q;

        
        vector<vector<int>> vis(n, vector<int>(m, 0));

        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) { 
                    q.push({{i, j}, 0}); 
                    vis[i][j] = 2; 
                } else {
                    vis[i][j] = 0; 
                }
            }
        }

        int tm = 0; 
        int drow[] = {-1, 0, +1, 0}; // Direction arrays for row movement (up, down, left, right)
        int dcol[] = {0, +1, 0, -1}; // Direction arrays for column movement

        // BFS loop
        while (!q.empty()) {
            int r = q.front().first.first; // Current row
            int c = q.front().first.second; // Current column
            int time = q.front().second; // Time elapsed for the current orange
            tm = max(tm, time); // Update the maximum time elapsed
            q.pop(); // Remove the processed element from the queue

            // Explore all 4-directionally adjacent cells
            for (int i = 0; i < 4; i++) {
                int nrow = r + drow[i]; 
                int ncol = c + dcol[i]; 

                // Check if the new position is valid, contains a fresh orange, and hasn't been visited
                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
                    vis[nrow][ncol] != 2 && grid[nrow][ncol] == 1) {
                    q.push({{nrow, ncol}, time + 1}); 
                    vis[nrow][ncol] = 2; // Mark the cell as visited (rotten)
                }
            }
        }

        // Check if there are any fresh oranges left
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (vis[i][j] != 2 && grid[i][j] == 1) {
                    return -1; // If a fresh orange is found, return -1 (impossible to rot all oranges)
                }
            }
        }

        return tm; // Return the total time required to rot all oranges
    }
};
