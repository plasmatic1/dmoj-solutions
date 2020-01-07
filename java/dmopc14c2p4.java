import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Deforestation {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int[] trees = new int[N];
		for(int i = 0; i < N; i++)
			trees[i] = Integer.parseInt(br.readLine());
		
		int sum = 0;
		for(int i = 0; i < N; i++){
			int val = trees[i];
			sum += val;
			trees[i] = sum;
		}
		
		int Q = Integer.parseInt(br.readLine());
		for(int i = 0; i < Q; i++){
			StringTokenizer tokens = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(tokens.nextToken()), b = Integer.parseInt(tokens.nextToken());
			
			if(a == 0)
				System.out.println(trees[b]);
			else{
				System.out.println(trees[b] - trees[a - 1]);
			}
		}
	}
}