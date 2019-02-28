import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class GiantAnts {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		ArrayList<Integer>[] matrix = new ArrayList[n];
		Queue<Integer> next = new LinkedList<Integer>();
		int[] levels = new int[n], timeAnts = new int[n];
		
		for(int i = 0; i < n; i++){
			matrix[i] = new ArrayList<Integer>();
		}
		
		for(int i = 0; i < m; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()) - 1
					, b = Integer.parseInt(token2.nextToken()) - 1;
			matrix[a].add(b);
			matrix[b].add(a);
		}
		
		int o = Integer.parseInt(br.readLine());
		
		Arrays.fill(levels, -1);
		Arrays.fill(timeAnts, -1);
		
		for(int i = 0; i < o; i++){
			int ant = Integer.parseInt(br.readLine()) - 1;
			next.add(ant);
			levels[ant] = 0;
		}
		
		while (!next.isEmpty()) {
			int curr = next.poll();
			int level = levels[curr];
			
//			System.out.println(curr + " | l: " + level);
			
			timeAnts[curr] = level;
			
			for (int adj : matrix[curr]) {
				if (levels[adj] != -1)
					continue;
				
				levels[adj] = level + 4;
				
				next.add(adj);
			}
		}
		
		Arrays.fill(levels, -1);
		levels[0] = 0;
		next.add(0);

		while (!next.isEmpty()) {
			int curr = next.poll();
			int level = levels[curr];

			for (int adj : matrix[curr]) {
				if (levels[adj] != -1)
					continue;
				
				if(timeAnts[adj] != -1 && timeAnts[adj] < level)
					continue;

				levels[adj] = level + 1;
				next.add(adj);
			}
		}
		
		int fd = levels[n - 1];
		
//		System.out.println(Arrays.toString(matrix));
//		System.out.println(Arrays.toString(levels));
//		System.out.println(Arrays.toString(timeAnts));
		
		System.out.println(fd == -1 ? "sacrifice bobhob314" : fd);
	}
}
