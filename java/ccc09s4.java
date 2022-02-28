import java.io.*;
import java.util.*;

public class Main {
  static final int INF = 1000000000;
    public static void main(String[] args) throws IOException {
        int N = readInt(), T = readInt();
        int[][] adj = new int[N][N];
        for (int i = 0; i < N; i++) {
          for (int j = 0; j < N; j++) {
            adj[i][j] = INF;
          }
        }
        for (int i = 0; i < T; i++) {
          int a = readInt()-1, b = readInt()-1, w = readInt();
          adj[a][b] = Math.min(adj[a][b], w);
          adj[b][a] = Math.min(adj[b][a], w);
        }
        int K = readInt();
        int[] extraCost = new int[N];
        for (int i = 0; i < N; i++) extraCost[i] = INF;
        for (int i = 0; i < K; i++) {
          int x = readInt()-1, w = readInt();
          extraCost[x] = Math.min(extraCost[x], w);
        }
        int D = readInt()-1;
        // dijkstra
        int[] dis = new int[N];
        Arrays.fill(dis, INF);
        boolean[] done = new boolean[N];
        dis[D] = 0;
        while (true) {
          int c = -1, best = INF;
          for (int i = 0; i < N; i++) {
            if (dis[i] < best && !done[i]) {
              best = dis[i];
              c = i;
            }
          }
          if (c == -1) break; // the queue is empty
          done[c] = true;
          for (int i = 0; i < N; i++) {
            int alt = dis[c] + adj[c][i];
            if (alt < dis[i]) {
              dis[i] = alt;
            }
          }
        }
        // compute answer
        int ans = INF;
        for (int i = 0; i < N; i++)
          ans = Math.min(ans, dis[i] + extraCost[i]);
        System.out.println(ans);
    }
    
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) st = new StringTokenizer(br.readLine().trim());
        return st.nextToken();
    }
    static long readLong() throws IOException {
        return Long.parseLong(next());
    }
    static int readInt() throws IOException {
        return Integer.parseInt(next()) ;
    }
    static short readShort() throws IOException{
        return Short.parseShort(next());
    }
    static double readDouble() throws IOException {
        return Double.parseDouble(next());
    }
    static char readCharacter() throws IOException {
        return next().charAt(0);
    }
    static String readLine() throws IOException {
        return br.readLine().trim();
    }
}