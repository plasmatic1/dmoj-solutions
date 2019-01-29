import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Boolean {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] a = br.readLine().split(" ");
		int l = a.length;
		boolean b = a[l - 1].equals("True");
		System.out.println((l - 1) % 2 == 0 ? b : !b + "");
	}
}
