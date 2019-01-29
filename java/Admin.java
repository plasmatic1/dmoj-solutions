import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Admin {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		List<Integer> fataleagle = new ArrayList<Integer>();
		List<Integer> xyene = new ArrayList<Integer>();
		
		String[] arr = br.readLine().split(" ");
		Arrays.stream(arr)
		.mapToInt(Integer::parseInt)
		.forEach(i -> fataleagle.add(i));
		
		String[] arr2 = br.readLine().split(" ");
		Arrays.stream(arr2)
		.mapToInt(Integer::parseInt)
		.forEach(i -> xyene.add(i));
		
		//System.out.println(fataleagle.size() + " " + xyene.size());
		
		fataleagle.sort(Integer::compare);
		xyene.sort(Integer::compare);
		
		System.out.println(runcontest(fataleagle, xyene, N));
		System.out.println(runcontest(xyene, fataleagle, N));
		
		
		//fataleagle best case scenario
	}
	
	static int runcontest(List<Integer> a, List<Integer> b, int N){
		int pts = 0;
		int ptr = 0;
		
		for(int i = 0; i < a.size(); i++){
			int req = b.get(i);
			boolean bk = false;
			
			while(a.get(ptr) <= req){
				if(ptr + 1 >= a.size()){
					bk = true;
					break;
				}
				
				ptr++;
			}
			
			//System.out.printf("%d | %d %d %b\n", i, ptr, req, bk);
			
			if(bk)
				break;
			pts++;
		}
		
		return pts;
	}
}
