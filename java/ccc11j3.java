import java.util.Scanner;

public class SumacSequence {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int A = sc.nextInt(), B = sc.nextInt();
		sc.close();
		
		System.out.println(sumac(A, B, 2));
	}
	
	public static int sumac(int a, int b, int x){
		//System.out.printf("%d %d | %d\n", a, b, x);
		
		return a < b ? x : sumac(b, a - b, x + 1);
	}
}