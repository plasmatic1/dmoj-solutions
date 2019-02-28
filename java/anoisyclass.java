import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class NoisyClass {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine()), nn = Integer.parseInt(br.readLine());
		int[] degrees = new int[n];
		ArrayList<Integer>[] matrix = new ArrayList[n];
		
		for(int i = 0; i < n; i++)
			matrix[i] = new ArrayList<Integer>();
		
		for(int i = 0; i < nn; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token.nextToken()), b = Integer.parseInt(token.nextToken());
			matrix[a - 1].add(b - 1);
		}
		
		for(ArrayList<Integer> adjs : matrix){
			for(int adj : adjs){
				degrees[adj]++;
			}
		}
		
//		System.out.println(Arrays.toString(degrees));
		
		LinkedList<Integer> next = new LinkedList<Integer>();
		
		for(int i = 0; i < n; i++){
			if(degrees[i] == 0)
				next.add(i);
		}
		
		while(!next.isEmpty()){
			int curr = next.poll();
			
			for(int adj : matrix[curr]){
				degrees[adj]--;
				
				if(degrees[adj] < 1)
					next.add(adj);
			}
		}
		
//		System.out.println(Arrays.toString(degrees));
		
		boolean acyclic = true;
		
		for(int degree : degrees){
			if(degree > 0){
				acyclic = false;
				break;
			}
		}
		
		System.out.println(acyclic ? "Y" : "N");
	}
}
