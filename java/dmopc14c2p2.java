import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class CuttingLogs {
	public static void main(String[] args) throws NumberFormatException, IOException{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<Integer> logs = new ArrayList<Integer>();
		
		int x = Integer.parseInt(in.readLine());
		char[] logss = in.readLine().toCharArray();
		
		int g = 0;
		for(int i = 0; i < x; i++){
			char c = logss[i];
			
			if(c == 'O'){
				g++;
				
				if(i == x - 1){
					logs.add(g);
					g = 0;
				}
			}
			else{
				if(g == 0)
					continue;
				
				logs.add(g);
				g = 0;
			}
		}
		
		System.out.println(logs.size());
		System.out.println(logs.stream().map(e -> genOs(e))
				.collect(Collectors.joining("\n")));
	}
	
	public static String genOs(int x){
		return x > 1 ? "O" + genOs(x - 1) : (x == 0 ? "" : "O");
	}
}