import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class FavouriteTimes {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int D = Integer.parseInt(br.readLine()), t = 1200, c = 0;
		
		if(D > 720){
			int a = D / 720;
			c += 31 * a;
			D -= a * 720;
		}
		
		for(int i = 0; i < D; i++){
			//inc time
			t++;
			
			if(t > 1259)
				t = 100;
			
			if(t % 100 > 59)
				t += 40;
			
			//check
			int x = t > 999 ? t % 1000 / 100 - t % 10000 / 1000 
					: t % 100 / 10 - t % 1000 / 100;
			
			//int oc = c;
			/*
			 * System.out.printf("x: %d | t: %d | c: %d\n", x, t, c);
			System.out.printf("%d - %d | %b\n", t % 100 / 10, t % 1000 / 100, (t % 100 / 10 - t % 1000 / 100) == x);
			System.out.printf("%d - %d | %b\n", t % 10, t % 100 / 10, (t % 10 - t % 100 / 10) == x);
			System.out.printf("%b | %d\n", ((t % 100 / 10 - t % 1000 / 100) == x) &&
						((t % 10 - t % 100 / 10) == x), ((t % 100 / 10 - t % 1000 / 100) == x) &&
						((t % 10 - t % 100 / 10) == x) ? 1 : 0);
			 */
			
			if(t > 999){
				c += ((t % 100 / 10 - t % 1000 / 100) == x) &&
						((t % 10 - t % 100 / 10) == x) ? 1 : 0;
			}
			else{
				c += (t % 10 - t % 100 / 10) == x ? 1 : 0;
			}
			
			
			
			/*
			 * if(c > oc)
				System.out.println("Yes");
			 */
		}
		
		//System.out.println(t);
		System.out.println(c);
	}
}