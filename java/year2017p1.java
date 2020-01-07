import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Cookies {
	public static void main(String[] args) throws NumberFormatException, IOException {
		Stack<Integer> l = new Stack<Integer>();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < N; i++){
			StringTokenizer tokens = new StringTokenizer(br.readLine());
			String qt = tokens.nextToken();
			int s = Integer.parseInt(tokens.nextToken());
			
			if(qt.equals("F"))
				l.add(0, s);
			else if(qt.equals("E"))
				l.add(s);
			else if(qt.equals("R"))
				l.remove((Object)s);
		}
		
		for(int i : l){
			System.out.println(i);
		}
	}
}