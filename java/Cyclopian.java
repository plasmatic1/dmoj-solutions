import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class Cyclopian {
	static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		f(N, 'A', 'B', 'C');
		out.close();
	}
	
	static void f(int n, char a, char b, char c){
		if(n == 1){
			out.printf("%c%c\n", a, c);
			return;
		}
		f(n - 1, a, c, b);
		out.printf("%c%c\n", a, c);
		f(n - 1, b, a, c);
	}
}
