import java.util.Scanner;

public class Estimate {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int N = sc.nextInt();
		
		for(int i = 0; i < N; i++){
			String num = sc.next();
			System.out.println(num.length());
		}
		
		sc.close();
	}

}