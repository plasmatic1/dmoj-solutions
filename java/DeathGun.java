import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.stream.Collectors;

public class DeathGun {
	static HashMap<String, List<String>> relations = new HashMap<String, List<String>>();
	static HashSet<String> uniques = new HashSet<String>();
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < N; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			String b = token.nextToken(), a = token.nextToken();
			
			uniques.add(a);
			uniques.add(b);
			addRelation(a, b);
		}
		
		ArrayList<String> order = new ArrayList<String>();
		HashMap<String, Integer> inDegreeMap = new HashMap<String, Integer>();
		LinkedList<String> next = new LinkedList<String>();
		
		for(String s : uniques)
			inDegreeMap.put(s, 0);
		
		for(List<String> ends : relations.values()){
			for(String end : ends){
				inDegreeMap.put(end, inDegreeMap.get(end) + 1);
			}
		}
		
		inDegreeMap.entrySet().stream().filter(entry -> entry.getValue() == 0).forEach(entry -> {
			next.add(entry.getKey());
		});
		
//		System.out.println(inDegreeMap);
		
		while(!next.isEmpty()){
			String curr = next.poll();
			order.add(curr);
			
//			System.out.println("At " + curr);
			
			if(!relations.containsKey(curr))
				continue;
			
			for(String adj : relations.get(curr)){
//				System.out.println("Adj " + adj);
				int num = inDegreeMap.get(adj) - 1;
				
				if(num == 0){
					next.addFirst(adj);
				}
				
				inDegreeMap.put(adj, num);
			}
			
//			System.out.println("End iteration " + next);
		}
		
//		System.out.println(inDegreeMap);
		
		System.out.println(order.stream().collect(Collectors.joining("\n")));
	}
	
	static void addRelation(String a, String b){
		if(relations.containsKey(a))
			relations.get(a).add(b);
		else{
			ArrayList<String> list = new ArrayList<String>();
			list.add(b);
			relations.put(a, list);
		}
	}
}
