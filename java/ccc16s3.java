import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
      int N = readInt(), K = readInt();
      boolean[] special = new boolean[N];
      ArrayList<Integer>[] g = new ArrayList[N];
      for (int i = 0; i < K; i++)
        special[readInt()] = true;
      for (int i = 0; i < N; i++) {
        g[i] = new ArrayList<Integer>();
      }
      for (int i = 1; i < N; i++) {
        int a = readInt(), b = readInt();
        g[a].add(b);
        g[b].add(a);
      }

      int[] dis1 = new int[N], dis2 = new int[N];
      
      int st = -1;
      for (int i = 0; i < N; i++)
        if (special[i])
          st = i;
      
      mark(st, -1, g, special);
      dfs(st, -1, g, special, dis1);
      int endpoint = -1, best = -1;
      for (int i = 0; i < N; i++) {
        if (dis1[i] > best) {
          endpoint = i;
          best = dis1[i];
        }
      }
      dfs(endpoint, -1, g, special, dis2);

      int nodecnt = 0, mx = 0;
      for (int i = 0; i < N; i++) {
        mx = Math.max(mx, dis2[i]);
        if (special[i])
          nodecnt++;
      }
      // System.out.printf("st=%d en=%d nc=%d mx=%d\n", st, endpoint, nodecnt, mx);

      System.out.println(2*(nodecnt-1) - mx);
    }

    static void mark(int c, int p, ArrayList<Integer>[] g, boolean[] special) {
      for (int to : g[c]) {
        if (to != p) {
          mark(to, c, g, special);
          special[c] |= special[to];
        }
      }
    }

    static void dfs(int c, int p, ArrayList<Integer>[] g, boolean[] special, int[] dis) {
      for (int to : g[c]) {
        if (to != p && special[to]) {
          dis[to] = dis[c] + 1;
          dfs(to, c, g, special, dis);
        }
      }
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