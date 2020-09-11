import java.util.Scanner;

public class ccc11j2 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int h = sc.nextInt();
		int m = sc.nextInt();
		sc.close();
		
		int t = 0;
		int A = 1;
		
		while(m >= t && A > 0){
			t++;
			A = (int) (-6 * Math.pow(t, 4) + h * Math.pow(t, 3) + 2 * Math.pow(t, 2) + t);
		}
		
		if(t >= m)
			System.out.println("The balloon does not touch ground in the given time.");
		else{
			System.out.println("The balloon first touches ground at hour:");
			System.out.println(t);
		}
	}
}
