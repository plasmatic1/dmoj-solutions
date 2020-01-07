import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class IOI101 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s = br.readLine();
		System.out.println(s.replaceAll("0", "O").replaceAll("1", "l").replaceAll("3", "E")
				.replaceAll("4", "A").replaceAll("5", "S").replaceAll("6", "G").replaceAll("8", "B")
				.replaceAll("9", "g"));
	}
}