import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class graph1p2 {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		ArrayList<Integer>[] matrix = new ArrayList[N];
		
		for(int i = 0; i < matrix.length; i++)
			matrix[i] = new ArrayList<Integer>();
		
		for(int i = 0; i < N; i++){
			String[] line = br.readLine().split(" ");
			
			for(int j = 0; j < line.length; j++){
				if(Integer.parseInt(line[j]) == 1){
					matrix[i].add(j);
				}
			}
		}
		
		//System.out.println("FINAL: " + Arrays.toString(matrix));
		
		Queue<Integer> next = new LinkedList<>();
		int[] levels = new int[N];
		Arrays.fill(levels, -1);
		levels[0] = 0;
		next.add(0);
		
		//System.out.println(levels.size());
		
		while(!next.isEmpty()){
			int current = next.poll();
			int cLevel = levels[current];
			
			for(int i : matrix[current]){
				if(levels[i] == -1){
					next.add(i);
					levels[i] = cLevel + 1;
				}
			}
		}
		
		System.out.println(levels[levels.length - 1]);
	}

}
