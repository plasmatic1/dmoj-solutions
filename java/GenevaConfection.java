import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class GenevaConfection {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < T; i++){
			int N = Integer.parseInt(br.readLine());
			Stack<Integer> middle = new Stack<Integer>(), list = new Stack<>();
			int current = 1;
			
			for(int j = 0; j < N; j++)
				list.add(Integer.parseInt(br.readLine()));
			
			while(!list.empty() || (!middle.empty() && middle.peek() == current)){
				int x;
				
				if(list.empty())
					x = -1;
				else
					x = list.pop();	
				
				while((!middle.isEmpty()) && (middle.peek() == current)){
					//System.out.printf("Sending middle to end (Middle %d | Curr %d)\n", middle.peek(), current);
					middle.pop();
					current++;
				}
				
				if(x != -1)
					if(x == current)
						current++;
					else
						middle.add(x);
				
				//System.out.printf("x: %d | middle: %s | current %d\n", x, middle.toString(), current);
			}
			System.out.println(middle.empty() ? "Y" : "N");
		}
	}
}
