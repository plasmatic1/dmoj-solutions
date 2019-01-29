import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Geppetto {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		//stuff
		for(int i = 0; i < m; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()), b = Integer.parseInt(token2.nextToken());
			
		}
	}
}
