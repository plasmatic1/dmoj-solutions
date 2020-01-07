import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ReJudging {

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		int N = Integer.parseInt(in.readLine());
		//int ac = 0;
		int wa = 0;
		//int tle = 0;
		//int ir = 0;
		int[] ocodes = new int[N];
		
		for(int i = 0; i < N; i++){
			String read = in.readLine();
			
			if(read.equals("AC")){
				//ac++;
				ocodes[i] = 0;
			}
			else if(read.equals("WA")){
				wa++;
				ocodes[i] = 1;
			}
			else if(read.equals("TLE")){
				//tle++;
				ocodes[i] = 2;
			}
			else if(read.equals("IR")){
				//ir++;
				ocodes[i] = 3;
			}
		}
		
		int wac = (int) (wa * 0.3);
		int irc = 20;
		
		for(int x : ocodes){
			if(x == 0)
				System.out.println("AC");
			else if(x == 1){
				if(wac > 0)
					System.out.println("AC");
				else
					System.out.println("WA");
				
				wac--;
			}
			else if(x == 2)
				System.out.println("WA");
			else if(x == 3){
				if(irc > 10)
					System.out.println("AC");
				else if(irc > 0)
					System.out.println("WA");
				else
					System.out.println("IR");
				
				irc--;
			}
		}
	}

}