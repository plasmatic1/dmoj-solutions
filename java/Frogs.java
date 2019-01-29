import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Frogs {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int stones = Integer.parseInt(br.readLine()), pads = Integer.parseInt(br.readLine());
		System.out.println((int)Math.pow(2, stones) * (pads + 1));
	}
	
	/*static int power2(int a, int b){
		if(b == 0)
			return 1;
		if(b == 1)
			return a;
		int t = power2(a, b / 2);
		if(b % 2 != 0)
			return t * t * a;
		return t * t;
	}*/
}
