import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class HighLowTide {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		String[] tS = br.readLine().split(" ");
		int[] tides = new int[N];
		for(int i = 0; i < N; i++)
			tides[i] = Integer.parseInt(tS[i]);
		Arrays.sort(tides);
		int mid = N / 2 + (N % 2 == 0 ? 0 : 1);
		int max = N - mid + (N % 2 == 0 ? 0 : 1);
		if(N == 1)
			System.out.println(tides[0]);
		else
			System.out.printf("%d %d", tides[mid - 1], tides[mid]);
		if(N > 2)
			for(int i = 1; i < max; i++){
				if(mid + i < N)
					System.out.printf(" %d %d", tides[mid - i - 1], tides[mid + i]);
				else
					System.out.printf(" %d", tides[mid - i - 1]);
			}
	}
}