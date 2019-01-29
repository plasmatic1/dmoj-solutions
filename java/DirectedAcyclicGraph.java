 	import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class DirectedAcyclicGraph {
	static ArrayList<Integer>[] matrix;
	static int[] visited;
	static int N;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		matrix = new ArrayList[N];
		visited = new int[N];
		for(int i = 0; i < N; i++){
			matrix[i] = new ArrayList<Integer>();
		}
		for(int i = 0; i < N; i++){
			StringTokenizer tokens = new StringTokenizer(br.readLine());
			for(int j = 0; j < N; j++){
				if(Integer.parseInt(tokens.nextToken()) == 1){
					matrix[i].add(j);
				}
			}
		}
		
		boolean a = false;
		for(int i = 0; i < N; i++){
			if(a)
				break;
			
			if(visited[i] < 1 && !matrix[i].isEmpty())
				a = isCyclic(i, new ArrayList<Integer>());
		}
		
		System.out.println(a ? "NO" : "YES");
	}
	
	static boolean isCyclic(int currPoint, ArrayList<Integer> cs){
		visited[currPoint] = 1;
		cs.add(currPoint);
		
//		System.out.printf("Point: %d | %s | %s\n", currPoint, matrix[currPoint].toString(), cs.toString());
		
		boolean b = false;
		
		for(int i : matrix[currPoint]){
//			System.out.printf("OGP: %d | ADJ-P: %d\n", currPoint, i);
			if(visited[i] == 0){
				b = b || isCyclic(i, new ArrayList<>(cs));
			}
			else if(visited[i] == 1){
				b = true;
			}
		}
		
		for(int i : cs)
			visited[i] = 2;
		
		return b;
	}
}
