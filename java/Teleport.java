import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;
import java.util.StringTokenizer;

public class Teleport {
	static Set<Integer>[] matrix;
	static int R, C;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokens = new StringTokenizer(br.readLine());
		R = Integer.parseInt(tokens.nextToken());
		C = Integer.parseInt(tokens.nextToken());
		tokens = new StringTokenizer(br.readLine());
		int sr = Integer.parseInt(tokens.nextToken()), sc = Integer.parseInt(tokens.nextToken());
		tokens = new StringTokenizer(br.readLine());
		int er = Integer.parseInt(tokens.nextToken()), ec = Integer.parseInt(tokens.nextToken());
		
		matrix = new Set[R * C];
		
		for(int i = 0; i < matrix.length; i++)
			matrix[i] = new HashSet<Integer>();
		
		for(int i = 0; i < R; i++){
			char[] chars = br.readLine().toCharArray();
			
			for(int j = 0; j < chars.length; j++){
				if(chars[j] == 'O'){
					if(i < R - 1)
						matrix[fromXY(i + 1, j)].add(fromXY(i, j));
					if(i > 0)
						matrix[fromXY(i - 1, j)].add(fromXY(i, j));
					if(j > 0)
						matrix[fromXY(i, j - 1)].add(fromXY(i, j));
					if(j < C - 1)
						matrix[fromXY(i, j + 1)].add(fromXY(i, j));
				}
			}
		}
		
		ArrayList<Integer> tps = new ArrayList<Integer>();
		int T = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < T; i++){
			StringTokenizer tokenss = new StringTokenizer(br.readLine());
			tps.add(fromXY(Integer.parseInt(tokenss.nextToken()), Integer.parseInt(tokenss.nextToken())));
		}
		
		int s = fromXY(sr, sc);
		int e = fromXY(er, ec);
		
		Queue<Integer> next = new LinkedList<Integer>();
		int[] levels = new int[matrix.length];
		Arrays.fill(levels, -1);
		next.add(s);
		levels[1] = 0;

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
		
		//System.out.println(Arrays.toString(matrix));
		
		int normalLength = levels[e];
		ArrayList<Integer> tplengths = new ArrayList<Integer>();
		
		for(int i : tps)
			tplengths.add(levels[i]);
		tplengths.sort(Integer::compareTo);
		
		//System.out.println(tplengths);
		//System.out.println(normalLength);
		
		System.out.println(normalLength - tplengths.get(0));
	}
	
	static int fromXY(int x, int y){
		return x * R + y;
	}
	
	static int[] toXY(int pos){
		return new int[]{pos / R, pos % C};
		
	}
}