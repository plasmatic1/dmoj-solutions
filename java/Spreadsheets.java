import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Spreadsheets {
	static final int A = 10;
	static final int B = 9;
	@SuppressWarnings("unchecked")
	static ArrayList<Integer>[] matrix = new ArrayList[A * B];
	static ArrayList<Integer> special = new ArrayList<Integer>();
	static int[][] grid = new int[A][B];
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(int i = 0; i < A; i++){
			for(int j = 0; j < B; j++){
				grid[i][j] = -1;
			}
		}
		
		for(int i = 0; i < A * B; i++){
			matrix[i] = new ArrayList<Integer>();
		}
		
		for(int i = 0; i < A; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			
			for(int j = 0; j < B; j++){
				String token1 = token.nextToken();
				
				try{
					int val = Integer.parseInt(token1);
					grid[i][j] = val;
				}
				catch(NumberFormatException e){
					int coord = coordConv(i, j);
					special.add(coord);
					
//					System.out.println("--Current Node: " + coord + "--");
					
					for(String coordinate : token1.split("\\+")){
						int a = coordinate.charAt(0) - 'A', b = coordinate.charAt(1) - '1';
						
//						System.out.printf("OG: %s | NEW: (%d, %d)\n", coordinate, a, b);
//						(a > -1 && a < A) && (b > -1 && b < B) &&
						
						matrix[coord].add(coordConv(a, b));
					}
				}
			}
		}
		
		//defining
		
//		System.out.println("Starting search");
		
		for(int node : special){
//			System.out.printf("Searching %d...\n", node);
			set(node, search(new ArrayList<Integer>(), node, false));
			matrix[node].clear();
		}
		
		//end
		
		for(int i = 0; i < A; i++){
			System.out.print(convert(grid[i][0]));
			for(int j = 1; j < B; j++){
				System.out.print(" " + convert(grid[i][j]));
			}
			System.out.println();
		}
	}
	
	static String convert(int a){
		return a == -1 ? "*" : "" + a;
	}
	
	static int coordConv(int a, int b){
		return a * (A - 1) + b;
	}
	
	static void set(int coord, int value){
		int[] coord_c = coordConv(coord);
		grid[coord_c[0]][coord_c[1]] = value;
	}
	
	static int get(int coord){
		int[] coord_c = coordConv(coord);
		return grid[coord_c[0]][coord_c[1]];
	}
	
	static int[] coordConv(int coord){
		int a = (coord + 1) / A;
		
		return new int[]{a, coord % B};
	}
	
	static int search(ArrayList<Integer> visited, int startCoord, boolean isNotStart){
		ArrayList<Integer> adjs = matrix[startCoord];
		adjs.removeAll(visited);
		
		if(adjs.isEmpty()){
//			System.out.println("Reached endpoint on " + startCoord + " (" + get(startCoord) + ")");
			return get(startCoord);
		}
		
		visited.add(startCoord);
		
		int total = 0;
		
		for(int node : adjs){
//			System.out.printf("Node: %d | searching at %d | visited is %s\n", startCoord, node, visited.toString());
			int val = search(visited, node, true);
			
			if(val == -1)
				return -1;
			
			total += val;
		}
		
		return total;
	}
	
//	static void defineAllBottom(){
//		for(int snode : special){
//			if(isDirect(snode)){
//				int total = 0;
//				for(int adj : matrix[snode]){
//					total += get(adj);
//				}
//				special.remove(snode);
//				set(snode, total);
//			}
//		}
//	}
//	
//	static boolean isDirect(int coord){
//		return matrix[coord].stream().allMatch(e -> !special.contains(e));
//	}
}
