import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Bananas {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while(true){
			String input = br.readLine();
			if(input.equals("X"))
				break;
			
			ArrayList<Character> chars = new ArrayList<Character>();
			for(char c : input.toCharArray())
				chars.add(c);
			
			boolean hasModified = true;
			while(hasModified && !chars.isEmpty()){
				int foundB = -1;
				for(int i = 0; i < chars.size(); i++){
					char c = chars.get(i);
					hasModified = false;
					
					System.out.println(c);
					
					if(c == 'B'){
						foundB = i;
						System.out.println("found b");
					}
					else if(c == 'S' && foundB != -1){
						chars.remove(foundB);
						chars.remove(i - 1);
						hasModified = true;
						System.out.println("found s with b");
					}
					else if(chars.size() - i > 2){
						if(c == 'A' && (chars.get(i + 1) == 'N' && chars.get(i + 2) == 'A')){
							System.out.println("found ana");
							chars.remove(i);
							chars.remove(i);
							hasModified = true;
						}
					}
				}
			}
			
			String end = "";
			for(char c : chars)
				end += c;
			
			System.out.println(end.equals("A") ? "YES" : "NO");
		}
	}
}
