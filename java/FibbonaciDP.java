public class FibbonaciDP {
	static long[] nums;
	
	public static void main(String[] args) {
		int max = 1000;
		nums = new long[max];
		nums[0] = 0;
		nums[1] = 1;
		
		for(int i = 0; i < max; i++){
			System.out.printf("fib(%d) = %d\n", i, fib(i));
		}
	}
	
	static long fib(int x){
		if(x < 2){
			return nums[x];
		}
		if(nums[x] != 0){
			return nums[x];
		}
		return nums[x] = fib(x - 1) + fib(x - 2);
	}
}
