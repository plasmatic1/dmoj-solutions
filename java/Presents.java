import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Presents {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		List<Integer> presents = new ArrayList<Integer>();
		
		for(int i = 0; i < N; i++)
			presents.add(Integer.parseInt(br.readLine()));
		presents.sort(Integer::compare);
		
		int sum = presents.get(0);
		int total = 1;
		
		for(int i : presents.subList(1, presents.size())){
			//System.out.println(i + " " + sum);
			
			if(i >= sum){
				total++;
				sum += i;
			}
		}
		
		System.out.println(total);
	}
}
