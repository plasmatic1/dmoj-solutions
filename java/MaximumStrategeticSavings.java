import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringTokenizer;

public class MaximumStrategeticSavings {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(token.nextToken()), m = Integer.parseInt(token.nextToken());
//		HashMap<p, ArrayList<e>> matrix = new HashMap<>();
//		for(int i = 0; i < n; i++){
//			for(int j = 0; j < m; j++){
//				matrix.put(new p(i, j), new ArrayList<>());
//			}
//		}
		ArrayList<f> paths = new ArrayList<>();
		
		int p = Integer.parseInt(token.nextToken()), q = Integer.parseInt(token.nextToken());
		
		for(int i = 0; i < p; i++){
			StringTokenizer token0 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token0.nextToken()) - 1,
					b = Integer.parseInt(token0.nextToken()) - 1,
					c = Integer.parseInt(token0.nextToken());
			for(int j = 0; j < n; j++){
//				matrix.get(new p(j, a)).add(new e(j, b, c));
				paths.add(new f(j, a, j, b, c));
			}
		}
		
		for(int i = 0; i < q; i++){
			StringTokenizer token0 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token0.nextToken()) - 1,
					b = Integer.parseInt(token0.nextToken()) - 1,
					c = Integer.parseInt(token0.nextToken());
			for(int j = 0; j < m; j++){
//				matrix.get(new p(j, a)).add(new e(j, b, c));
				paths.add(new f(a, j, b, j, c));
			}
		}
		
//		System.out.println("start compute");
		
		paths.sort(f::compareTo);
		dset dset = new dset(n, m);
		int total = 0;
		for(f edge : paths){
//			System.out.printf("%s | %s\n", edge.p0, edge.p1);
			if(dset.same(edge.p0, edge.p1)){
				total += edge.z;
				System.out.printf("cut edge: %s -> %s | %d\n", edge.p0, edge.p1, edge.z);
			}
			else{
				dset.union(edge.p0, edge.p1);
			}
		}
		
		System.out.println(total);
	}
	
//	static class e implements Comparable<e>{
//		public p p;
//		public int z;
//		public e(int x0, int y0, int z0){
//			p = new p(x0, y0);
//			z = z0;
//		}
//		public e(p p0, int z0){
//			p = p0;
//			z = z0;
//		}
//		
//		@Override
//		public int compareTo(e o) {
//			return Integer.compare(z, o.z);
//		}
//		
//		@Override
//		public String toString(){
//			return p + " | " + z;
//		}
//		
//		@Override
//		public boolean equals(Object other){
//			if(other instanceof e){
//				e o = (e)other;
//				return p.equals(o.p) && z == o.z;
//			}
//			else if(other instanceof p){
//				p o = (p)other;
//				return p.equals(o);
//			}
//			
//			return false;
//		}
//	}
	
	static class p{
		public int x, y;
		public p(int x, int y){
			this.x = x;
			this.y = y;
		}
		
		@Override
		public boolean equals(Object other){
//			if(other instanceof e){
//				e o = (e)other;
//				return equals(o.p);
//			}
			if(other instanceof p){
				p o = (p)other;
				return x == o.x && y == o.y;
			}
			
			return false;
		}
		
		@Override
		public String toString(){
			return String.format("(%d, %d)", x, y);
		}
		
		@Override
		public int hashCode(){
			return x << 8 + y;
		}
	}
	
	static class f implements Comparable<f>{
		public p p0, p1;
		public int z;
		
		public f(int x0, int y0, int x1, int y1, int z){
			p0 = new p(x0, y0);
			p1 = new p(x1, y1);
			this.z = z;
		}
		
		@Override
		public int compareTo(f o) {
			return Integer.compare(z, o.z);
		}
		
		@Override
		public boolean equals(Object o){
			if(o instanceof f){
				f other = (f)o;
				return p0.equals(other.p0) && p1.equals(other.p1) && z == other.z;
			}
			return false;
		}
	}
	
	static class dset{
		private HashMap<p, p> set;
		private HashMap<p, Integer> ranks;
		
		public dset(int p, int c){
			set = new HashMap<>();
			ranks = new HashMap<>();
			
			for(int i = 0; i < p; i++){
				for(int j = 0; j < c; j++){
					set.put(new p(i, j), new p(i, j));
					ranks.put(new p(i, j), 1);
				}
			}
			
//			System.out.println(set);
		}
		
		public p root(p node){
			if(set.get(node).equals(node)){
				return node;
			}
			
//			System.out.println("root of " + node);
			
			return root(set.get(node));
		}
		
		public void union(p node, p node1){
			p r1 = root(node), r2 = root(node1);
			int s1 = ranks.get(r1), s2 = ranks.get(r2);
			if(s1 < s2){
				set.put(r1, r2);
			}
			else{
				set.put(r2, r1);
				
				if(s1 == s2){
					ranks.put(r1, s1 + s2);
				}
			}
		}
		
		public boolean same(p node, p node0){
			return root(node) == root(node0);
		}
	}
}
