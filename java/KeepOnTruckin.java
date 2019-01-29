import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class KeepOnTruckin {
	static int A, B, N, motels[], ogmotels[] = {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000}
	,total = 0;
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		A = Integer.parseInt(br.readLine());
		B = Integer.parseInt(br.readLine());
		N = Integer.parseInt(br.readLine());
		
		motels = new int[N + ogmotels.length];
		
		for(int i = N; i < motels.length; i++)
			motels[i] = ogmotels[i - N];
		
		for(int i = 0; i < N; i++)
			motels[i] = Integer.parseInt(br.readLine());
		
		get(0);
		System.out.println(total);
	}
	
	static void get(int current){
		if(current + A > 7000){
			total++;
			return;
		}
		
		for(int motel : motels){
			if(current > motel)
				continue;
			int diff = motel - current;
			
			if(diff >= A && diff <= B)
				get(motel);
		}
	}
}
