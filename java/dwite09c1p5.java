import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class RunningInCircles {
	static final int N = 101;
	@SuppressWarnings("unchecked")
	static ArrayList<Integer>[] matrix = new ArrayList[N];
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < N; j++){
				matrix[j] = new ArrayList<>();
			}
			
			int n = Integer.parseInt(br.readLine());
			
			for(int j = 0; j < n; j++){
				StringTokenizer token = new StringTokenizer(br.readLine());
				int a = Integer.parseInt(token.nextToken()), b = Integer.parseInt(token.nextToken());
				matrix[a].add(b);
			}
			
			System.out.println(search(1, new ArrayList<>()));
		}
	}
	
	@SuppressWarnings("unchecked")
	static int search(int node, ArrayList<Integer> traveled){
		traveled.add(node);
//		System.out.printf("Node %d\n", node);
		
		int size = 0;
		
		for(int adj : matrix[node]){
//			System.out.printf("Adj node %d, isCycleEnd %b\n", adj, traveled.contains(adj));
			if(traveled.contains(adj))
				return traveled.size() - traveled.indexOf(adj);
			size = Math.max(size, search(adj, (ArrayList<Integer>) traveled.clone()));
		}
		
//		System.out.println();
		return size;
	}
}