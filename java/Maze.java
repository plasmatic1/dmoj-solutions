import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Maze {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < n; i++){
			int r = Integer.parseInt(br.readLine()), c = Integer.parseInt(br.readLine());
			char[][] maze = new char[r][c];
			
			for(int j = 0; j < r; j++){
				maze[r] = br.readLine().toCharArray();
			}
			
			
		}
	}
}
