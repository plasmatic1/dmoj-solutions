import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

public class PerfectTrees {
	static HashMap<Integer, Long> dp = new HashMap<>();
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		
		dp.put(1, 1L);
		dp.put(2, 1L);
		
		dp(n);
		
//		System.out.println(dp);
		
		if(n < 3){
			System.out.println(1);
		}
		else{
			System.out.println(dp.get(n));
		}
	}
	
	static long dp(int n){
//		if(n < 3){
//			return 1;
//		}
		
		if(dp.containsKey(n)){
			return dp.get(n);
		}
		
		long val = 0, k = n, next = 0;
		
	    while(k >= 2){
	    	long weight = n / k;
	    	
	    	next = n / (weight + 1);
	    	val += (k - next) * dp((int)weight);
	    	k = next;
	    }
		
		dp.put(n, val);
		
		return val;
	}
}