
import java.util.Scanner;

public class ccc12j3 {

	public static void main(String[] args) {
		String spa = "";
		String sta = "";
		String ast = "";
		
		Scanner sc = new Scanner(System.in);
		int scale = sc.nextInt();
		sc.close();
		
		for(int i = 0; i < scale; i++){
			spa += " ";
			sta += "x";
			ast += "*";
		}
		
		for(int i = 0; i < scale; i++){
			System.out.println(ast + sta + ast);
		}
		for(int i = 0; i < scale; i++){
			System.out.println(spa + sta + sta);
		}
		for(int i = 0; i < scale; i++){
			System.out.println(ast + spa + ast);
		}
		
	}
}
