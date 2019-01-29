import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PEG {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int[][] board = new int[7][7];
		for(int i = 0; i < 7; i++){
			char[] line = br.readLine().toCharArray();
			int l = line.length;
			for(int j = 0; j < l; j++){
				char c = line[j];
				if(c == ' ')
					board[i][j] = 0;
				else if(c == '.')
					board[i][j] = 1;
				else if(c == 'o')
					board[i][j] = 2;
			}
		}
		
//		for(int i = 0; i < 7; i++){
//			System.out.println(Arrays.toString(board[i]));
//		}
		
		int moves = 0;
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 7; j++){
				if(board[i][j] == 2){
//					System.out.println("Reached " + i + ", " + j);
					if(i < 5 && board[i + 1][j] == 2 && board[i + 2][j] == 1){
						moves++;
					}
					if(i > 1 && board[i - 1][j] == 2 && board[i - 2][j] == 1){
						moves++;
					}
					
					if(j < 5 && board[i][j + 1] == 2 && board[i][j + 2] == 1){
						moves++;
					}
					if(j > 1 && board[i][j - 1] == 2 && board[i][j - 2] == 1){
						moves++;
					}
				}
			}
		}
		
		System.out.println(moves);
	}
}
