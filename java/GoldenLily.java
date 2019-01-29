import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class GoldenLily {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int l = Integer.parseInt(token.nextToken()), d = Integer.parseInt(token.nextToken());
		int[][] gr = new int[d][l];
		for(int i = 0; i < d; i++){
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			for(int j = 0; j < l; j++){
				gr[i][j] = Integer.parseInt(token2.nextToken());
			}
		}
		StringTokenizer token2 = new StringTokenizer(br.readLine());
		int gx = Integer.parseInt(token2.nextToken()), gy = Integer.parseInt(token2.nextToken());
		
		PriorityQueue<e> next = new PriorityQueue<>();
		int[][] dist = new int[d][l];
		next.add(new e(0, 0, gr[0][0]));
		dist[0][0] = gr[0][0];
		for(int i = 0; i < d; i++){
			Arrays.fill(dist[i], Integer.MAX_VALUE);
		}
		while(!next.isEmpty()){
			e curr = next.poll();
			
			if(curr.w > dist[curr.x][curr.y]){
				continue;
			}
			
//			System.out.println("Searching " + curr);
			
			ArrayList<e> adjs = new ArrayList<>();
			
			if(curr.x < d - 1){
				adjs.add(new e(curr.x + 1, curr.y, gr[curr.x + 1][curr.y]));
			}
			if(curr.x > 0){
				adjs.add(new e(curr.x - 1, curr.y, gr[curr.x - 1][curr.y]));
			}
			if(curr.y < l - 1){
				adjs.add(new e(curr.x, curr.y + 1, gr[curr.x][curr.y + 1]));
			}
			
			for(e adj : adjs){
//				System.out.println("    Adj " + adj);
				int alt = curr.w + adj.w;
				if(alt < dist[adj.x][adj.y]){
					dist[adj.x][adj.y] = alt;
					next.add(new e(adj.x, adj.y, alt));
				}
			}
		}
		
		System.out.println(dist[gx][gy]);
	}
	
	static class e implements Comparable<e>{
		int x, y, w;
		public e(int x0, int y0, int w0){
			x = x0;
			y = y0;
			w = w0;
		}
		
		@Override
		public int compareTo(e o) {
			// TODO Auto-generated method stub
			return Integer.compare(w, o.w);
		}
		
		@Override
		public String toString(){
			return String.format("(%d, %d) -> %d", x, y, w);
		}
	}
}
