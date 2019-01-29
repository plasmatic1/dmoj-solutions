import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Klopka2 {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int small = 101, large = 0;
		for(int i = 0; i < N; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token.nextToken()), b = Integer.parseInt(token.nextToken());
			if(a < small){
				small = a;
			}
			else if(a > large){
				large = a;
			}
			if(b < small){
				small = b;
			}
			else if(b > large){
				large = b;
			}
		}
		
		int diff = Math.abs(large - small);
		System.out.println(diff * diff);
	}
}
