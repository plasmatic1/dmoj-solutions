import java.util.Scanner;

public class ccc07j4 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		String l1 = sc.nextLine().replaceAll(" ", "").toUpperCase();
		String l2 = sc.nextLine().replaceAll(" ", "").toUpperCase();
		
		sc.close();
		
		boolean a = true;
		
		for(char c : l1.toCharArray()){
			l2 = l2.replaceFirst(tS(c), "");
			l1 = l1.replaceFirst(tS(c), "");
			
			if(l1.length() != l2.length()){
				a = false;
				break;
			}
		}
		
		if(a)
			System.out.println("Is an anagram.");
		else
			System.out.println("Is not an anagram.");
	}
	
	static String tS(char c){
		return new Character(c).toString();
	}
}
