import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class TheTriangle {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int[][] table = new int[n][n];
		for(int i = 0; i < n; i++){
			String[] linee = br.readLine().split(" ");
			int[] line = new int[i + 1];
			
			for(int j = 0; j < i + 1; j++){
				line[j] = Integer.parseInt(linee[j]);
			}
			
//			System.out.println(Arrays.toString(line));
			
			if(i == 0){
				table[0][0] = line[0];
				continue;
			}
			
			for(int j = 0; j <= i; j++){
				int alt0 = table[i - 1][j] + line[j];
				
//				System.out.printf("I: %d, J: %d, Alt0: %d\n", i, j, alt0);
				
				if(alt0 > table[i][j]){
					table[i][j] = alt0;
				}
				
				if(j > 0){
					int alt1 = table[i - 1][j - 1] + line[j];
					if(alt1 > table[i][j]){
						table[i][j] = alt1;
					}
					
//					System.out.printf("Alt1: %d\n", alt1);
				}
			}
		}
		
		int max = -1;
		for(int bot : table[n - 1]){
			if(bot > max){
				max = bot;
			}
		}
		
//		for(int i = 0; i < n; i++){
//			System.out.println(Arrays.toString(table[i]));
//		}
		
		System.out.println(max);
	}
}
