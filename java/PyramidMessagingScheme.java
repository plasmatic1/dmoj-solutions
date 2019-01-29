import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;

public class PyramidMessagingScheme {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int L = Integer.parseInt(br.readLine());
		
		for(int helpme = 0; helpme < L; helpme++){
			int N = Integer.parseInt(br.readLine());
			int cd = 0, max = 0;
			
			Set<String> past = new HashSet<String>();
			Stack<String> inputs = new Stack<String>();//inputs go backwards
			
			for(int i = 0; i < N; i++){
				inputs.add(br.readLine());
			}
			
			int l = inputs.size();
			for(int i = 0; i < l; i++){
				String input = inputs.pop();
				
				if(past.contains(input)){
					cd--;
				}
				else{
					cd++;
				}
				
				past.add(input);
				
				if(cd > max){
					max = cd;
				}
				
//				System.out.printf("s: %s (l: %s, %s) | c: %d m: %d\n", input, last, last2, cd, max);
			}
			
//			System.out.printf("%d %d\n", N, max);
			System.out.println((N - (max - 1) * 2) * 10);
		}
	}
}