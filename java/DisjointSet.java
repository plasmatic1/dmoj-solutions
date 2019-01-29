public class DisjointSet {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
	
	static int[] disjointset(int n, int size){
		int[] set = new int[size];
		set[n] = n;
		
		return set;
	}
	
	static int find(int start, int[] set){
		if(start != set[start]){
			set[start] = find(set[start], set);
		}
		return set[start];
	}
	
	static int[] union(int a, int b, int[] set){
		return new int[]{};
	}
	
	
	
	public void link(int x, int y){
		//
	}
}
