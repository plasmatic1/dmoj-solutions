//N <3
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Sokoboop {
	static boolean[][] walls, vis;
	static int N, M, startX, startY, endX, endY, startboxX, startboxY;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		N = Integer.parseInt(token.nextToken());
		M = Integer.parseInt(token.nextToken());
		walls = new boolean[N][M];
		vis = new boolean[N][M];
		
		for(int i = 0; i < N; i++){
			char[] line = br.readLine().toCharArray();
			for(int j = 0; j < M; j++){
				char c = line[j];
				if(c == 'P'){
					startX = i;
					startY = j;
				}
				else if(c == 'B'){
					startboxX = i;
					startboxY = j;
				}
				else if(c == 'X'){
					endX = i;
					endY = j;
				}
				else if(c == '#'){
					walls												[i][j] = true;
				}
			}
		}
		
		System.out.println(getLength(startX, startY, startboxX, startboxY, 0));
	}
	
	static int getLength(int currX, int currY, int boxX, int boxY, int dist){
		vis[currX][currY] = true;
		System.out.printf("For: %d %d\n", currX, currY);
		if(currX > 0){
			if(!walls[currX - 1][currY] && !vis[currX - 1][currY]){
				if(currX - 2 == boxX && currX > 1){
					if(currX - 2 == endX && currY == endY)
						return dist;
					System.out.printf("Box Case (-1, 0)\n");
					return getLength(currX - 1, currY, boxX - 1, boxY, dist + 1);
				}
				else{
					return getLength(currX - 1, currY, boxX, boxY, dist + 1);
				}
			}
		}
		if(currX < N - 1){
			if(!walls[currX + 1][currY] && !vis[currX + 1][currY]){
				if(currX + 2 == boxX && currX < N){
					if(currX + 2 == endX && currY == endY)
						return dist;
					System.out.printf("Box Case (+1, 0)\n");
					return getLength(currX + 1, currY, boxX + 1, boxY, dist + 1);
				}
				else{
					return getLength(currX + 1, currY, boxX, boxY, dist + 1);
				}
			}
		}
		
		if(currY > 0){
			if(!walls[currX][currY - 1] && !vis[currX][currY - 1]){
				if(currY - 1 == boxY && currY > 1){
					if(currX == endX && currY - 2 == endY)
						return dist;
					System.out.printf("Box Case (0, -1)\n");
					return getLength(currX, currY + 1, boxX + 1, boxY, dist + 1);
				}
				else{
					return getLength(currX, currY + 1, boxX, boxY, dist + 1);
				}
			}
		}
		if(currY < M - 1){
			if(!walls[currX][currY + 1] && !vis[currX][currY + 1]){
				if(currY + 1 == boxY && currY < N - 1){
					if(currX == endX && currY + 2 == endY)
						return dist;
					System.out.printf("Box Case (0, +1)\n");
					return getLength(currX, currY + 1, boxX, boxY + 1, dist + 1);
				}
				else{
					return getLength(currX, currY + 1, boxX, boxY, dist + 1);
				}
			}
		}
		
		return -1;
	}
	
//	static int fromXY(int[] a){
//		return fromXY(a[0], a[1]);
//	}
//	
//	static int fromXY(int x, int y){
//		return (x + 1) * N + y;
//	}
//	
//	static int[] toXY(int c){
//		int d = c + 1;
//		return new int[]{d / N - 1, d % N - 1};
//	}
}
