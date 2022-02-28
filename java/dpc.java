import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class dpc {
	
	public static void main(String[] args) throws IOException {
		int N = readInt();
		int[][] H = new int[N+1][3], dp = new int[N+1][3];
		
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < 3; j++)
				H[i][j] = readInt();
		}
		
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					if (k != j)
						dp[i][j] = Math.max(dp[i][j], dp[i-1][k] + H[i][j]);
		}
		
		int ans = Math.max(dp[N][0], Math.max(dp[N][1], dp[N][2]));
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