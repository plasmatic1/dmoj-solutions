import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class mmm14a {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int A = Integer.parseInt(br.readLine()), B = Integer.parseInt(br.readLine());
		
		List<Integer> primes = new ArrayList<Integer>();
		primes.add(2);
		
		for(int l = 3; l < B; l++){
			boolean prime = true;
			
			for(int ll : primes){
				if(l % ll == 0){
					prime = false;
					break;
				}
				
				if(ll > Math.sqrt(l))
					break;
			}
			
			if(prime){
				primes.add(l);
			}
		}
		
		int[] numbers = new int[B + 1];
		
		for(int i : primes){
			for(int j = i * (A / i); j < numbers.length; j += i)
				numbers[j]++;
		}
		
		for(int i = A; i <= B; i++)
			System.out.println(numbers[i]);
	}
}
