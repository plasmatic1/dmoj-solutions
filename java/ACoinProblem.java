import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class ACoinProblem {
	// Angie

	static final int MAX = 2001, MD = 10001, MQ = 100000;
	static int n, q, ba, bb,
		coins[] = new int[MAX], dp[] = new int[MD], ans[] = new int[MQ];
	static PriorityQueue<qu> queries = new PriorityQueue<>();

	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		
		n = Integer.parseInt(token.nextToken());
		q = Integer.parseInt(token.nextToken());

		token = new StringTokenizer(br.readLine());
		for (int i = 1; i <= n; ++i) {
			coins[i] = Integer.parseInt(token.nextToken());
		}

		for (int i = 0; i < q; ++i) {
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			ba = Integer.parseInt(token2.nextToken());
			bb = Integer.parseInt(token2.nextToken());

			queries.add(new qu(i, ba, bb));
		}

		// DP

		Arrays.fill(dp, 0x3f3f3f3f);
		dp[0] = 0;

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < MD; ++j) {
				if(j >= coins[i]){
					dp[j] = Math.min(dp[j], dp[j - coins[i]] + 1);
				}
			}

			while(!queries.isEmpty() && queries.peek().l == i){
				qu que = queries.poll();

				ans[que.i] = dp[que.c];
			}
		}

		// Out

		for (int i = 0; i < q; ++i) {
			System.out.printf("%d\n", ans[i] == 0x3f3f3f3f ? -1 : ans[i]);
		}
	}
	
	private static class qu implements Comparable<qu>{
		int i, c, l;

		qu(int i0, int c0, int l0){
			i = i0;
			c = c0;
			l = l0;
		}
		
		qu(){
			this(-1, -1, -1);
		}

		@Override
		public int compareTo(qu arg0) {
			return Integer.compare(this.l, arg0.l);
		}
	};
}
