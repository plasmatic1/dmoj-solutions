import java.util.Scanner;

public class SumGame {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int N = sc.nextInt(), K = 0;
		int[] s = new int[N], S = new int[N];
		
		for(int i = 0; i < N; i++)
			s[i] = sc.nextInt();
		
		for(int i = 0; i < N; i++)
			S[i] = sc.nextInt();
		
		sc.close();
		
		s = sum(s);
		S = sum(S);
		
		//System.out.println(Arrays.toString(s) + "\n" + Arrays.toString(S));
		
		for(int i = 0; i < N; i++)
			if(s[i] == S[i] && i >= K)
				K = i + 1;
		
		System.out.println(K);
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