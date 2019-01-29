import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class HiddenPalindromes {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String input = br.readLine();
		int max = 0;
		
		for(int i = 0; i < input.length(); i++){
			for(int j = i + 1; j <= input.length(); j++){
				//System.out.println(input.substring(i, j));
				if(isPalindrome(input.substring(i, j))){
					int size = j - i;
					if(size > max)
						max = size;
				}
			}
		}
		
		System.out.println(max);
	}
	
	static boolean isPalindrome(String s){
		return new StringBuilder(s).reverse().toString().equals(s);
	}
}
