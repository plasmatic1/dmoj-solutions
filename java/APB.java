import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class APB {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		for(int i = 0; i < N; i++){
			StringTokenizer tokens = new StringTokenizer(br.readLine());
			System.out.println(Integer.parseInt(tokens.nextToken())
					+ Integer.parseInt(tokens.nextToken()));
		}
	}

}
