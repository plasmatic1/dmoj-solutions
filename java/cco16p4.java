import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

public class OCanada {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine()), q = Integer.parseInt(br.readLine());
		HashMap<Integer, Integer> counts = new HashMap<>();
		for(int i = 0; i < q; i++){
			boolean[][] test = new boolean[n][n];
			for(int j = 0; j < n; j++){
				char[] s = br.readLine().toCharArray();
				for(int k = 0; k < n; k++){
					test[j][k] = s[k] == 'R';
				}
			}
			int sig = unique(test);
			if(counts.containsKey(sig)){
				counts.put(sig, counts.get(sig) + 1);
			}
			else{
				counts.put(sig, 1);
			}
		}
		
		int sum = counts.values().stream().map(o -> o * (o - 1) / 2).reduce(0, (a, b) -> a + b);
		System.out.println(sum);
	}
	
	static int unique(boolean[][] arr){
		String fin = "";
		int l = arr.length, lTC = l - 1;
		for(int i = 0; i < lTC; i++){
			for(int j = 0; j < lTC; j++){
				if(!arr[i][j]){
					//SWAP
					arr[i][j] = !arr[i][j];
					arr[i + 1][j] = !arr[i + 1][j];
					arr[i][j + 1] = !arr[i][j + 1];
					arr[i + 1][j + 1] = !arr[i + 1][j + 1];
				}
			}
		}
		
		for(int i = 0; i < l; i++){
			fin += arr[l - 1][i] ? 1 : 0; 
		}
		
		for(int i = l - 2; i >= 0; i--){
			fin += arr[i][l - 1] ? 1 : 0;
		}
		
		return Integer.parseInt(fin, 2);
	}
}