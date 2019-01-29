import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class MigrantMascot {
	static ArrayList<e>[] matrix;
	static int[] dist;
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		matrix = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			matrix[i] = new ArrayList<>();
		}
		dist = new int[n];
		
		for(int i = 0; i < m; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()) - 1,
					b = Integer.parseInt(token2.nextToken()) - 1,
					d = Integer.parseInt(token2.nextToken()) * -1;
			matrix[a].add(new e(b, d));
			matrix[b].add(new e(a, d));
		}
		
		Arrays.fill(dist, Integer.MIN_VALUE);
		dist[0] = 0;
		
		search(0, new HashSet<>());
		
		for (int i = 0; i < n; i++) {
			System.out.println(dist[i]);
		}
	}
	
	@SuppressWarnings("unchecked")
	static void search(int curr, HashSet<Integer> vis){
		vis.add(curr);
		
		for(e adj : matrix[curr]){
			if(vis.contains(adj.p)){
				continue;
			}
			
			int total = dist[curr] + adj.d;
			System.out.printf("Curr: %d, total %d, before %d\n", curr, total, dist[adj.p]);
			if(total > dist[adj.p]){
				total = dist[adj.p];
				search(adj.p, (HashSet<Integer>)vis.clone());
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
