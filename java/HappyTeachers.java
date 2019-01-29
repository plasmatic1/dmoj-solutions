import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class HappyTeachers {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		e[] t = new e[n];
		for(int i = 0; i < n; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int h = Integer.parseInt(token.nextToken()), e = Integer.parseInt(token.nextToken()),
					p = Integer.parseInt(token.nextToken());
			
			t[i] = new e(h, e, p);
		}
		
		int tt = Integer.parseInt(br.readLine());
		
		int[][] table = new int[n][tt + 1];
		
		for(int i = 0; i < n; i++){
			e teacher = t[i];
			System.out.printf("-- I of %d, teacher (%d, %d, %d)\n", i, teacher.h, teacher.e, teacher.p);
			
			for(int j = 0; j <= tt; j++){
				System.out.printf("For j %d\n", j);
				if(j >= teacher.p){
					int happ = teacher.h - teacher.e * (j - teacher.p);
					System.out.printf("HapV of %d\n", happ);
					
					if(i != 0){
						int alt = table[i][j - 1] + happ;
						System.out.printf("Alt of %d\n", alt);
						
						if(alt > table[i - 1][j]){
							table[i][j] = happ;
						}
					}
					else{
						if(happ > 0){
							table[i][j] = table[i][j - 1] + happ;
						}
						else{
							table[i][j] = table[i][j - 1];
						}
					}
				}
			}
		}
		
		for(int i = 0; i < n; i++){
			System.out.println(Arrays.toString(table[i]));
		}
		
		System.out.println(table[n - 1][tt]);
	}
	
	static class e{
		int h, e, p;
		public e(int n0, int e0, int p0){
			h = n0;
			e = e0;
			p = p0;
		}
	}
}
