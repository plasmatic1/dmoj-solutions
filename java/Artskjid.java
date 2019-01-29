import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Artskjid {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int c = Integer.parseInt(token.nextToken()), r = Integer.parseInt(token.nextToken());
		ArrayList<e>[] matrix = new ArrayList[c];
		
		for(int i = 0; i < c; i++){
			matrix[i] = new ArrayList<>();
		}
		for(int i = 0; i < r; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int s = Integer.parseInt(token2.nextToken()), d = Integer.parseInt(token2.nextToken()),
					l = Integer.parseInt(token2.nextToken());
			matrix[s].add(new e(d, l, 0));
		}
		
		int[][] dp = new int[c][1 << c];
		PriorityQueue<e> next = new PriorityQueue<>();
		next.add(new e(0, 0, 0));
		
		while(!next.isEmpty()){
			e curr = next.poll();
			int bitmask = curr.bitmask;
			System.out.println("Curr: " + curr);
			
			for(e adj : matrix[curr.v]){
				if((bitmask & (1 << adj.v)) == 0){
					System.out.println("    Searching adj " + adj);
					int newmask = bitmask | (1 << adj.v);
					int alt = adj.w + curr.w;
					
					if(alt > dp[adj.v][newmask]){
						dp[adj.v][newmask] = alt;
						next.add(new e(adj.v, alt, newmask));
					}
					
//					next.add(new e(adj.v, alt, newmask));
				}
			}
		}
		
		int[] fns = dp[c - 1];
		int l = fns.length, fnl = Integer.MIN_VALUE;
		for(int i = 0; i < l; i++){
			if(fns[i] > fnl){
				fnl = fns[i];
			}
		}
		
//		for(int i = 0; i < c; i++){
//			System.out.println(Arrays.toString(dp[i]));
//		}
		
		System.out.println(fnl);
		System.out.println(Arrays.toString(dp[c - 1]));
		
//		System.out.println(dp[c - 1][fns.length - 2]);
	}
	
	static class e implements Comparable<e>{
		public int v, w, bitmask;
		public e(int v0, int w0, int b0){
			v = v0;
			w = w0;
			bitmask = b0;
		}
		
		@Override
		public String toString(){
			return "(" + v + ", " + w + ") | " + Integer.toBinaryString(bitmask);
		}

		@Override
		public int compareTo(e o) {
			return -Integer.compare(w, o.w);
		}
	}
}
