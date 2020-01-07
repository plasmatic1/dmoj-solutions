import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class AnimeConvention {
	static int[] dset;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), q = Integer.parseInt(token.nextToken());
//		ArrayList<Integer>[] matrix = new ArrayList[n];
//		for(int i = 0; i < n; i++){
//			matrix[i] = new ArrayList<>();
//		}
		dset = new int[n];
		for(int i = 0; i < n; i++){
			dset[i] = i;
		}
		
		for(int i = 0; i < q; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			char c = token2.nextToken().charAt(0);
			int a = Integer.parseInt(token2.nextToken()) - 1,
					b = Integer.parseInt(token2.nextToken()) - 1;
			
			if(c == 'A'){
//				matrix[a].add(b);
//				matrix[b].add(a);
				
				//Disjointed set thing]
				union(a, b);
//				System.out.println(Arrays.toString(dset));
			}
			else if(c == 'Q'){
				System.out.println(same(a, b) ? "Y" : "N");
			}
		}
	}
	
	private static int root(int x){
		if(dset[x] == x){
			return x;
		}
		return root(dset[x]);
	}
	
	private static void union(int x, int y){
		int xr = root(x), yr = root(y);
		
		dset[yr] = xr;
	}
	
	private static boolean same(int x, int y){
		return root(x) == root(y);
	}
}