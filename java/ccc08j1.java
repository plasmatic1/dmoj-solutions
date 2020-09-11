import java.util.Scanner;

public class ccc08j1 {
	
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		double w;
		double h;
		
		w = sc.nextDouble();
		h = sc.nextDouble();
		
		double bmi = (w) / (h * h);
		
		if(bmi < 18.5)
			System.out.println("Underweight");
		else if(bmi > 25)
			System.out.println("Overweight");
		else
			System.out.println("Normal weight");
	}
}
