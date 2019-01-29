import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class GoldChainRule {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		int[] dist = new int[n], diste = new int[n];
		ArrayList<e>[] list = new ArrayList[n];
		
		for(int i = 0; i < n; i++){
			list[i] = new ArrayList<>();
		}
		Arrays.fill(dist, Integer.MAX_VALUE);
		Arrays.fill(diste, Integer.MAX_VALUE);
		
		for(int i = 0; i < m; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()),
					b = Integer.parseInt(token2.nextToken()),
					d = Integer.parseInt(token2.nextToken());
			list[a].add(new e(b, d));
			list[b].add(new e(a, d));
		}
		
		PriorityQueue<e> queue = new PriorityQueue<>();
		dist[0] = 0;
		
		//dijkstra #1
		
		for(int i = 0; i < n; i++){
			queue.add(new e(i, dist[i]));
		}
		
		while(!queue.isEmpty()){
			e v = queue.poll();
//			System.out.println("On: " + v);
			for(e adj : list[v.p]){
				int d = dist[v.p];
				int alt = d == Integer.MAX_VALUE ? d : d + adj.d;
				if(alt < dist[adj.p]){
					dist[adj.p] = alt;
//					queue.remove(adj);
					queue.add(new e(adj.p, alt));
				}
			}
		}
		
		//dijkstra #2
		diste[n - 1] = 0;
		
		for(int i = 0; i < n; i++){
			queue.add(new e(i, dist[i]));
		}
		
		while(!queue.isEmpty()){
			e v = queue.poll();
//			System.out.println("On: " + v);
			for(e adj : list[v.p]){
				int d = diste[v.p];
				int alt = d == Integer.MAX_VALUE ? d : d + adj.d;
				if(alt < diste[adj.p]){
					diste[adj.p] = alt;
//					queue.remove(adj);
					queue.add(new e(adj.p, alt));
				}
			}
		}
		
		//end
		
//		System.out.println(Arrays.toString(dist));
//		System.out.println(Arrays.toString(diste));
		
		int ans = -1;
		for(int i = 0; i < n; i++){
			int a = dist[i], b = diste[i];
			if(a == -1 || b == -1)
				break;
			ans = Math.max(ans, a + b);
		}
		
		System.out.println(ans);
	}
	
	static e point(int v){
		return new e(v, -1);
	}
	
	private static class e implements Comparable<e>{
		int p;
		int d;
		
		public e(int p, int d){
			this.p = p;
			this.d = d;
		}

		@Override
		public int compareTo(e arg0) {
			return Integer.compare(this.d, arg0.d);
		}
		
		@Override
		public boolean equals(Object other){
			if(!(other instanceof e)){
				return false;
			}
			return this.p == ((e)other).p;
		}
		
		@Override
		public String toString(){
			return "(P: " + this.p + " | D: " + this.d + ")";
		}
	}
}
