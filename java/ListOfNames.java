import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ListOfNames {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int[] a = new int[20];
		for(int i = 0; i < N; i++){
			char[] c = br.readLine().toCharArray();
			for(int j = 0; j < c.length; j++)
				a[j] += (int)c[j];
		}
		for(int i = 1; i < N; i++){
			char[] c = br.readLine().toCharArray();
			for(int j = 0; j < c.length; j++)
				a[j] -= (int)c[j];
		}
		for(int x : a){
			if(x == 0)
				break;
			System.out.print((char)x);
		}
	}
}
