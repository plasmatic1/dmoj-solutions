import java.util.Scanner;

public class UnevenSand {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		final int MAX = 2000000000;
		
		int u = MAX;
		int d = 1;
		//int g = 0;
		
		while(true){
			int m = d + (u - d) / 2;
			System.out.println(m);
			//System.out.println(u + " " + d);
			System.out.flush();
			//g++;
			//System.out.println(g);
			
			String input = sc.next();
			
			if(input.equals("FLOATS")){
					u = m - 1;
			}
			else if(input.equals("SINKS")){
					d = m + 1;
			}
			else if(input.equals("OK")){
				break;
			}
		}
		
		sc.close();
	}

}