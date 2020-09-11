import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ccc11j1 {
	
	static Scanner sc = new Scanner(System.in);
	static List<String> pss = new ArrayList<String>();

	public static void main(String[] args) {
		int ants = sc.nextInt();
		int eyes = sc.nextInt();
		
		if(ants >= 3 && eyes <= 4)
			pss.add("TroyMartian");
		if(ants <= 6 && eyes >= 2)
			pss.add("VladSaturnian");
		if(ants <= 2 && eyes <= 3)
			pss.add("GraemeMercurian");
		
		if(!pss.isEmpty()){
			for(String s : pss)
				System.out.println(s);
		}
	}

}
