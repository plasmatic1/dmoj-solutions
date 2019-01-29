import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.stream.Collectors;

public class PhoneMicrowave {
	public static void main(String[] args) throws NumberFormatException, IOException {
		final int[] max = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int S = Integer.parseInt(br.readLine());
		StringTokenizer tokens = new StringTokenizer(br.readLine(), " ");
		Integer[] ymd = Arrays.stream(tokens.nextToken().split("/"))
				.map(Integer::parseInt)
				.collect(Collectors.toList())
				.toArray(new Integer[0]), 
			hms = Arrays.stream(tokens.nextToken().split(":"))
			.map(Integer::parseInt)
			.collect(Collectors.toList())
			.toArray(new Integer[0]);
		
		//System.out.println(Arrays.toString(ymd) + " | " + Arrays.toString(hms));
		
		while(S > 0){
			if(hms[0] > 1)
				hms[0]--;
			else{
				hms[0] = 24;
				if(ymd[2] > 1)
					ymd[2]--;
				else{
					ymd[2] = ymd[1] == 1 ? max[11] : max[ymd[1] - 2];
					//System.out.println(ymd[2]);
					
					if(ymd[1] > 1)
						ymd[1]--;
					else{
						ymd[1] = 12;
						ymd[0]--;
					}
				}
			}
			
			S--;
		}
		
		if(hms[0] == 24){
			if(ymd[2] == 31)
				hms[0]--;
			else{
				ymd[2]++;
				hms[0] = 0;
			}
		}
		
		System.out.printf("%d/%02d/%02d %02d:%02d:%02d\n", ymd[0], ymd[1], ymd[2], hms[0], hms[1], hms[2]);
	}
}
