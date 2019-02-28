import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class Jayden {
	static ArrayList<Integer>[] matrix;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		matrix = new ArrayList[N + 1];
		for (int i = 0; i < matrix.length; i++)
			matrix[i] = new ArrayList<Integer>();
		
		for(int i = 1; i < N; i++){
			String[] line = br.readLine().split(" ");
			int a = Integer.parseInt(line[0]), b = Integer.parseInt(line[1]);
			matrix[a].add(b);
			matrix[b].add(a);
		}
		
		Queue<Integer> next = new LinkedList<Integer>();
		int[] levels = new int[N + 1];
		Arrays.fill(levels, -1);
		next.add(1);
		levels[1] = 0;
		
		while(!next.isEmpty()){
			int curr = next.poll();
			int level = levels[curr];
			
			for(int adj : matrix[curr]){
				if(levels[adj] != -1)
					continue;
				
				levels[adj] = level + 1;
				next.add(adj);
			}
		}
		
		int max = Arrays.stream(levels)
				.reduce(0, Math::max);
		int ns = -1;
		
		for(int i = 0; i < levels.length; i++)
			if(levels[i] == max){
				ns = i;
				break;
			}
		
		System.out.println(ns);
		
		Queue<Integer> nextt = new LinkedList<Integer>();
		int[] levelss = new int[N - 1];
		Arrays.fill(levelss, -1);
		nextt.add(ns);
		levels[ns] = 0;

		while (!nextt.isEmpty()) {
			int curr = nextt.poll();
			int level = levelss[curr];

			for (int adj : matrix[curr]) {				
				if(levels[adj] != -1)
					continue;
				
				levels[adj] = level + 1;
				next.add(adj);
			}
		}
		
		System.out.println(Arrays.stream(levelss)
				.reduce(0, Math::max));
	}
}
