import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class BowlingForNumbers {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		for(int i = 0; i < t; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int n = Integer.parseInt(token.nextToken()), k = Integer.parseInt(token.nextToken()),
					w = Integer.parseInt(token.nextToken());
			
			int[][] table = new int[k + 1][n];
			int[] balls = new int[n];
			for(int j = 0; j < n; j++){
				balls[j] = Integer.parseInt(br.readLine());
			}
			int[] sums = pfxsum(balls);
			
			for(int j = 0; j < k; j++){
				
			}
		}
	}
	
	private static int[] pfxsum(int[] a){
		int sum = 0;
		int[] neww = new int[a.length];
		for(int i = 0; i < a.length; i++){
			sum += a[i];
			neww[i] = sum;
		}
		
		return neww;
	}
}
