import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Collection;
import java.util.HashMap;
import java.util.StringTokenizer;

public class NailedIt {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		HashMap<Integer, Integer> map = new HashMap<Integer, Integer>();
		int N = Integer.parseInt(br.readLine());
		int[] arr = new int[N];
		StringTokenizer tokens = new StringTokenizer(br.readLine());
		
		for(int i = 0; i < N; i++){
			arr[i] = Integer.parseInt(tokens.nextToken());
		}
		
		for(int i = 0; i < N; i++){
			for(int j = i + 1; j < N; j++){
				int x = arr[i] + arr[j];
				Integer e = map.get(x);
				if(e == null)
					map.put(x, 1);
				else
					map.put(x, e + 1);
			}
		}
		
		int max = 0, maxC = 0;
		Collection<Integer> values = map.values();
		
		System.out.println(map);
		System.out.println(values);
		
		for(int i : values){
			if(i > max)
				max = i;
		}
		
		for(int i : values){
			if(i == max)
				maxC++;
		}
		
		System.out.printf("%d %d\n", max, maxC);
	}
}
