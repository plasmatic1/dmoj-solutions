import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class CCC20S4 {
	static final int INF = 0x3f3f3f3f;
	static final char[][] PERM = new char[][] {
		{'A', 'B', 'C'},
		{'A', 'C', 'B'},
		{'B', 'A', 'C'},
		{'B', 'C', 'A'},
		{'C', 'A', 'B'},
		{'C', 'B', 'A'},
	};
	
	static int rq(int[][] pre, int c, int l, int r) {
		return pre[c][r] - pre[c][l-1];
	}
	
	public static void main(String[] args) throws IOException {
		String s = next();
		int N = s.length();
		
		int ans = INF;
		for (char[] p : PERM) {
			char[] repl = new char[N];
			for (int j = 0; j < N; j++) {
//				System.out.printf("shift=%s j=%d sj=%c let=%d\n", shift, j, shift.charAt(j), let(shift.charAt(j)));
				repl[j] = p[let(s.charAt(j))];
			}
			
			ans = Math.min(ans, solve(new String(repl)));
		}
		
		System.out.println(ans);
	}

	public static int solve(String s) {
		int N = s.length();
		
		int[][] pre = new int[3][N*2+1];
		s = s + s;
		for (int i = 1; i <= 2*N; i++) {
			for (int j = 0; j < 3; j++)
				pre[j][i] += pre[j][i-1];
			pre[let(s.charAt(i-1))][i]++;
		}
		
		int ans = INF;
		for (int i = N; i < 2*N; i++) {
			int l = i-N+1, r = i;
			int[][] want = new int[3][3];
			int[] cnt = new int[3];
			for (int j = 0; j < 3; j++) cnt[j] = rq(pre, j, l, r);
			for (int j = 0; j < 3; j++) {
				// all want[j][0] - idx 1..cnt[0]
				want[j][0] = rq(pre, j, l, l+cnt[0]-1);
				// all want[j][1] - idx cnt[0]+1, cnt[0]+cnt[1]
				want[j][1] = rq(pre, j, l+cnt[0], l+cnt[0]+cnt[1]-1);
				// all want[j][2] - idx cnt[0]+cnt[1]+1, cnt[0]+cnt[1]+cnt[2] (= r)
				want[j][2] = rq(pre, j, l+cnt[0]+cnt[1], l+cnt[0]+cnt[1]+cnt[2]-1);
				assert(l+cnt[0]+cnt[1]+cnt[2]-1 == r);
			}
			ans = Math.min(ans, greedy(want));
		}
		
		return ans;
	}
	
	static int let(char c) {
		return c - 'A';
	}
	
	static int greedy(int[][] want) {
		int swaps = 0;
		
		// +2 swaps
		for (int i = 0; i < 3; i++) {
			for (int j = i+1; j < 3; j++) {
				int sub = Math.min(want[i][j], want[j][i]);
				want[i][j] -= sub;
				want[j][i] -= sub;
				swaps += sub;
			}
		}
		// final swaps
		int rem = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (i != j)
					rem += want[i][j];
		assert(rem % 3 == 0);
		swaps += (rem / 3) * 2;
		
		return swaps;
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