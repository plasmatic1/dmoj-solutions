import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class FrankAndRoads {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int t = Integer.parseInt(token.nextToken()), n = Integer.parseInt(token.nextToken()) + 1,
				r = Integer.parseInt(token.nextToken()), f = Integer.parseInt(token.nextToken());
		int[] foodbasics = new int[f];
		ArrayList<e>[] matrix = new ArrayList[n];
		
		for(int i = 0; i < n; i++){
			matrix[i] = new ArrayList<>();
		}
		
		for(int i = 0; i < f; i++){
			foodbasics[i] = Integer.parseInt(br.readLine());
		}
		for(int i = 0; i < r; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()), b = Integer.parseInt(token2.nextToken()),
					c = Integer.parseInt(token2.nextToken());
			matrix[a].add(new e(b, c));
			//matrix[b].add(new e(a, c));
		}
		
		int[] dist = new int[n];
		boolean[] vis = new boolean[n];
		Arrays.fill(dist, Integer.MAX_VALUE);
		dist[0] = 0;
		
		PriorityQueue<e> queue = new PriorityQueue<>();
		
		for(int i = 0; i < n; i++){
			queue.add(new e(i, dist[i]));
		}
		
		while(!queue.isEmpty()){
			e v = queue.poll();
			
			if(vis[v.p] || v.d > dist[v.p]){
				continue;
			}
			
			vis[v.p] = true;
			for(e adj : matrix[v.p]){
				int alt = v.d == Integer.MAX_VALUE ? v.d : v.d + adj.d;
				if(alt < dist[adj.p]){
					dist[adj.p] = alt;
					queue.add(new e(adj.p, alt));
				}
			}
		}
		
		int total = 0;
		for(int store : foodbasics){
			if(dist[store] <= t){
				total++;
			}
		}
		System.out.println(total);
	}
	
	static e point(int v) {
		return new e(v, -1);
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
