import java.util.Scanner;

public class ccc08j2 {
	static String str = "ABCDE";
	
	public static void main(String[] args){
		Scanner it = new Scanner(System.in);
		
		for(;;){
			int x = it.nextInt();
			int y = it.nextInt();
			
			switch(x){
			case 1:
				a(y);
				break;
			case 2:
				b(y);
				break;
			case 3:
				c(y);
				break;
			case 4:
				for(int z = 0; z < y; z++){
					for(char c : str.toCharArray()){
						System.out.print(c + " ");
					}
				}
				out("");
				it.close();
				break;
			default:
				break;
			}
			
			if(x == 4)
				break;
		}
	}
	
	static void a(int n){
		for(int cn = 0; cn < n; cn++){
			str = "" + str.substring(1, str.length()) + str.charAt(0);
		}
		//out(str);
	}
	
	static void b(int n){
		for(int cn = 0; cn < n; cn++){
			str = "" + str.charAt(str.length() - 1) + str.substring(0, str.length() - 1);
		}
		//out(str);
	}
	
	static void c(int n){
		for(int cn = 0; cn < n; cn++){
			str = "" + str.charAt(1) + str.charAt(0) + str.substring(2, str.length());
		}
		//out(str);
	}
	
	static void out(Object o){
		System.out.println("" + o);
	}
}
