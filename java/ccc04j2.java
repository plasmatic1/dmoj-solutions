import java.util.Scanner;

public class ccc04j2 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int magic = 60;
		
		int x = sc.nextInt();
		int y = sc.nextInt();
		sc.close();
		
		for(int i = 0; i <= y - x; i++){
			if(i % magic == 0)
				System.out.println("All positions change in year " + (i + x));
		}
	}

}
