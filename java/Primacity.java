import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Primacity {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int T = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < T; i++){
			StringTokenizer ln = new StringTokenizer(br.readLine());
			
			int A = Integer.parseInt(ln.nextToken()), B = Integer.parseInt(ln.nextToken()),
					K = Integer.parseInt(ln.nextToken());
			
			int[] nums = new int[B + 1];
			
			for(int j = 2; j <= B; j++){
				if(nums[j] != 0)
					continue;
				
				for(int k = j; k <= B; k += j){
					//System.out.printf("J (%d): %d | %d\n", nums[j], j, k);
					nums[k]++;
				}
			}
			
			int pcyC = 0;
			
			for(int j = A; j <= B; j++){
				if(nums[j] == K)
					pcyC++;
			}
			
			System.out.printf("Case #%d: %d\n", i + 1, pcyC);
		}
	}
}
