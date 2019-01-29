import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PrimeFactor {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < N; i++){
			int x = Integer.parseInt(br.readLine());
			boolean prime = true;
			int ox = x;
			int msx = (int) Math.sqrt(x);
			
			for(int j = 2; j < ox; j++){
				while(x % j == 0){
					prime = false;
					x /= j;
					System.out.print(j + " ");
				}
				
				if(prime && j > msx){
					System.out.print(x);
					break;
				}
				
				if(x == 1){	
					if(prime)
						System.out.print(1);
					break;
				}
			}
			
			System.out.print("\n");
		}
	}
}
