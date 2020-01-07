import java.util.Scanner;

public class BattlePositions {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int l = sc.nextInt(), req = sc.nextInt(), wn = sc.nextInt(), fails = -1;
		
		int[] stations = new int[l + 1];
		
		for(int i = 0; i < wn; i++){
			int b = sc.nextInt() - 1, e = sc.nextInt(), n = sc.nextInt();
			stations[b] += n;
			stations[e] -= n;
		}
		
		stations = sum(stations);
		
		for(int x : stations){
			if(x < req)
				fails++;
		}
		
		System.out.println(fails);
		
		sc.close();
	}
	
	static int[] sum(int... a){
		int s = 0;
		
		for(int i = 0; i < a.length; i++){
			//System.out.printf("x = %d + %d (a[%d])\n", s, a[i], i);
			
			s += a[i];
			a[i] = s;
		}
		
		return a;
	}
}