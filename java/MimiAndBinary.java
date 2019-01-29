import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class MimiAndBinary {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		char[] s = br.readLine().toCharArray();
		int l = s.length, curr = 0, curr0 = 0;
		int[] zeros = new int[l], ones = new int[l];
		for(int i = 0; i < l; i++){
			if(s[i] == '1'){
				curr++;
			}
			if(s[i] == '0'){
				curr0++;
			}
			ones[i] = curr;
			zeros[i] = curr0;
		}
		System.out.println("Ones: " + Arrays.toString(ones));
		System.out.println("Zeros: " + Arrays.toString(zeros));
		int q = Integer.parseInt(br.readLine());//, totalc = ones[l - 1], totalc0 = zeros[l - 1];
		for(int i = 0; i < q; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int x = Integer.parseInt(token.nextToken()), y = Integer.parseInt(token.nextToken()),
					z = token.nextToken().charAt(0) - '0';
			if(z == 1){
				System.out.println("Val to search for: " + (y + ones[x - 1] - 1));
				System.out.println(Arrays.binarySearch(ones, y + ones[x - 1] - 1));
			}
			else{
				System.out.println("Val to search for: " + (y + zeros[x - 1] - 1));
				System.out.println(Arrays.binarySearch(zeros, y + zeros[x - 1] - 1));
			}
		}
	}
}