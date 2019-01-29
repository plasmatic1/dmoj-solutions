import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Golf {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int b = Integer.parseInt(br.readLine());
		int[][] table = new int[b][n + 1];
		for(int i = 0; i < b; i++){
			int c = Integer.parseInt(br.readLine());
			for(int j = 0; j <= n; j++){
				if(i == 0){
					if(j >= c && j % c == 0){
						table[0][j] = 1;
					}
					continue;
				}
				
				
			}
		}
	}
}
