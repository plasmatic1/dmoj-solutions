import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CountingSubsequences {
	static String s;
	static int[] dp, last = new int[26];
//	static boolean[] isnew;
	static int n;
	
//	@SuppressWarnings("rawtypes")
//	static ArrayList[] uses;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		s = br.readLine();
		n = s.length();
		dp = new int[n];
//		isnew = new boolean[n];
		
//		uses = new ArrayList[n];
//		for(int i = 0; i < n; i++){
//			uses[i] = new ArrayList<Integer>();
//		}
		
//		boolean[] used = new boolean[26];
//		
//		for(int i = 0; i < n; i++){
//			int v = s.charAt(i) - 'a';
////			if(!used[v]){
////				isnew[i] = used[v] = true;
////			}
//			
//			uses[v].add(i);
//		}
//		
//		for(int i = 0; i < n; i++){
//			System.out.println(((char)(i + 'a')) + " : " + uses[i]);
//		}
//		
		System.out.println(dp(n - 1) % 10007);
	}
	
	static int dp(int m){
		if(m == 0){
			return 1;
		}
		
		if(dp[m] == 0){
			int def = 2 * dp(m - 1), v = s.charAt(m) - 'a';
			
//			System.out.println(ind);
			
			if(last[v] == 0){
				def++;
			}
			else{
				def -= dp(last[v] - 1);
			}
			
//			System.out.println(def);
			
			dp[m] = def % 10007;
			last[v] = m;
		}
		
		return dp[m];
	}
}
