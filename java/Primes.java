import java.util.Scanner;

public class Primes {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int max = sc.nextInt();
		int p = 0;
		sc.close();
		
		for(int i = max; ; i++){
			boolean prm = true;
			
			for(int j = 2; j < max; j++){
				if(i % j == 0){
					prm = false;
					break;
				}
				
				if(j > Math.sqrt(i))
					break;
			}
			
			if(prm){
				p = i;
				break;
			}
		}
		
		if(max < 2)
			p = 2;
		
		System.out.println(p);
	}
}
