import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class Friends {
	static ArrayList<Integer>[] matrix;
	static final int N = 10000;
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		matrix = new ArrayList[N];
		
		for(int i = 0; i < N; i++){
			matrix[i] = new ArrayList<>();
		}
		
		for(int i = 0; i < n; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(token.nextToken()), s = Integer.parseInt(token.nextToken());
			matrix[r].add(s);
		}
		
//		for(int i = 0; i < 100; i++){
//			System.out.println(matrix[i]);
//		}
		
		int a = -1, b = -1;
		while(true){
			StringTokenizer token = new StringTokenizer(br.readLine());
			a = Integer.parseInt(token.nextToken());
			b = Integer.parseInt(token.nextToken());
			
			if(a == 0 && b == 0)
				break;
			
			Queue<Integer> next = new LinkedList<Integer>();
			ArrayList[] paths = new ArrayList[N];
			
			for(int i = 0; i < N; i++){
				paths[i] = new ArrayList<>();
			}
			
			int[] levels = new int[N];
			boolean end = true;
			Arrays.fill(levels, -1);
			next.add(a);
			levels[a] = 0;

			while (!next.isEmpty()) {
				int curr = next.poll();
				int level = levels[curr];

				for (int adj : matrix[curr]) {
//					System.out.println(matrix[curr]);
					if(a == adj){
//						System.out.println("endup");
						end = true;
						break;
					}
					
					if (levels[adj] != -1)
						continue;
					
					paths[curr].add(adj);
					levels[adj] = level + 1;
					next.add(adj);
				}
			}
			
			if(!end)
				System.out.println("No");
			else{
				if(levels[b] > -1){
					System.out.printf("Yes %d\n", levels[b] - 1);
				}
				else
					System.out.println("No");
			}
				
		}
	}
}