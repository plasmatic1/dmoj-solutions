import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class APBHard {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int zero = '0';
		
		for(int i = 0; i < N; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			String a = token.nextToken(), b = token.nextToken();
			
			if(a.startsWith("-")){
				String t = a;
				a = b;
				b = t;
			}
			
			boolean neg = b.startsWith("-") ? !(b.startsWith("-") && a.startsWith("-")) : false;
			
			if(neg){
				b = b.substring(1);
			}
			else if(a.startsWith("-") && b.startsWith("-")){
				a = a.substring(1);
				b = b.substring(1);
			}
			
			int al = a.length(), bl = b.length();
			
			if(al > bl){
				b = zeros(a.length()).substring(al - bl - 1) + b;
			}
			else if(al < bl){
				a = zeros(b.length()).substring(bl - al - 1) + b;
				al = bl;
			}
			
//			System.out.println("before");
//			System.out.println(a);
//			System.out.println(b);
//			System.out.println(neg);
			
			char[] aca = a.toCharArray(), bca = b.toCharArray();
			int[] aa = new int[al], ba = new int[al], f = new int[al];
			for(int j = 0; j < al; j++){
				aa[j] = aca[j] - zero;
				ba[j] = bca[j] - zero;
			}
			
			for(int j = al - 1; j >= 0; j--){
				f[j] = neg ? aa[j] - ba[j] : aa[j] + ba[j];
			}
			
//			System.out.println(Arrays.toString(f));
			
			int extra = Integer.MAX_VALUE;
			
			for(int j = al - 1; j >= 0; j--){
				if(f[j] > 10){
					if(j == 0){
						extra = 1;
						f[j] -= 10;
					}
					else{
						f[j] -= 10;
						f[j - 1]++;
					}
				}
				else if(f[j] < 0){
					if(j == 0){
//						f[j]++;
					}
					else{
						f[j] = -f[j];
						f[j - 1]--;
					}
				}
			}
			
//			System.out.print(extra);
//			System.out.println(Arrays.toString(f));
			
			String result = "";
			
			for(int j = 0; j < al; j++){
				result += Integer.toString(f[j]);
			}
			
			if(extra != Integer.MAX_VALUE){
				result = extra + result;
			}
			
			if(result.startsWith("0")){
				result = result.substring(1);
			}
			
			System.out.println(result);
		}
	}
	
	static String zeros(int x){
		return x < 2 ? "0" : "0" + zeros(x - 1);
	}
}
