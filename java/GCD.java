
public class GCD {
	public static void main(String[] args) {
		System.out.println(gcd(45, 56));
	}
	
	static int gcd(int x, int y){
		int z = x % y;
		x = y;
		y = z;
		return y > 0 ? gcd(x, y) : x;
	}
}
