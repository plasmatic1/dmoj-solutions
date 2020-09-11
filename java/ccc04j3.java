import java.util.Scanner;

public class ccc04j3 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int adjectiveAmount = sc.nextInt();
		int nounAmount = sc.nextInt();
		
		String[] adjectives = new String[adjectiveAmount];
		String[] nouns = new String[nounAmount];
		
		for(int i = 0; i < adjectiveAmount; i++)
			adjectives[i] = sc.next();
		for(int i = 0; i < nounAmount; i++)
			nouns[i] = sc.next();
		
		sc.close();
		
		for(String adjective : adjectives){
			for(String noun : nouns)
				System.out.println(adjective + " as " + noun);
		}
	}
}