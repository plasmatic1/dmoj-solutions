import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class GreatSequence {
	static int n, k, q;
	static long seq[];
	static HashMap<Long, TreeSet<Integer>> nums = new HashMap<>();

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		
		//Input
		n = Integer.parseInt(token.nextToken());
		k = Integer.parseInt(token.nextToken());
		q = Integer.parseInt(token.nextToken());
		
		seq = new long[n + 1];
		StringTokenizer token2 = new StringTokenizer(br.readLine());
		for (int i = 1; i <= n; i++) {
			seq[i] = Integer.parseInt(token2.nextToken());
		}
		
		//Setting up data structs
		
		// Matcher
		for(int i = 1; i <= n; i++){
			TreeSet<Integer> set = nums.get(seq[i]);
			
			if(set == null){
				set = new TreeSet<>();
				set.add(i);
				nums.put(seq[i], set);
			}
			else{
				set.add(i);
			}
		}
		
		// Prefix sum array
		for (int i = 1; i <= n; i++) {
			seq[i] += seq[i - 1];
		}
		
		//Query solving
		
		for(int i = 0; i < q; i++){
			StringTokenizer token3 = new StringTokenizer(br.readLine());
			long a = Long.parseLong(token3.nextToken()), b = Long.parseLong(token3.nextToken());
			int x = Integer.parseInt(token3.nextToken()), y = Integer.parseInt(token3.nextToken());
			
			System.out.println(((seq[y] - seq[x - 1] > k) && 
					(contains(x, y, a) && contains(x, y, b))) ? "Yes" : "No");
		}
	}
	
	static boolean contains(int l, int r, long v){
		TreeSet<Integer> set = nums.get(v);
		if(set == null){
			return false;
		}
		
		return (set.floor(r) != null) && (l < set.floor(r));
	}
}