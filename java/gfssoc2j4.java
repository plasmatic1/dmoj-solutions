import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Marathon {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokens = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(tokens.nextToken()), Q = Integer.parseInt(tokens.nextToken());
		int[] episodes = new int[N];
		String[] inp = br.readLine().split(" ");
		for(int i = 0; i < N; i++)
			episodes[i] = Integer.parseInt(inp[i]);
		
		int sum = 0;
		for (int i = 0; i < N; i++) {
			sum += episodes[i];
			episodes[i] = sum;
		}
		
		for(int i = 0; i < Q; i++){
			StringTokenizer tokenss = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(tokenss.nextToken()), b = Integer.parseInt(tokenss.nextToken());
			int sumRange;
			if(a <= 1)
				sumRange = episodes[b - 1];
			else
				sumRange = episodes[b - 1] - episodes[a - 2];
			System.out.println(sum - sumRange);
		}
	}
}
