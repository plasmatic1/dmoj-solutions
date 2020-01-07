import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class SingleSourceShortestPath {
	static final int MAX = 1048576;
	static ArrayList<e>[] matrix;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		matrix = new ArrayList[n];
		
		for(int i = 0; i < n; i++){
			matrix[i] = new ArrayList<>();
		}
		for(int i = 0; i < m; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()) - 1
					,b = Integer.parseInt(token2.nextToken()) - 1,
					c = Integer.parseInt(token2.nextToken());
			
			matrix[a].add(new e(b, c));
			matrix[b].add(new e(a, c));
		}
		
//		for(int i = 0; i < n; i++){
//			for(int j = 0; j < n; j++){
//				System.out.printf("%d -> %d : %d\n", i, j, adj[i][j]);
//			}
//		}
//		
//		System.out.println();
//		System.out.println("done with input");
//		System.out.println();
		
		PriorityQueue<e> next = new PriorityQueue<e>();
		int[] dist = new int[n];
		Arrays.fill(dist, Integer.MAX_VALUE);
		next.add(new e(0, 0));
		dist[0] = 0;

		while (!next.isEmpty()) {
			e curr = next.poll();

			for (e adj : matrix[curr.v]) {
				int alt = curr.w + adj.w;
				
				if(alt < dist[adj.v]){
					dist[adj.v] = alt;
					next.add(new e(adj.v, alt));
				}
			}
		}
		
//		System.out.println(Arrays.toString(vis));
//		System.out.println(Arrays.toString(distance));
		
		for(int d : dist){
			if(d == Integer.MAX_VALUE){
				System.out.println(-1);
			}
			else{
				System.out.println(d);
			}
		}
	}
	
	static class e implements Comparable<e>{
		int v, w;
		
		public e(int v, int w){
			this.v = v;
			this.w = w;
		}

		@Override
		public int compareTo(e o) {
			return Integer.compare(this.w, o.w);
		}
	}
}