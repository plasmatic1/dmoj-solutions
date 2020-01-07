import java.util.ArrayList;
import java.util.Scanner;

public class Senpai {
	public static void main(String[] args) {
		ArrayList<Integer> factors = new ArrayList<Integer>();
		Scanner sc = new Scanner(System.in);
		int A = sc.nextInt();
		sc.close();
		
		for(int i = A / 2; i > 0; i--){
			if(A % i == 0)
				factors.add(i);
		}
		
		//System.out.println(factors);
		
		int w, h;
		int m = factors.size() / 2;
		int sqrt = (int)Math.sqrt(A);
		
		if(sqrt * sqrt != A){
			w = factors.get(m - 1);
			h = factors.get(m);
		}
		else{
			w = sqrt;
			h = sqrt;
		}
		
		//System.out.println(w + " " + h);
		
		System.out.println(2 * (w + h));
	}
}