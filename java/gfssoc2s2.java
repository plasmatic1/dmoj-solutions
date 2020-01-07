import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.util.stream.Collectors;

public class Hearthstone {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<Card> cards = new ArrayList<Card>();
		StringTokenizer tokens = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(tokens.nextToken()), T = Integer.parseInt(tokens.nextToken());
		
		for(int i = 0; i < N; i++){
			StringTokenizer tokenss = new StringTokenizer(br.readLine());
			cards.add(new Card(tokenss.nextToken(), Integer.parseInt(tokenss.nextToken())));
		}
		cards.sort(Card::compareTo);
		
		ArrayList<Integer> costs = new ArrayList<Integer>();
		costs.addAll(cards.stream().map(Card::getCost).collect(Collectors.toList()));
		
		for(int i = 0; i < N; i++){
			for(int j = i; j < N; j++){
				if(j == i)
					continue;
				
				for(int k = j; k < N; k++){
					if(k == j || k == i)
						continue;
					
					if((costs.get(i) + costs.get(j) + costs.get(k)) <= T){
						String[] cardl = {cards.get(i) + "", cards.get(j) + "", cards.get(k) + ""};
						Arrays.sort(cardl, String::compareTo);
						System.out.println(Arrays.stream(cardl)
								.collect(Collectors.joining(" ")));
					}
				}
			}
		}
	}
}

class Card implements Comparable<Card>{
	private String name;
	private int cost;
	
	public Card(String name, int cost){
		this.name = name;
		this.cost = cost;
	}
	
	@Override
	public String toString(){
		return name;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getCost() {
		return cost;
	}
	
	@Override
	public int compareTo(Card other){
		return this.name.compareTo(other.getName());
	}

	public void setCost(int cost) {
		this.cost = cost;
	}
}