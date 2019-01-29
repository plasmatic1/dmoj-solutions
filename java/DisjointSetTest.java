import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class DisjointSetTest {
	static int parent[];
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer token = new StringTokenizer(br.readLine());
		ArrayList<Integer> e = new ArrayList<>();
		int n = Integer.parseInt(token.nextToken()),
				m = Integer.parseInt(token.nextToken()), cnt = 0;
		parent = new int[n];
		
		for(int i = 1; i < n; i++){
			parent[i] = i;
		}	
		
		for(int i = 1; i <= m; i++) {
			StringTokenizer token2 = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token2.nextToken()) - 1,
					b = Integer.parseInt(token2.nextToken()) - 1;
			int roota = find(a), rootb = find(b);
			
			if(roota != rootb){
				union(roota, rootb);
				cnt++;
				e.add(i);
			}
			if(cnt == n - 1){
				break;
			}
		}
		
		if(cnt == n - 1){
			for(int u : e){
				System.out.println(u);
			}
		}
		else{
			System.out.println("Disconnected Graph");
		}
	}
	
	static int find(int x){
		if(x != parent[x]){
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	
	static void union(int a, int b){
		parent[a] = b;
	}
}
