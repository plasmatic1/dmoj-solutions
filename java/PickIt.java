import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Collectors;

public class PickIt {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<Integer> input = get(br);
		while(!(input.get(0).equals(0) && input.size() == 1)){
//			int l = input.size();
//			int[][] table = new int[l][l];
//			
//			for(int i = 1; i < l; i++){
//				System.out.printf("-- i: %d\n", i);
//				for(int j = 1; j < l - i; j++){
//					System.out.printf("- j: %d | ln: %d\n", j, input.size());
//					int alt = input.get(j - 1) + input.get(j) + input.get(j + 1);
//					int old = table[i - 1][j - 1] + table[i][j];
//					
//					System.out.printf("Alt: %d | Old %d\n", alt, old);
//					
//					table[i][j - 1] = Math.max(alt, old);
//				}
//			}
//			
//			for(int i = 0; i < l; i++){
//				System.out.println(Arrays.toString(table[i]));
//			}
//			
//			System.out.println(table[l - 1][0]);
			
			System.out.println(gett(0, input));
			
			input = get(br);
		}
	}
	
	private static ArrayList<Integer> get(BufferedReader r) throws IOException{
		ArrayList<Integer> list = new ArrayList<>();
		for(String ln : r.readLine().split(" ")){
			list.add(Integer.parseInt(ln));
		}
		
		return list;
	}
	
	@SuppressWarnings("unchecked")
	private static int gett(int cs, ArrayList<Integer> original){
		if(original.size() < 4){
			System.out.println("Ending with " + original);
			return original.stream().reduce(0, (a, b) -> a + b);
		}
		
		System.out.println("In " + original);
		
		int l = original.size();
		int max = 0;
		for(int i = 1; i < l - 1; i++){
			ArrayList<Integer> neww = (ArrayList<Integer>) original.clone();
			neww.remove(i);
			int ncs = cs + original.get(i - 1) + original.get(i) + original.get(i + 1);
			int curr = ncs + gett(ncs, neww);
			System.out.println("Curr " + curr);
			if(curr > max){
				max = curr;
			}
		}
		
		return max;
	}
}
