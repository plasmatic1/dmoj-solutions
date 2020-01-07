import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class ThirdPlace {
	static ArrayList<e>[] matrix;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		matrix = new ArrayList[n];
		for(int i = 0; i < n; i++){
			matrix[i] = new ArrayList<>();
		}
		
		int q = n - 1;
		for(int i = 0; i < q; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token.nextToken()) - 1,
					b = Integer.parseInt(token.nextToken()) - 1,
					c = Integer.parseInt(token.nextToken());
			
			matrix[a].add(new e(b, c));
			matrix[b].add(new e(a, c));
		}
		
		//BFS1
		
		long[] levels = bfs(0, n);
		
		//BFS 2
		
		e m = arrayMax(levels, n);
		levels = bfs(m.v, n);
		
		//BFS 3
		
		e m22 = arrayMax(levels, n);
		e m2 = arraySecMax(levels, n);
		long[] levels0 = bfs(m22.v, n);
		
		//END
				
		e m3 = arraySecMax(levels0, n);
		
//		System.out.println(Arrays.toString(levels));
//		System.out.println(Arrays.toString(levels0));
//		
//		System.out.printf("%d (%d), %d (%d)\n", max2, max, max22, max21);
		
		System.out.println(Math.max(m2.w, m3.w));
	}
	
	private static e arrayMax(long[] arr, int n){
		long max = Long.MIN_VALUE;
		int mn = -1;
		for(int i = 0; i < n; i++){
			if(arr[i] != -1 && arr[i] > max){
				max = arr[i];
				mn = i;
			}
		}
		
		return new e(mn, max);
	}
	
	private static e arraySecMax(long[] arr, int n){
		long[] arr2 = arr.clone();
		
		e max = arrayMax(arr, n);
		arr2[max.v] = Long.MIN_VALUE;
		return arrayMax(arr2, n);
	}
	
	private static long[] bfs(int start, int n){
		Queue<e> next = new LinkedList<>();
		long[] levels = new long[n];
		Arrays.fill(levels, -1);
		next.add(new e(start, 0));
		levels[start] = 0;

		while (!next.isEmpty()) {
			e curr = next.poll();
			long level = levels[curr.v];

			for (e adj : matrix[curr.v]) {
				if (levels[adj.v] != -1)
					continue;

				levels[adj.v] = level + adj.w;
				next.add(adj);
			}
		}
		
		return levels;
	}
	
	private static class e{
		public int v;
		public long w;
		public e(int v, long w){
			this.v = v;
			this.w = w;
		}
		
		@Override
		public String toString(){
			return "(" + this.v + ", " + this.v + ")";
		}
	}
}