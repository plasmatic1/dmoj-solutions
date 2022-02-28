import java.io.*;
import java.util.*;

public class Main {
  static final int INF = 1000000000, MV = 100001;
  static final long LINF = 1000000000000000000L;
    public static void main(String[] args) throws IOException {
      int N = readInt(), W = readInt();
      long[] dp = new long[MV];
      for (int i = 1; i < MV; i++) dp[i] = LINF;

      for (int i = 0; i < N; i++) {
        int w = readInt(), v = readInt();
        for (int j = MV-1; j >= v; j--) { // loop backwards to avoid counting a single item multiple times
          dp[j] = Math.min(dp[j], dp[j-v] + w);
        }
      }

      int ans = 0;
      for (int i = 0; i < MV; i++)
        if (dp[i] <= W) // can make this knapsack
          ans = i;
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