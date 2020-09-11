import java.util.Scanner;

/*
 * Written by GUYT
 */
public class SpecialDay {
	
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		int m;
		int d;
		
		try{
			m = sc.nextInt();
			d = sc.nextInt();
		}
		catch(Exception e){
			m = 1;
			d = 1;
		}
		
		if(m < 2)
			so("Before");
		else if(m == 2){
			if(d < 18)
				so("Before");
			else if(d == 18)
				so("Special");
			else
				so("After");
		}
		else
			so("After");
	}
	
	static void so(String s){
		System.out.println(s);
	}
}
