import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class MinimumCostFlow {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken()),
				d = Integer.parseInt(token.nextToken());
//		PriorityQueue<e> edges = new PriorityQueue<>();
		ArrayList<e> edges = new ArrayList<>();
		int n0 = n - 1;
		for(int i = 0; i < m; i++){
			StringTokenizer token0 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token0.nextToken()) - 1,
					b = Integer.parseInt(token0.nextToken()) - 1,
					c = Integer.parseInt(token0.nextToken());
			edges.add(new e(a, b, c, i >= n0));
		}
		
		edges.sort(e::compareTo);
		
		int[] dset = create(n);
		e last = null;
		
		int tally = 0, index = 0, cnt = 0;
		for(e edge : edges){
		    if(cnt >= n){
		        break;
		    }
		    
			if(!same(edge.a, edge.b, dset)){
				if(edge.n){
					tally++;
					
				}
				
				last = edge;
				union(edge.a, edge.b, dset);
				cnt++;
			}
			index++;
		}
		
		if(edges.get(m - 1).n){
			dset = create(n);
			
			for(int i = 0; i < m; i++){
				e edge = edges.get(i);
				
				if(!same(edge.a, edge.b, dset)){
					if(edge.c < last.c || (edge.c == last.c && !edge.n)){
						union(edge.a, edge.b, dset);
					}
					else if(edge.c <= d && !edge.n){
						tally--;
						break;
					}
				}
			}
		}
		
		System.out.println(tally);
	}
	
	static int[] create(int n){
		int[] set = new int[n];
		for(int i = 0; i < n; i++){
			set[i] = i;
		}
		return set;
	}
	
	static int root(int n, int[] set){
		if(set[n] == n){
			return n;
		}
		return root(set[n], set);
	}
	
	static void union(int a, int b, int[] set){
		int[] ra = rootAndSize(a, 0, set), rb = rootAndSize(b, 0, set);
		if(ra[1] > rb[1]){
			set[rb[0]] = ra[0];
		}
		else{
			set[ra[0]] = rb[0];
		}
	}
	
	static int[] rootAndSize(int n, int off, int[] set){
		if(set[n] == n){
			return new int[]{n, off};
		}
		return rootAndSize(set[n], off + 1, set);
	}
	
	static boolean same(int a, int b, int[] set){
		return root(a, set) == root(b, set);
	}
	
	static class e implements Comparable<e>{
		public int a, b, c;
		public boolean n;
		public e(int a0, int b0, int c0, boolean n0){
			a = a0;
			b = b0;
			c = c0;
			n = n0;
		}
		
		@Override
		public int compareTo(e o) {
			if(c == o.c){
				if(!n && o.n){
					return -1;
				}
				else if(n && !o.n){
					return 1;
				}
			}
			return Integer.compare(c, o.c);
		}
		
		@Override
		public boolean equals(Object other){
			if(other instanceof e){
				e o = (e)other;
				return a == o.a && b == o.b && c == o.c && n == o.n;
			}
			return false;
		}
		
		@Override
		public String toString(){
			return String.format("(%d -> %d | %d, %b)", a, b, c, n);
		}
	}
}