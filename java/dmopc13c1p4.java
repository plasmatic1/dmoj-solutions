import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class AFK {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		for(int i = 0; i < n; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int w = Integer.parseInt(token.nextToken()), h = Integer.parseInt(token.nextToken());
			char[][] grid = new char[h][w];
			int endX = -1, endY = -1, currX = -1, currY = -1;
			for(int j = 0; j < h; j++){
				char[] line = br.readLine().toCharArray();
				int l = line.length;
				for(int k = 0; k < l; k++){
					if(line[k] == 'C'){
						currX = j;
						currY = k;
					}
					if(line[k] == 'W'){
						endX = j;
						endY = k;
					}
				}
				
				grid[j] = line;
			}
			
//			for(int j = 0; j < grid.length; j++){
//				System.out.println(Arrays.toString(grid[j]));
//			}
//			System.out.printf("Start: (%d, %d)\nEnd: (%d, %d)\n", currX, currY, endX, endY);
			
			Queue<Pair> next = new LinkedList<Pair>();
			int[][] levels = new int[h][w];
			for(int j = 0; j < h; j++){
				Arrays.fill(levels[j], -1);
			}
			next.add(new Pair(currX, currY));
			levels[currX][currY] = 0;

			while (!next.isEmpty()) {	
				Pair curr = next.poll();
				int level = levels[curr.x][curr.y];
				
//				System.out.printf("On: %s\n", curr.toString());
				
				if(curr.x < h - 1){
					int newX = curr.x + 1, newY = curr.y;
//					System.out.printf("New: (%d, %d) (+1, 0)\n", newX, newY);
					char adj = grid[newX][newY];
					if(adj != 'X' && levels[newX][newY] == -1){
						levels[newX][newY] = level + 1;
						next.add(new Pair(newX, newY));
					}
				}
				if(curr.x > 0){
					int newX = curr.x - 1, newY = curr.y;
//					System.out.printf("New: (%d, %d) (-1, 0)\n", newX, newY);
					char adj = grid[newX][newY];
					if(adj != 'X' && levels[newX][newY] == -1){
						levels[newX][newY] = level + 1;
						next.add(new Pair(newX, newY));
					}
				}
				if(curr.y < w - 1){
					int newX = curr.x, newY = curr.y + 1;
//					System.out.printf("New: (%d, %d) (0, +1)\n", newX, newY);
					char adj = grid[newX][newY];
					if(adj != 'X' && levels[newX][newY] == -1){
						levels[newX][newY] = level + 1;
						next.add(new Pair(newX, newY));
					}
				}
				if(curr.y > 0){
					int newX = curr.x, newY = curr.y - 1;
//					System.out.printf("New: (%d, %d) (0, -1)\n", newX, newY);
					char adj = grid[newX][newY];
					if(adj != 'X' && levels[newX][newY] == -1){
						levels[newX][newY] = level + 1;
						next.add(new Pair(newX, newY));
					}
				}
			}
		
//			for(int j = 0; j < levels.length; j++){
//				System.out.println(Arrays.toString(levels[j]));
//			}
			
			int shortestDist = levels[endX][endY];
			if(shortestDist >= 60 || shortestDist == -1){
				System.out.println("#notworth");
			}
			else{
				System.out.println(shortestDist);
			}
		}
	}
}

class Pair{
	int x, y;
	public Pair(int x, int y){
		this.x = x;
		this.y = y;
	}
	@Override
	public String toString(){
		return "(" + x + ", " + y + ")";
	}
}


