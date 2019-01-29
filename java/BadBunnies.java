import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class BadBunnies {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), r = Integer.parseInt(token.nextToken());
		ArrayList<Integer>[] matrix = new ArrayList[n];
//		int[] rabbits = new int[r];
		ArrayList<Integer> rabbits = new ArrayList<>();
		int[] dist = new int[n];
		
		for(int i = 0; i < n; i++){
			matrix[i] = new ArrayList<>();
		}
		Arrays.fill(dist, Integer.MAX_VALUE);
		
		for(int i = 1; i < n; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()) - 1
					, b = Integer.parseInt(token2.nextToken()) - 1;
			matrix[a].add(b);
			matrix[b].add(a);
		}
		for(int i = 0; i < r; i++){
//			rabbits[i] = Integer.parseInt(br.readLine());
			rabbits.add(Integer.parseInt(br.readLine()) - 1);
		}
		
		StringTokenizer token3 = new StringTokenizer(br.readLine());
		int x = Integer.parseInt(token3.nextToken()) - 1
				,y = Integer.parseInt(token3.nextToken()) - 1;
		
		for(int rabbit : rabbits){
			Queue<Integer> next = new LinkedList<Integer>();
			boolean[] vis = new boolean[n];
			int[] rdist = new int[n];
			next.add(rabbit);
			vis[rabbit] = true;
			rdist[rabbit] = 0;

			while (!next.isEmpty()) {
				int curr = next.poll();
				int level = rdist[curr];
//				System.out.printf("%d with level %d\n", curr, level);

				for (int adj : matrix[curr]) {
					if (vis[adj])
						continue;
					
//					System.out.println("On adj " + adj);
					
					if(dist[adj] > level + 1){
						dist[adj] = level + 1;
					}
					vis[adj] = true;
					next.add(adj);
				}
			}
			
			System.out.println("Done rabbit " + rabbit);
		}
		
		System.out.println("Begin search");
		
		Queue<Integer> next = new LinkedList<Integer>();
		int[] levels = new int[n];
		int[] prev = new int[n];
		Arrays.fill(levels, -1);
		next.add(x);
		levels[x] = 0;

		while (!next.isEmpty()) {
			int curr = next.poll();
			int level = levels[curr];

			for (int adj : matrix[curr]) {
				if (levels[adj] != -1)
					continue;

				levels[adj] = level + 1;
				prev[adj] = curr;
				next.add(adj);
			}
		}
		
		System.out.println("Done search");
		
//		System.out.println(Arrays.toString(levels));
//		System.out.println();
//		
//		for(int i = 0; i < n; i++){
//			System.out.println(Arrays.toString(rabbitd[i]));
//		}
		
//		ArrayList<Integer> path = new ArrayList<>();
		int curr = y, min = Integer.MAX_VALUE;
		while(true){
			int d = dist[curr];
			
			if(d < min){
				min = d;
			}
			
			System.out.println("Path part: " + curr);
			
			if(prev[curr] == x){
				break;
			}
			
			curr = prev[curr];
		}
		
		System.out.println(min);
	}
}
