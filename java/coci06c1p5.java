import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Bond {
	static int n, p[][];
	static double[] dp;
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		p = new int[n][n];
		dp = new double[1 << n];
		for(int i = 0; i < n; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			for(int j = 0; j < n; j++){
				p[i][j] = Integer.parseInt(token.nextToken());
			}
		}
		Arrays.fill(dp, -1e10);
		System.out.println(f(0, 0) * 100.0);
	}
	
	static double f(int a, int mask){
		if(dp[mask] >= 0){
			return dp[mask];
		}
		
		if(a > n - 1){
			return 1.0;
		}
		
		for(int i = 0; i < n; i++){
			if((mask & (1 << i)) == 0){
				dp[mask] = Math.max(dp[mask], f(a + 1, mask | (1 << i)) * (p[a][i] / 100.0));
			}
		}
		
		return dp[mask];
	}
}
