import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class dpd {
	
	public static void main(String[] args) throws IOException {
		int N = readInt(), W = readInt();
		long[] dp = new long[W+1];
		
		for (int i = 0; i < N; i++) {
			int w = readInt(), v = readInt();
			for (int j = W; j >= w; j--)
				dp[j] = Math.max(dp[j], dp[j - w] + v);
		}
		
		System.out.println(dp[W]);
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