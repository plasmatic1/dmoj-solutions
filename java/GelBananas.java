import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class GelBananas {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		long A = Long.parseLong(br.readLine()), B = Long.parseLong(br.readLine()),
				T = Long.parseLong(br.readLine());
		
		long times = T / (A * B / gcd(A, B)) + 1;
		if(A == 1 && B == 1)
			times -= 1;
		
		System.out.println(times);
	}
	
	static long gcd(long x, long y){
		long z = x % y;
		x = y;
		y = z;
		return y > 0 ? gcd(x, y) : x;
	}
}
