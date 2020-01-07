import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Dolls {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int[] prices = new int[101];
		int N = Integer.parseInt(br.readLine());
		StringTokenizer token = new StringTokenizer(br.readLine());
		
		for(int i = 0; i < N; i++){
			int price = Integer.parseInt(token.nextToken());
			prices[price]++;
		}
		
		int max = 0, min = 0, maxc = 0, minc = 1000001;
		for(int i = 0; i < 101; i++){
			int amt = prices[i];
//			System.out.printf("i: %d, amt: %d current min: %d\n", i, amt, minc);
			if(amt >= maxc){
				max = i;
				maxc = amt;
			}
			if(amt < minc && amt != 0){
//				System.out.println("amt is less than minc");
				min = i;
				minc = amt;
			}
		}
		
//		System.out.println(max);
//		System.out.println(min);
//		System.out.println(Arrays.toString(prices));
		
		System.out.println(Math.abs(max - min));
	}
}