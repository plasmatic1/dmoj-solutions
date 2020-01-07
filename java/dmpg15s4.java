import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class SignalHill {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int b = Integer.parseInt(token.nextToken()), q = Integer.parseInt(token.nextToken());
		e[] beacons = new e[b];
		for(int i = 0; i < b; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(token2.nextToken()), y = Integer.parseInt(token2.nextToken()),
					d = Integer.parseInt(token2.nextToken());
			beacons[i] = new e(x, y, d);
		}
		
		ArrayList<Integer>[] matrix = new ArrayList[b];
		for(int i = 0; i < b; i++){
			matrix[i] = new ArrayList<>();
		}
		
		for(int i = 0; i < b; i++){
			for(int j = i; j < b; j++){
				e first = beacons[i], second = beacons[j];
				int dx = second.x - first.x, dy = second.y - first.y;
				double dist = Math.sqrt(dx * dx + dy * dy);
				
				if(first.d >= dist){
					matrix[i].add(j);
				}
				if(second.d >= dist){
					matrix[j].add(i);
				}
			}
		}
		
		for(int i = 0; i < q; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int s = Integer.parseInt(token2.nextToken()) - 1,
					e = Integer.parseInt(token2.nextToken()) - 1;
			
			Queue<Integer> next = new LinkedList<Integer>();
			int[] levels = new int[b];
			Arrays.fill(levels, -1);
			next.add(s);
			levels[s] = 0;

			while (!next.isEmpty()) {
				int curr = next.poll();
				int level = levels[curr];

				for (int adj : matrix[curr]) {
					if (levels[adj] != -1)
						continue;

					levels[adj] = level + 1;
					next.add(adj);
				}
			}
			
			if(levels[e] != -1){
				System.out.println("YES");
			}
			else{
				System.out.println("NO");
			}
		}
	}
	
	private static class e implements Comparable<e> {
		int x, y, d;

		public e(int x0, int y0, int d0) {
			x=x0;y=y0;d=d0;
		}

		@Override
		public int compareTo(e arg0) {
			return Integer.compare(this.d, arg0.d);
		}

//		@Override
//		public boolean equals(Object other) {
//			if (!(other instanceof e)) {
//				return false;
//			}
//			return this.p == ((e) other).p;
//		}

		@Override
		public String toString() {
			return "((" + this.x + ", " + this.y + ") | D: " + this.d + ")";
		}
	}
}