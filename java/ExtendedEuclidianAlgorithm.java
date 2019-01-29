import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExtendedEuclidianAlgorithm {
	public static void main(String[] args){
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Enter your numbers:");
		int a = -1, b = -1;
		try {
			a = Integer.parseInt(br.readLine());
			b = Integer.parseInt(br.readLine());
		} catch (NumberFormatException | IOException e) {
			System.out.println("Boi bad input");
			return;
		}
		
		if(a < 0 || b < 0){
			System.out.println("Numbers must be 0 or larger!");
			return;
		}
		
		System.out.println(f(a, b));
	}
	
	static int f(int a, int b){
		int x = Math.max(a, b), y = Math.min(a, b), z = x % y;
		return z == 0 ? y : f(y, z);
	}
}
