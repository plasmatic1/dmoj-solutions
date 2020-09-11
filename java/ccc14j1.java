import java.util.Scanner;

public class ccc14j1 {
	
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		int a1 = sc.nextInt();
		int a2 = sc.nextInt();
		int a3 = sc.nextInt();
		
		if((a1 + a2 + a3) == 180){
			if(a1 == a2 && a2 == a3)
				System.out.println("Equilateral");
			else if((a1 == a2 && a2 != a3) || (a1 == a3 && a3 != a2) || (a2 == a3 && a3 != a1))
				System.out.println("Isosceles");
			else
				System.out.println("Scalene");
		}
		else{
			System.out.println("Error");
		}
	}

}
