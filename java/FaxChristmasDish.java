import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class FaxChristmasDish {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken()),
				d = Integer.parseInt(token.nextToken());
		
		for(int i = 0; i < m; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int target = Integer.parseInt(token2.nextToken()), 
					rc = Integer.parseInt(token2.nextToken());
			for(int j = 0; j < rc; j++){
				int item = Integer.parseInt(token2.nextToken());
			}
		}
		
		token = new StringTokenizer(br.readLine());
		for(int i = 0; i < d; i++){
			int v = Integer.parseInt(token.nextToken());
			//v = item on day i
		}
		
		//output
	}
}
