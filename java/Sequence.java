import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.TreeSet;

public class Sequence {

	@SuppressWarnings("unused")
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N, K, Q;
		String[] line = br.readLine().split(" ");
		
		N = Integer.parseInt(line[0]);
		K = Integer.parseInt(line[1]);
		Q = Integer.parseInt(line[2]);
		
		String[] arr = br.readLine().split(" ");
		
		int[] seq = Arrays.stream(arr)
		.mapToInt(Integer::parseInt)
		.toArray();
		
		List<TreeSet<Integer>> nums = new ArrayList<TreeSet<Integer>>();
		
		for(int i = 0; i < 2002; i++)
			nums.add(new TreeSet<Integer>());
		
		for(int i = 0; i < seq.length; i++){
			nums.get(seq[i] + 1000).add(i + 1);
		}
		
		pfxsum(seq);
		
		for(int i = 0; i < Q; i++){
			String[] qline = br.readLine().split(" ");
			
			int a = Integer.parseInt(qline[0]), b = Integer.parseInt(qline[1]), x = Integer.parseInt(qline[2])
					,y = Integer.parseInt(qline[3]);
			
			int sum = x > 1 ? seq[y - 1] - seq[x - 2] : seq[y - 1];
			boolean isAma = (sum > K) && (within(nums.get(a + 1000), x, y) && within(nums.get(b + 1000), x, y));
			
			System.out.println(isAma ? "Yes" : "No");
		}
	}
	
	static void pfxsum(int[] arr) {
		int sum = 0;

		for (int i = 0; i < arr.length; i++) {
			sum += arr[i];
			arr[i] = sum;
		}
	}
	
	static boolean within(TreeSet<Integer> set, int x, int y){
		return (set.floor(y) != null) && (set.ceiling(x) != null);
	}
}