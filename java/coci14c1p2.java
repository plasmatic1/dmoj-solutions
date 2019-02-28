import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Klopka {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		int smallx = 101, smally = 101, largex = 0, largey = 0;
		for(int i = 0; i < N; i++){
			StringTokenizer token = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(token.nextToken()), b = Integer.parseInt(token.nextToken());
			if(a < smallx){
				smallx = a;
			}
			else if(a > largex){
				largex = a;
			}
			if(b < smally){
				smally = b;
			}
			else if(b > largey){
				largey = b;
			}
		}
		
//		System.out.printf("x: %d - %d | y: %d - %d | diffs: %d, %d\n", largex, smallx, largey, smally,
//				largex - smallx, largey - smally);
		
		int diff = Math.max(Math.abs(largex - smallx), Math.abs(largey - smally));
		System.out.println(diff * diff);
	}
}
