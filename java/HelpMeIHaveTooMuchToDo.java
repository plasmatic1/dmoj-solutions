import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class HelpMeIHaveTooMuchToDo {
	@SuppressWarnings("unchecked")
	static Set<Integer>[] matrix = new Set[8];
	static final String FALLBACK = "Cannot complete these tasks. Going to bed.";
	static List<Integer> rems;
	
	public static void main(String[] args) throws Exception{
		for(int i = 1; i < matrix.length; i++)
			matrix[i] = new HashSet<>();
		
		link(1, 7);
		link(1, 4);
		link(2, 1);
		link(3, 4);
		link(3, 5);
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		for(;;){
			int a = Integer.parseInt(br.readLine()), b = Integer.parseInt(br.readLine());
			
			if(a == 0 && b == 0)
				break;
			
			link(a, b);
		}
		
		int start = -1;
		rems = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6, 7));
		
		for(Set<Integer> rl : Arrays.copyOfRange(matrix, 1, matrix.length))
			rems.removeAll(rl);
		
		if(!rems.isEmpty())
			start = rems.get(0);
		
		System.out.println(Arrays.toString(matrix));
		System.out.println(start);
		
		if(start == -1){
			//System.out.println("COULD NOT FIND START");
			System.out.println(FALLBACK);
		}
		else{
			String seq = path(new ArrayList<Integer>(), new ArrayList<Integer>(), start);
			System.out.println(seq);
		}
	}
	
	static void link(int from, int to){
		matrix[from].add(to);
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	static String path(ArrayList<Integer> vis, ArrayList<Integer> path, int current){
		if(vis.size() >= 7)
			return path.stream().map(e -> Integer.toString(e)).collect(Collectors.joining(" "));
		
		ArrayList<Integer> next = new ArrayList(matrix[current]);
		next.removeAll(vis);
		next.addAll(rems);
		
		System.out.printf("--FOR C: %d--\nNEXT: %s \nPATH: %s\n", current, next.toString(), path.toString());
		
		vis.add(current);
		path = new ArrayList<>(path);
		path.add(current);
		
		for(int n : next)
			path(vis, path, n);
		
		return FALLBACK;
	}
}
