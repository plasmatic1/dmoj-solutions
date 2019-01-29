
public class Exponentiation {

	public static void main(String[] args) {
		System.out.println(power1(4, 5));
		System.out.println(power2(4, 0));
	}
	
	static int power1(int a, int b){
		if(b == 1)
			return a;
		return power1(a, b - 1) * a;
	}
	
	static int power2(int a, int b){
		if(b == 1)
			return a;
		int t = power2(a, b / 2);
		if(b % 2 != 0)
			return t * t * a;
		return t * t;
	}
}
