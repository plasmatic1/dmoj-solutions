import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class SimonAndMarcy {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int c = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		e[] cages = new e[c];
		int[][] table = new int[c][m + 1];
		
		for(int i = 0; i < c; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int n = Integer.parseInt(token2.nextToken()), k = Integer.parseInt(token2.nextToken());
			cages[i] = new e(n, k);
			//n = v, k = w
		}
		
		for(int i = 0; i < c; i++){
			e curr = cages[i];
			for(int j = 0; j <= m; j++){
//				System.out.printf("PART -- %d %d\n", i, j);
				if(j >= curr.w){
					if(i == 0){
						table[0][j] = curr.v;
					}
					else{
						int alt = curr.v + table[i - 1][j - curr.w];
//						System.out.printf("ALT %d, ORG %d\n", alt, table[i - 1][j]);
						if(alt > table[i - 1][j]){
							table[i][j] = alt;
						}
						else{
							table[i][j] = table[i - 1][j];
						}
					}
				}
				else if(i != 0){
					table[i][j] = table[i - 1][j];
				}
			}
		}
		
//		for(int i = 0; i < c; i++){
//			System.out.println(Arrays.toString(table[i]));
//		}
		
		System.out.println(table[c - 1][m]);
	}
	
	private static class e{
		public int v, w;
		
		public e(int v, int w){
			this.v = v;
			this.w = w;
		}
	}
}
