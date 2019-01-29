import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class JaydenEatsChocolate {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		StringTokenizer token = new StringTokenizer(br.readLine());
		int[] table = new int[n + 1];
		
		for(int i = 0; i < 3; i++){
			int x = Integer.parseInt(token.nextToken());
			
			for(int j = 0; j <= n; j++){
				if(j >= x){
					int diff = table[j - x];
					if((diff != 0 || j % x == 0) && diff + 1 > table[j]){
						table[j] = diff + 1;
					}
				}
			}
		}
		
//		System.out.println(Arrays.toString(table));
		
		System.out.println(table[n]);
	}
}
