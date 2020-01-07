import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class ZeroThatOut {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		Stack<Integer> items = new Stack<Integer>();
		for(int i = 0; i < N; i++){
			int x = Integer.parseInt(br.readLine());
			if(x != 0)
				items.add(x);
			else
				items.pop();
		}
		System.out.println(items.stream().reduce(0, (a, b) -> a + b));
	}
}