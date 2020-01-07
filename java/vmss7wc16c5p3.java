import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.concurrent.CopyOnWriteArrayList;

public class Trees {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int size = sc.nextInt();
		
		@SuppressWarnings("unchecked")
		List<Integer>[] matrix = new ArrayList[size + 1];
		
		for(int i = 1; i < matrix.length; i++){
			matrix[i] = new ArrayList<Integer>();
		}
		
		for(int i = 1; i < size; i++){
			int a = sc.nextInt();
			int b = sc.nextInt();
			
			matrix[a].add(b);
			matrix[b].add(a);
		}
		
		sc.close();
		
		List<Integer> on = new CopyOnWriteArrayList<Integer>();
		Set<Integer> vis = new HashSet<Integer>();
		
		on.add(1);
		
		int foundLast = -1;
		
		for(;;){
			List<Integer> onn = new ArrayList<Integer>();
			
			for(int x : on){
				for(int n : matrix[x]){
					if(!vis.contains(n)){
						onn.add(n);
						vis.add(n);
					}
				}
			}
			
			if(onn.size() == 0){
				foundLast = on.get(0);
				break;
			}
			
			on.clear();
			on.addAll(onn);
		}
		
		on.clear();
		vis.clear();
		
		int dist = -1;
		on.add(foundLast);
		
		for(int d = 0; ; d++){
			List<Integer> onn = new ArrayList<Integer>();
			
			for(int x : on){
				for(int n : matrix[x]){
					if(!vis.contains(n)){
						onn.add(n);
						vis.add(n);
					}
				}
			}
			
			if(onn.size() == 0){
				dist = d;
				break;
			}
			
			on.clear();
			on.addAll(onn);
		}
		
		System.out.println(dist);
	}
}