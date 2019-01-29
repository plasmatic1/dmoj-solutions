import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class SurpriseTeleportation {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int w, h, startX, startY, endX, endY;
		StringTokenizer token = new StringTokenizer(br.readLine());
		w = Integer.parseInt(token.nextToken());
		h = Integer.parseInt(token.nextToken());
		StringTokenizer token2 = new StringTokenizer(br.readLine());
		startX = Integer.parseInt(token2.nextToken()) - 1;
		startY = Integer.parseInt(token2.nextToken()) - 1;
		StringTokenizer token3 = new StringTokenizer(br.readLine());
		endX = Integer.parseInt(token3.nextToken()) - 1;
		endY = Integer.parseInt(token3.nextToken()) - 1;
		
		System.out.printf("Start: (%d, %d)\nEnd: (%d, %d)\n", startX, startY, endX, endY);
		
		ArrayList<Pair> teleporters = new ArrayList<Pair>();
		
		char[][] grid = new char[w][h];
		for(int i = 0; i < h; i++){
			grid[i] = new StringBuilder(br.readLine()).reverse().toString().toCharArray();
		}
		
		int teleporterCount = Integer.parseInt(br.readLine());
		for(int i = 0; i < teleporterCount; i++){
			StringTokenizer token4 = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(token4.nextToken()) - 1, y = Integer.parseInt(token4.nextToken()) - 1;
			teleporters.add(new Pair(x, y));
		}
		
		Queue<Pair> next = new LinkedList<Pair>();
		int[][] levels = new int[h][w];
		for(int i = 0; i < h; i++){
			Arrays.fill(levels[i], -1);
		}
		next.add(new Pair(startX, startY));
		levels[startX][startY] = 0;

		while (!next.isEmpty()) {
			Pair curr = next.poll();
			int level = levels[curr.x][curr.y];

			if(curr.x < h - 1){
				int newX = curr.x + 1, newY = curr.y;
//				System.out.printf("New: (%d, %d) (+1, 0)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels[newX][newY] == -1){
					levels[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
			if(curr.x > 0){
				int newX = curr.x - 1, newY = curr.y;
//				System.out.printf("New: (%d, %d) (-1, 0)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels[newX][newY] == -1){
					levels[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
			if(curr.y < w - 1){
				int newX = curr.x, newY = curr.y + 1;
//				System.out.printf("New: (%d, %d) (0, +1)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels[newX][newY] == -1){
					levels[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
			if(curr.y > 0){
				int newX = curr.x, newY = curr.y - 1;
//				System.out.printf("New: (%d, %d) (0, -1)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels[newX][newY] == -1){
					levels[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
		}
		
		//second search
		
		int[][] levels2 = new int[h][w];
		for(int i = 0; i < h; i++){
			Arrays.fill(levels2[i], -1);
		}
		next.add(new Pair(startX, startY));
		levels2[startX][startY] = 0;

		while (!next.isEmpty()) {
			Pair curr = next.poll();
			int level = levels2[curr.x][curr.y];
			
			if(teleporters.contains(curr)){
				levels2[endX][endY] = level;
				break;
			}

			if(curr.x < h - 1){
				int newX = curr.x + 1, newY = curr.y;
//				System.out.printf("New: (%d, %d) (+1, 0)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels2[newX][newY] == -1){
					levels2[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
			if(curr.x > 0){
				int newX = curr.x - 1, newY = curr.y;
//				System.out.printf("New: (%d, %d) (-1, 0)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels2[newX][newY] == -1){
					levels2[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
			if(curr.y < w - 1){
				int newX = curr.x, newY = curr.y + 1;
//				System.out.printf("New: (%d, %d) (0, +1)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels2[newX][newY] == -1){
					levels2[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
			if(curr.y > 0){
				int newX = curr.x, newY = curr.y - 1;
//				System.out.printf("New: (%d, %d) (0, -1)\n", newX, newY);
				char adj = grid[newX][newY];
				if(adj != 'X' && levels2[newX][newY] == -1){
					levels2[newX][newY] = level + 1;
					next.add(new Pair(newX, newY));
				}
			}
		}
		
		for(int j = 0; j < levels.length; j++){
			System.out.println(Arrays.toString(levels[j]));
		}
		System.out.println();
		for(int j = 0; j < levels2.length; j++){
			System.out.println(Arrays.toString(levels2[j]));
		}
		
		int diff = levels[endX][endY] - levels2[endX][endY];
		System.out.printf("Normal: %d\nTP: %d\n", levels[endX][endY], levels2[endX][endY]);
		
		System.out.println(diff < 0 ? 0 : diff);
	}
	
	public static class Pair{
		int x, y;
		public Pair(int x, int y){
			this.x = x;
			this.y = y;
		}
		@Override
		public String toString(){
			return "(" + x + ", " + y + ")";
		}
		@Override
		public boolean equals(Object other){
			if(other instanceof Pair){
				Pair other2 = (Pair)other;
				return this.x == other2.x && this.y == other2.y;
			}
			
			return false;
		}
	}
}