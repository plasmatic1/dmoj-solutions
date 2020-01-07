import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.stream.Collectors;

public class Main {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		
		int[][] table = new int[n][n], r90 = new int[n][n], r180 = new int[n][n], r270 = new int[n][n];
		
		for(int i = 0; i < n; i++) {
			StringTokenizer token = new StringTokenizer(br.readLine());
			for(int j = 0; j < n; j++) {
				table[i][j] = Integer.parseInt(token.nextToken());
			}
		}
		
		if(isValid(table)) {
			print(table, n);
			return;
		}
		
		//90
		r90 = t90(table, n);
		if(isValid(r90)) {
			print(r90, n);
			return;
		}
		
		r180 = t180(table, n);
		if(isValid(r180)) {
			print(r180, n);
			return;
		}
		
		r270 = t180(t90(table, n), n);
		if(isValid(r270)) {
			print(r270, n);
			return;
		}
		
//		System.out.println();
//		print(table, n);
//		print(r90, n);
//		print(r180, n);
//		print(r270, n);
	}
	
	static boolean isValid(int[][] table) {
		for(int i = 0; i < table.length; i++) {
			int[] row = table[i];
			int[] last = i > 0 ? table[i - 1] : null;
			int prev = -1;
			
			for(int j = 0; j < row.length; j++) {
				if(j != 0) {
					if(row[j] < prev) {
						return false;
					}
				}
				
				if(last != null) {
					if(row[j] < last[j]) {
						return false;
					}
				}
				
				prev = row[j];
			}
		}
		
		return true;
	}
	
	static int[][] t180(int[][] o, int m){
		int[][] n = new int[m][m];
		
		for(int i = m - 1; i >= 0; i--) {
			for(int j = m - 1; j >= 0; j--) {
				n[i][j] = o[m - 1 - i][m - 1 - j];
			}
		}
		
		return n;
	}
	
	static int[][] t90(int[][] o, int m){
		int[][] n = new int[m][m];
		
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < m; j++) {
				n[i][j] = o[m - 1 - j][i];
			}
		}
		
		return n;
	}
	
	static void print(int[][] a, int n) {
		for(int i = 0; i < n; i++) {
			System.out.println(Arrays.stream(a[i]).mapToObj(Integer::toString).collect(Collectors.joining(" ")));
		}
	}
}