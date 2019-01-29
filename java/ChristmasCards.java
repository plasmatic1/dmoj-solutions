import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class ChristmasCards {
	static int[] dp;
	static LinkedList<e> cards = new LinkedList<>();
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		dp = new int[n];
		
		for(int i = 0; i < n; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int c = Integer.parseInt(token.nextToken()), d = Integer.parseInt(token.nextToken());
			cards.add(new e(c, d));
		}
	}
	
	static int dp(int cc){
		return 0;
	}
	
	private static class e{
		private int c, d;
		public e(int c0, int d0){
			c = c0;
			d = d0;
		}
	}
}
