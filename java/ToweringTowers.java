import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class ToweringTowers {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		Stack<Integer> stk = new Stack<Integer>();
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 0; i < N; i++){
			int o = Integer.parseInt(st.nextToken()), c = 1;
			while(!stk.isEmpty() && stk.peek() <= o){
				stk.pop();
				c++;
			}
			System.out.printf("%d ", c);
			stk.push(o);
		}
	}
}