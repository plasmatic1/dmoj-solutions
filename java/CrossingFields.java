import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class CrossingFields {
	static int[][] matrix;
	static boolean[][] vis;
	static int H;
	static int bound;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(token.nextToken());
		H = Integer.parseInt(token.nextToken());
		
		matrix = new int[N][N];
		vis = new boolean[N][N];
		bound = N - 1;
		
		for(int i = 0; i < N; i++){
			StringTokenizer token0 = new StringTokenizer(br.readLine());
			for(int j = 0; j < N; j++){
				matrix[i][j] = Integer.parseInt(token0.nextToken());
			}
		}
		
		System.out.println(canCross(0, 0, matrix[0][0]) ? "yes" : "no");
	}
	
	static boolean canCross(int x, int y, int lh){
		if(x > bound || y > bound)
			return false;
		if(x < 0 || y < 0)
			return false;
		
//		System.out.printf("%d %d | h: %d %d | ib: %b h: %b v: %b\n", 
//				x, y, matrix[x][y], lh, x == bound && y == bound, matrix[x][y] - lh > H, vis[x][y]);
		
		int h = matrix[x][y];
		
		if(Math.abs(h - lh) > H)
			return false;
		if(vis[x][y])
			return false;
		vis[x][y] = true;
		if(x == bound && y == bound)
			return true;
		
		return canCross(x + 1, y, h) || canCross(x - 1, y, h) || canCross(x, y + 1, h) ||
				canCross(x, y - 1, h);
	}
}
