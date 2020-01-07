import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
		
		char[][] grid = new char[n][m];
		ArrayList<e> frees = new ArrayList<>();
		e start = null;
		
		for(int i = 0; i < n; i++) {
			char[] line = br.readLine().toCharArray();
			for(int j = 0; j < m; j++) {
				grid[i][j] = line[j];
				if(line[j] == '.') {
					frees.add(new e(i, j));
				}
				else if(line[j] == 'S') {
					start = new e(i, j);
				}
			}
		}
		
		int[][] levels = new int[n][m];
		LinkedList<e> next = new LinkedList<>();
		
		for(int i = 0; i < n; i++) {
			Arrays.fill(levels[i], -2);
		}
		levels[start.x][start.y] = 0;
		next.add(start);
		
		boolean sc = false;
		
		for(int i = start.y; i < m; i++) {
			char ct = grid[start.x][i];
			if(ct == 'W') {
				break;
			}
			else if(ct == 'C') {
				sc = true;
				break;
			}
		}
		for(int i = start.y; i > 0; i--) {
			char ct = grid[start.x][i];
			if(ct == 'W') {
				break;
			}
			else if(ct == 'C') {
				sc = true;
				break;
			}
		}
		for(int i = start.x; i < n; i++) {
			char ct = grid[i][start.y];
			if(ct == 'W') {
				break;
			}
			else if(ct == 'C') {
				sc = true;
				break;
			}
		}
		for(int i = start.x; i > 0; i--) {
			char ct = grid[i][start.y];
//			System.out.println("ct: " + ct);
			if(ct == 'W') {
				break;
			}
			else if(ct == 'C') {
				sc = true;
				break;
			}
		}
		
		if(sc) {
			next.clear();
		}
		
		while(!next.isEmpty()) {
			e curr = next.poll();
			int level = levels[curr.x][curr.y];
			
//			System.out.println("On " + curr);
//			for(int i = 0; i < levels.length; i++) {
//				System.out.println(Arrays.toString(levels[i]));
//			}
			
//			if(level > n * m) {
//				break;
//			}
			
			for(e adj : new e[] {new e(curr.x - 1, curr.y), new e(curr.x, curr.y - 1), new e(curr.x + 1, curr.y),
					new e(curr.x, curr.y + 1)}) {
				char type = grid[adj.x][adj.y];
				
				ArrayList<e> cv = new ArrayList<>();
				while(type == 'R' || type == 'U' || type == 'L' || type == 'D') {
//					System.out.println("Conveyor " + adj);
					
					if(type == 'R') {
						adj.y++;
					}
					else if(type == 'U') {
						adj.x--;
					}
					else if(type == 'L') {
						adj.y--;
					}
					else if(type == 'D') {
						adj.x++;
					}
					
					type = grid[adj.x][adj.y];
					
					if(cv.contains(adj)) {
						type = '@';
					}
					
					cv.add(new e(adj.x, adj.y));
				}
				
				if(levels[adj.x][adj.y] != -2) {
					continue;
				}
				
				type = grid[adj.x][adj.y];
				
				if(type == 'W') {
					levels[adj.x][adj.y] = -1;
				}
				else if(type == 'C') {
					levels[adj.x][adj.y] = -1;
				}
				else if(type == '.') {
					boolean c = false, b = false;
					
					for(int i = adj.y; i < m && !b; i++) {
						char ct = grid[adj.x][i];
						if(ct == 'W') {
							b = true;
						}
						else if(ct == 'C') {
							c = true;
							b = true;
						}
					}
					
					b = false;
					
					for(int i = adj.y; i > 0 && !b; i--) {
						char ct = grid[adj.x][i];
						if(ct == 'W') {
							b = true;
						}
						else if(ct == 'C') {
							c = true;
							b = true;
						}
					}
					
					b = false;
					
					for(int i = adj.x; i < n && !b; i++) {
						char ct = grid[i][adj.y];
						if(ct == 'W') {
							b = true;
						}
						else if(ct == 'C') {
							c = true;
							b = true;
						}
					}
					
					b = false;
					
					for(int i = adj.x; i > 0 && !b; i--) {
						char ct = grid[i][adj.y];
//						System.out.println("ct: " + ct);
						if(ct == 'W') {
							b = true;
						}
						else if(ct == 'C') {
							c = true;
							b = true;
						}
					}
					
					if(!c) {
						levels[adj.x][adj.y] = level + 1;
						next.add(adj);
					}
					else {
						levels[adj.x][adj.y] = -1;
					}
				}
			}
		}
		
//		for(int i = 0; i < levels.length; i++) {
//			System.out.println(Arrays.toString(levels[i]));
//		}
		
		for(e point : frees) {
			int l = levels[point.x][point.y];
			System.out.println(l == -2 ? -1 : l);
		}
	}
	
	static class e{
		public int x, y;
		public e(int x0, int y0){
			x = x0;
			y = y0;
		}
		
		@Override
		public String toString() {
			return "(" + x + ", " + y + ")";
		}
		
		@Override
		public boolean equals(Object other) {
			if(other instanceof e) {
				e otherr = (e)other;
				return x == otherr.x && y == otherr.y;
			}
			return false;
		}
	}
}