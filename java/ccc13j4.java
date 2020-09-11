import java.util.Arrays;
import java.util.Scanner;

public class ccc13j4 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int maxtime = sc.nextInt();
		int[] activities = new int[sc.nextInt()];
		
		for(int i = 0; i < activities.length; i++)
			activities[i] = sc.nextInt();
		
		sc.close();
		
		Arrays.sort(activities);
		
		int sum = 0;
		int maxactivities = 0;
		
		for(int i : activities){
			sum += i;
			
			if(sum > maxtime) break;
			
			maxactivities++;
		}
		
		System.out.println(maxactivities);
	}
}