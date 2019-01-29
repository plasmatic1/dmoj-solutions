import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class TrickOrTreeing {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		for(int i = 0; i < 5; i++){
			String line = br.readLine();
			String noBrackets = line.replaceAll("[\\(\\)]", "");
			int bracketCount = line.length() - noBrackets.length();
			StringTokenizer token = new StringTokenizer(noBrackets);
			int total = 0;
			while(token.hasMoreTokens()){
				total += Integer.parseInt(token.nextToken());
			}
			
			System.out.printf("%d %d\n", bracketCount * 2 - (bracketCount / 2), total);
		}
	}
}
