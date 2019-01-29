import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Contagion {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int c = Integer.parseInt(br.readLine());
		ArrayList<e>[] matrix = new ArrayList[c];
		for (int i = 0; i < c; i++) {
			matrix[i] = new ArrayList<>();
		}
		p[] cities = new p[c];
		
		for(int i = 0; i < c; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token.nextToken()), b = Integer.parseInt(token.nextToken());
			cities[i] = new p(a, b);
		}
		
		for(int i = 0; i < c; i++){
			for(int j = i; j < c; j++){
				if(j == i){
					continue;
				}
				p og = cities[i], other = cities[j];
				int dX = other.x - og.x, dY = other.y - og.y, dS = dX * dX + dY * dY;
				matrix[i].add(new e(j, dS));
				matrix[j].add(new e(i, dS));
			}
		}
		//
		
//		for (int i = 0; i < c; i++) {
//			System.out.println(matrix[i]);
//		}
		
		
		//
		
		int[] dist = new int[c];
		PriorityQueue<e> next = new PriorityQueue<>();
		
		int begin = Integer.parseInt(br.readLine()) - 1;
		
		Arrays.fill(dist, Integer.MAX_VALUE);
		dist[begin] = 0;
		
		for (int i = 0; i < c; i++) {
			next.add(new e(i, dist[i]));
		}
		
		while(!next.isEmpty()){
			e curr = next.poll();
			
			if(curr.d > dist[curr.p]){
				continue;
			}
			
			for(e adj : matrix[curr.p]){
				int alt = dist[curr.p] == Integer.MAX_VALUE ? Integer.MAX_VALUE : dist[curr.p] + adj.d;
				if(alt < dist[adj.p]){
					dist[adj.p] = alt;
					next.add(new e(adj.p, alt));
				}
			}
		}
		
//		System.out.println(Arrays.toString(dist));
		
		Arrays.sort(dist);
		
//		System.out.println(Arrays.toString(dist));
		
		int qc = Integer.parseInt(br.readLine());
		for(int i = 0; i < qc; i++){
			int q = Integer.parseInt(br.readLine()), max = 1;
			
			if(q >= dist[c - 1]){
				System.out.println(c);
				continue;
			}
			
			for(int j = 1; j < c; j++){
				if(q < dist[j]){
					break;
				}
				max++;
			}
			
			System.out.println(max);
		}
	}
	
	private static class p{
		public int x;
		public int y;
		
		public p(int x, int y){
			this.x = x;
			this.y = y;
		}
		
		@Override
		public boolean equals(Object other){
			if(other instanceof p){
				p otherr = (p)other;
				return this.x == otherr.x && this.y == otherr.y;
			}
			return false;
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
