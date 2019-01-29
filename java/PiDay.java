import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PiDay {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int pies = Integer.parseInt(br.readLine());
		int users = Integer.parseInt(br.readLine());
		
		int[][] table = new int[users][pies + 1];
	}
}
