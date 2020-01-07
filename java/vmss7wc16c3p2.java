import java.util.Scanner;

public class Sha {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int houses = sc.nextInt(), roads = sc.nextInt(), s = sc.nextInt(), d = sc.nextInt();
		
		int[][] matrix = new int[houses + 1][houses + 1];
		
		for(int i = 0; i < roads; i++){
			int a = sc.nextInt(), b = sc.nextInt();
			
			matrix[a][b] = 1;
			matrix[b][a] = 1;
		}
		
		System.out.println((search(s, d, matrix) ? "GO SHAHIR!" : "NO SHAHIR!"));
		sc.close();
	}
	
	static boolean search(int s, int d, int[][] matrix){
		boolean cond = false;
		
		if(s == d) return true;
		
		for(int i = 1; i < matrix[s].length; i++){
			if(matrix[s][i] == 1 && i == d){
				return true;
			}
			else if(matrix[s][i] == 1){
				matrix[s][i] = 0;
				matrix[i][s] = 0;
				cond = cond || search(i, d, matrix);
			}
		}
		
		return cond;
	}
}