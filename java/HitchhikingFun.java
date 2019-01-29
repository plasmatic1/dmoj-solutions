import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class HitchhikingFun {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		ArrayList<e>[] list = new ArrayList[n];
		int[] dist = new int[n], prev = new int[n];
		boolean[] vis = new boolean[n];
//		int totaldist = 0, last = -1;
		
		for(int i = 0; i < n; i++){
			list[i] = new ArrayList<>();
		}
		Arrays.fill(dist, Integer.MAX_VALUE);
		Arrays.fill(prev, -1);
		
		for(int i = 0; i < m; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()) - 1,
					b = Integer.parseInt(token2.nextToken()) - 1,
					d = Integer.parseInt(token2.nextToken());
			
			list[a].add(new e(b, d));
			list[b].add(new e(a, d));
		}
		
		PriorityQueue<e> queue = new PriorityQueue<>();
		dist[0] = 0;
		
		for(int i = 0; i < n; i++){
			queue.add(new e(i, dist[i]));
		}
		
		while(!queue.isEmpty()){
			e v = queue.poll();
			if(vis[v.p]){
				continue;
			}
			vis[v.p] = true;
			for(e adj : list[v.p]){
				int d = dist[v.p];
				int alt = d == Integer.MAX_VALUE ? d : d + adj.d;
				if(alt < dist[adj.p]){
					dist[adj.p] = alt;
					prev[adj.p] = v.p;
//					prev[adj.p]++;
//					queue.remove(adj);
					queue.add(new e(adj.p, alt));
				}
			}
		}
		
		int totaldist = 0, curr = n - 1;
		for(int i = 0; i < n; i++){
			int prevv = prev[curr];
			totaldist++;
			
			if(prevv == -1){
				System.out.println(-1);
				break;
			}
			if(prevv == 0){
				System.out.printf("%d %d\n", dist[n - 1], totaldist);
				break;
			}
			
			curr = prevv;
		}
		
//		int totaldist = prev[n - 1];
//		if(totaldist == 0){
//			System.out.println(-1);
//		}
//		else{
//			System.out.printf("%d %d\n", dist[n - 1], totaldist);
//		}
		
//		System.out.println(Arrays.toString(prev));
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
