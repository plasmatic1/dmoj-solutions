import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class SaveNagato {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		ArrayList<Integer>[] matrix = new ArrayList[n];
		for(int i = 0; i < n; i++){
			matrix[i] = new ArrayList<>();
		}
		
		for(int i = 1; i < n; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token.nextToken()) - 1,
					b = Integer.parseInt(token.nextToken()) - 1;
			matrix[a].add(b);
			matrix[b].add(a);
		}
		
		int[] levels = bfs(matrix, 0, n);
		int end1 = maxIndex(levels);
	
		int[] levels0 = bfs(matrix, end1, n);
		int end2 = maxIndex(levels0);
		int[] levels1 = bfs(matrix, end2, n);
		
		for(int i = 0; i < n; i++){
			System.out.println(Math.max(levels0[i] + 1, levels1[i] + 1));
		}
		
//		System.out.println();
//		
//		System.out.println(Arrays.toString(levels));
//		System.out.println(Arrays.toString(levels0));
//		System.out.println(Arrays.toString(levels1));
//		System.out.println(end1 + " " + end2);
	}
	
	static int[] bfs(ArrayList<Integer>[] matrix, int start, int n){
		LinkedList<Integer> next = new LinkedList<Integer>();
		int[] levels = new int[n];
		Arrays.fill(levels, -1);
		next.add(start);
		levels[start] = 0;

		while (!next.isEmpty()) {
			int curr = next.poll();
			int level = levels[curr];

			for (int adj : matrix[curr]) {
				if (levels[adj] != -1)
					continue;

				levels[adj] = level + 1;
				next.add(adj);
			}
		}
		
		return levels;
	}
	
	static int maxIndex(int[] arr){
		int max = Integer.MIN_VALUE, maxInd = -1, length = arr.length;
		for(int i = 0; i < length; i++){
			if(arr[i] > max){
				max = arr[i];
				maxInd = i;
			}
		}
		
		return maxInd;
	}
}