import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class GFSSOC2J5 {
	
	public static void main(String[] args) throws IOException {
		int N = readInt(), Q = readInt();
		int[][] psum = new int[11][N+1];
		for (int i = 1; i <= N; i++) {
			int x = readInt();
			psum[x][i]++;
			for (int j = 1; j <= 10; j++)
				psum[j][i] += psum[j][i-1];
		}
		
		while (Q-- > 0) {
			int a = readInt(), b = readInt();
			for (int i = 10; i >= 1; i--) {
				int cnt = psum[i][a-1] + psum[i][N] - psum[i][b];
				if (cnt > 0) {
					System.out.printf("%d %d\n", i, cnt);
					break;
				}
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
    	return Integer.parseInt(next());
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