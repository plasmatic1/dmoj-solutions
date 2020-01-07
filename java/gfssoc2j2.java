import java.util.Scanner;

public class FizzFuzz {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int nr = sc.nextInt();
		sc.close();
		
		int x = 1, y = 1;
		
		for(int i = 0; i < nr; i++){
			if(x % 7 == 0)
				if(x % 13 == 0)
					System.out.print("Fizz Fuzz ");
				else
					System.out.print("Fizz ");
			else if(x % 13 == 0)
				System.out.print("Fuzz ");
			else
				System.out.print(x + " ");
			
			if(y % 7 == 0)
				if(y % 13 == 0)
					System.out.print("Fizz Fuzz\n");
				else
					System.out.print("Fizz\n");
			else if(y % 13 == 0)
				System.out.print("Fuzz\n");
			else
				System.out.print(y + "\n");
			
			x++;
			y++;
			y++;
		}
	}

}