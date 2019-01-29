import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class LineGraph {
	static ArrayList<e>[] matrix;
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), k = Integer.parseInt(token.nextToken());
		
		matrix = new ArrayList[n];
		for(int i = 0; i < n; i++){
			matrix[i] = new ArrayList<>();
		}
		
		StringTokenizer token2 = new StringTokenizer(br.readLine());
		for(int i = 0; i < n - 1; i++){
			int d = Integer.parseInt(token2.nextToken());
			
			matrix[i].add(new e(i + 1, d));
			matrix[i + 1].add(new e(i, d));
			
			if(i + k < n){
				matrix[i].add(new e(i + k, 0));
				matrix[i + k].add(new e(i, 0));
			}
		}
		
		//PRIMS ALGORITHM
		
		int[] mins = new int[n];
		boolean[] added = new boolean[n];
		PriorityQueue<e> next = new PriorityQueue<>();
		
		Arrays.fill(mins, Integer.MAX_VALUE);
		
		added[0] = true;
		mins[0] = 0;
		next.add(new e(0, 0));
		
		while(!next.isEmpty()){
			e curr = next.poll();
			
			for(e adj : matrix[curr.p]){
				if(added[adj.p]){
					continue;
				}
				
				mins[adj.p] = adj.d;
				next.add(adj);
			}
		}
	}
	
	private static class e implements Comparable<e> {
		int p;
		int d;

		public e(int p, int d) {
			this.p = p;
			this.d = d;
		}

		@Override
		public int compareTo(e arg0) {
			return Integer.compare(this.d, arg0.d);
		}

		@Override
		public boolean equals(Object other) {
			if (!(other instanceof e)) {
				return false;
			}
			return this.p == ((e) other).p;
		}

		@Override
		public String toString() {
			return "(P: " + this.p + " | D: " + this.d + ")";
		}
	}
}
