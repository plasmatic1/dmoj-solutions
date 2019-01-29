import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

public class DegreesOfSeparation {
	@SuppressWarnings("unchecked")
	static ArrayList<Integer>[] matrix = new ArrayList[51];
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Arrays.fill(matrix, new ArrayList<Integer>());
		
		setupAll(6, 1, 2, 3, 4, 5, 7);
		setupAll(3, 4, 5, 15);
		setupAll(4, 3, 5);
		setup(7, 8);
		setup(8, 9);
		setupAll(9, 12, 10);
		setupAll(11, 12, 10);
		setup(15, 13);
		setupAll(13, 14, 12);
		setupAll(16, 18, 17);
		setup(17, 18);
		
		while(true){
			char type = br.readLine().charAt(0);
			
			if(type == 'i'){
				int a = Integer.parseInt(br.readLine()), b = Integer.parseInt(br.readLine());
				setup(a, b);
			}
			else if(type == 'd'){
				int a = Integer.parseInt(br.readLine()), b = Integer.parseInt(br.readLine());
				matrix[a].remove((Object) b);
				matrix[b].remove((Object) a);
			}
			else if(type == 'n')
				System.out.println(matrix[Integer.parseInt(br.readLine())].size());
			else if(type == 'f'){
				int a = Integer.parseInt(br.readLine());
				List<Integer> friends = matrix[a];
				Set<Integer> count = new HashSet<Integer>();
				
				for(int x : friends)
					count.addAll(matrix[x]);
				count.removeAll(friends);
				
				System.out.println(count.size() - 1);
			}
			else if(type == 's'){
				int a = Integer.parseInt(br.readLine()), b = Integer.parseInt(br.readLine());
				int sep = bfs(a).get(b);
				
				System.out.println(sep == -1 ? "Not connected" : sep);
			}
			else if(type == 'q')
				break;
		}
	}
	
	static List<Integer> bfs(int cpos){
		Queue<Integer> queue = new LinkedList<Integer>();
		ArrayList<Integer> levels = new ArrayList<Integer>(51);
		queue.add(cpos);
		
		System.out.println(levels.size() + "-");
		
		Collections.fill(levels, -1);
		levels.add(cpos, 0);
		
		while(!queue.isEmpty()){
			cpos = queue.poll();
			int clevel = levels.get(cpos);
			
			for(int adj : matrix[cpos]){
				if(levels.get(adj) == -1){
					levels.set(adj, clevel + 1);
					queue.add(adj);
				}
			}
		}
		
		return levels;
	}
	
	static void setup(int a, int b){
		matrix[a].add(b);
		matrix[b].add(a);
	}
	
	static void setupAll(int a, int...others){
		for(int x : others)
			setup(a, x);
	}
}
