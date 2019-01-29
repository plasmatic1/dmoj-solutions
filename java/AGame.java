import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class AGame {
	static int[][] dp;
	static int[] coins;
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		dp = new int[n][n];
		coins = new int[n];
		
		StringTokenizer token = new StringTokenizer(br.readLine());
		for(int i = 0; i < n; i++){
			coins[i] = Integer.parseInt(token.nextToken());
		}
		
		System.out.println(dp(1, n - 1));
	}
	
	static int dp(int l, int r){
		if(l == r){
			return coins[r];
		}
		
		if(dp[l][r] == 0){
			dp[l][r] = (coins[r] - coins[l - 1]) - Math.min(dp(l + 1, r), dp(l, r - 1));
		}
		
		return dp[l][r];
	}
}
