import java.util.Scanner;

public class ccc02s2 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int d = sc.nextInt();
		sc.close();
		
		int gcf = gcf(n, d);
		
		if(gcf > 1){
			n /= gcf;
			d /= gcf;
		}
		
		if(n > d){
			if(n % d == 0)
				System.out.println(n / d);
			else{
				int extra = n / d;
				System.out.println(extra + " " + (n - extra * d) + "/" + d);
			}
		}
		else
			System.out.println(n + "/" + d);
	}
	static int gcf(int x, int y){
		if(x == y)
			return x;
		
		int gcf = 0;
		
		for(int i = 1; i <= Math.min(x, y); i++){
			if((x % i == 0 && y % i == 0) && gcf < i)
				gcf = i;
		}
		
		return gcf;
	}
}
