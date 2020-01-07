import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		
		int[] villages = new int[n];
		double[] sizes = new double[n];
		
		for(int i = 0; i < n; i++) {
			villages[i] = Integer.parseInt(br.readLine());
		}
		
		Arrays.sort(villages);
		
		for(int i = 0; i < n; i++) {
			if(i == 0 || i == n - 1) {
				sizes[i] = Integer.MAX_VALUE;
				continue;
			}
			
			sizes[i] = ((double)(villages[i] - villages[i - 1] + villages[i + 1] - villages[i])) / 2.0;
		}
		
		double smallest = Double.MAX_VALUE;
		for(int i = 0; i < n; i++) {
			if(sizes[i] < smallest) {
				smallest = sizes[i];
			}
		}
		
//		System.out.println(smallest);
		System.out.printf("%.1f", smallest);
	}
}