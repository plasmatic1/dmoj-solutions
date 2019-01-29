public class Candy {
	public static void main(String[] args) {
		//Scanner sc = new Scanner(System.in);
		
		//int C = sc.nextInt(), X = sc.nextInt(), c = 0;
		
		
	}
	
	static boolean isPrime(int x){
		for(int i = 2; i <= Math.sqrt(x); i++){
			if(x % i == 0)
				return false;
		}
		return true;
	}
}
