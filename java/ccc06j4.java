import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.stream.Collectors;
import java.util.Collections;

public class Teen {
	static final int N = 7;
	@SuppressWarnings("unchecked")
	static ArrayList<Integer>[] matrix = new ArrayList[N];
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		init();
		addRelation(0, 6);
		addRelation(0, 3);
		addRelation(1, 0);
		addRelation(2, 3);
		addRelation(2, 4);
//		addRelation(6, 0);
//		addRelation(3, 0);
//		addRelation(0, 1);
//		addRelation(3, 2);
//		addRelation(4, 2);
		
		int a = 0, b = 0;
		while(true){
			a = Integer.parseInt(br.readLine()) - 1;
			b = Integer.parseInt(br.readLine()) - 1;
			
			if(a == -1 || b == -1){
				break;
			}
			
			addRelation(a, b);
		}
		
//		System.out.println(Arrays.toString(matrix));
		
		PriorityQueue<Integer> next = new PriorityQueue<Integer>();
		int[] levels = new int[N];
		ArrayList<Integer> path = new ArrayList<Integer>();
		int[] inDegrees = new int[N];
		Arrays.fill(levels, -1);
		
		for(int i = 0; i < N; i++){
			for(int adjecent : matrix[i]){
//				System.out.printf("Adding 1 for adj %d to root node %d\n", adjecent, i);
				inDegrees[adjecent]++;
			}
		}
		
		for(int i = 0; i < N; i++){
			if(inDegrees[i] == 0){
				levels[i] = 0;
				next.add(i);
			}
		}

		while (!next.isEmpty()) {
			int curr = next.poll();
			int level = levels[curr];
			path.add(curr + 1);
			
//			System.out.printf("Curr: %d\n", curr);

			for (int adj : matrix[curr]) {
				inDegrees[adj]--;
//				if (levels[adj] != -1)
//					continue;
				
//				System.out.printf("Adj: %d\n", adj);

				levels[adj] = level + 1;
				
				if(inDegrees[adj] < 1){
					next.add(adj);
//					System.out.printf("  Adding adj\n");
				}
			}
		}
		
//		System.out.println(path);
//		System.out.println(Arrays.toString(inDegrees));
		
		if(Arrays.stream(inDegrees).anyMatch(i -> i != 0)){
			System.out.println("Cannot complete these tasks. Going to bed.");
		}
		else{
			for (int i: path) {
			    System.out.print(i + " ");
			}
			System.out.println();
		}
	}
	
	//b is adj to a
	static void addRelation(int a, int b){
		matrix[a].add(b);
	}
	
	static void init(){
		for(int i = 0; i < N; i++){
			matrix[i] = new ArrayList<Integer>();
		}
	}
}