import java.util.Scanner;

public class ccc12j4 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int shift = sc.nextInt();
		String s = sc.next();
		
		sc.close();
		
		String es = "";
		
		for(int i = 0; i < s.length(); i++){
			int bs = i(s.charAt(i)) - 3 * (i + 1) - shift;
			int sa = 0;
			
			if(bs < 65)
				sa = 90 - (64 - bs);
			else
				sa = bs;
			
			es += (char) sa;
		}
		
		System.out.println(es);
	}
	
	static int i(char c){
		return (int) c;
	}
}
