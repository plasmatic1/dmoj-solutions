import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class DeathGunn {

	@SuppressWarnings({ "unchecked", "resource" })
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int M = sc.nextInt(), tot = 0;
		String[] name = new String[M + 1];
		HashMap<String, Integer> mp = new HashMap<String, Integer>();
		ArrayList<Integer>[] adj = new ArrayList[901];
		for(int i = 0; i <= 900; i++)
			adj[i] = new ArrayList<Integer>();
		int[] indeg = new int[901];
		for(int i = 0; i < M; i++){
			String x = sc.next(), y = sc.next();
			if(!mp.containsKey(x)){
				name[tot] = x;
				mp.put(x, tot);
				tot++;
			}
			if(!mp.containsKey(y)){
				name[tot] = y;
				mp.put(y, tot);
				tot++;
			}
			adj[mp.get(y)].add(mp.get(x));
			indeg[mp.get(x)]++;
		}
		while(true){
			boolean flag = true;
			for(int i = 0; i < tot; i++){
				if(indeg[i] == 0){
					indeg[i]--;
					flag = false;
					System.out.println(name[i]);
					
					for(int v : adj[i])
						indeg[v]--;
					break;
				}
			}
			if(flag)
				break;
		}
	}

}