import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class TruckingTroubles2 {
	static ArrayList<e>[] matrix;
	static ArrayList<Integer> cities;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int c = Integer.parseInt(token.nextToken()), r = Integer.parseInt(token.nextToken()),
				d = Integer.parseInt(token.nextToken());
		
		matrix = new ArrayList[c];
		for(int i = 0; i < c; i++){
			matrix[i] = new ArrayList<>();
		}
		
		cities = new ArrayList<>(d);
		
		for(int i = 0; i < r; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()) - 1,
					b = Integer.parseInt(token2.nextToken()) - 1,
					w = Integer.parseInt(token2.nextToken());
			matrix[a].add(new e(b, w));
			matrix[b].add(new e(a, w));
		}
		
		for(int i = 0; i < d; i++){
			cities.add(Integer.parseInt(br.readLine()) - 1);
		}
		
		int[] mins = new int[c];
		Arrays.fill(mins, Integer.MIN_VALUE);
		
		Queue<Integer> next = new LinkedList<Integer>();
		
		next.add(0);

		while (!next.isEmpty()) {
			int curr = next.poll();
//			System.out.printf("Curr is ");
			
			for (e adj : matrix[curr]) {
				int minDist = mins[curr] < adj.d ? 
						(mins[curr] == Integer.MIN_VALUE ? adj.d : mins[curr]) :
							adj.d;
//				int minDist = Math.min(adj.d, mins[curr]);
				
				if(minDist > mins[adj.p]){
					mins[adj.p] = minDist;
					next.add(adj.p);
				}
			}
		}
		
		int min = Integer.MAX_VALUE;
		for(int city : cities){
			min = Math.min(mins[city], min);
		}
		
		System.out.println(min);
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