import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class BridgeCrossing {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int m = Integer.parseInt(br.readLine());
		
		int[] p = new int[m + n + 2], dp = new int[m + n + 2], par = new int[m + n + 2];
		String[] names = new String[m + 2];
		
		for(int i = 1; i <= m; i++){
			String name = br.readLine();
			int v = Integer.parseInt(br.readLine());
			
			names[i] = name;
			p[i] = v;
		}
		
		par[0] = -1;
		Arrays.fill(dp, Integer.MAX_VALUE);
		dp[0] = 0;
		for (int i = 0; i <= m; i++) {
//			System.out.printf("i=%d dp[i]=%d\n", i, dp[i]);
			
			for (int j = i + 1; j <= i + n; j++) {
				int alt = dp[i] + maxOf(p, i + 1, j + 1);
				
				if(alt < dp[j]){
					dp[j] = alt;
					par[j] = j - i;
				}
			}
		}
		
//		System.out.println(Arrays.toString(dp));
//		System.out.println(Arrays.toString(par));
		
		System.out.printf("Total Time: %d\n", dp[m]);
		
		//
		
		ArrayList<ArrayList<String>> bestgroup = new ArrayList<>();
		bestgroup.add(new ArrayList<>());
		int curri = m, cgi = 0;
		while(par[curri] != -1){
			for(int i = curri - par[curri] + 1; i <= curri; i++){
				bestgroup.get(cgi).add(names[i]);
			}
			
			curri -= par[curri];
			
			cgi++;
			bestgroup.add(new ArrayList<>());
		}
		
		// 
		
		Collections.reverse(bestgroup);
		for (int i = 1; i < bestgroup.size(); i++) {
			System.out.println(String.join(" ", bestgroup.get(i)));
		}
	}
	
	// Too lazy for segment tree
	static int maxOf(int[] a, int l, int r){
		int max = 0;
		
		for(int i = l; i < r; i++){
			max = Math.max(max, a[i]);
		}
		
		return max;
	}
}
