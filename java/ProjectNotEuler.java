import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ProjectNotEuler {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int x = Integer.parseInt(br.readLine());
		boolean prime = true;
		int ox = x;
		int msx = (int) Math.sqrt(x);
		
		for(int j = 2; j <= ox; j++){
			while(x % j == 0){
				prime = false;
				x /= j;
				System.out.println(j);
			}
			
			if(prime && j > msx){
				System.out.println(x);
				break;
			}
			
			if(x == 1){	
				if(prime)
					System.out.println(1);
				break;
			}
		}
	}
}
