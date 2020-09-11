import java.util.Scanner;

public class liljami {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int sz = sc.nextInt(), ncq = sc.nextInt();
		int[] cups = new int[sz];
		
		for(int i = 0; i < ncq; i++){
			cups[sc.nextInt()]++;
		}
		
		//System.out.println(Arrays.toString(cups));
		
		cups = sum(cups);
		
		int qc = sc.nextInt();
		
		//System.out.println(Arrays.toString(cups));
		
		for(int i = 0; i < qc; i++){
			int a = sc.nextInt() - 1, b = sc.nextInt();
			
			if(a < 0)
				System.out.println(cups[b]);
			else
				System.out.println(cups[b] - cups[a]);
		}
		
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
