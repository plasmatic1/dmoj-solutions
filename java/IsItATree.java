import java.util.Arrays;
import java.util.Scanner;

public class IsItATree {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		//EDGES = VERTICIES - 1
		//MININUM AMOUNT OF EDGES TO CONNECT A NUMBER OF VERTICIES
		
		int edges = 0;
		int[][] matrix = new int[4][4];
		
		for(int i = 0; i < 16; i++){
			int v = sc.nextInt();
			edges += v;
			
			matrix[i / 4][i % 4] = v;
		}
		
		boolean notCycle = true;
		
		for(int[] row : matrix){
			if(sumA(row) == 0){
				notCycle = false;
				break;
			}
		}
		
		/*for(int[] a : matrix){
			System.out.println(Arrays.toString(a));
		}*/
		
		sc.close();
		
		System.out.println((edges / 2 == 3) && notCycle ? "Yes" : "No");
	}
	
	public static int sumA(int[] array){
		return array[0] + (array.length == 1 ? 0 : sumA(Arrays.copyOfRange(array, 1, array.length)));
	}
}