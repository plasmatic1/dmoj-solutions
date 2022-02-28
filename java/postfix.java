import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class PostFix {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] input = br.readLine().split(" ");
		Stack<Double> numbers = new Stack<Double>();
		
		for(String op : input){
			try{
				numbers.push(Double.parseDouble(op));
			}
			catch(NumberFormatException e){
				double b = numbers.pop(), a = numbers.pop();
				
				if(op.equals("+"))
					numbers.push(a + b);
				else if(op.equals("-"))
					numbers.push(a - b);
				else if(op.equals("*"))
					numbers.push(a * b);
				else if(op.equals("/"))
					numbers.push(a / b);
				else if(op.equals("%"))
					numbers.push(a % b);
				else if(op.equals("^"))
					numbers.push(Math.pow(a, b));
			}
		}
		
		System.out.printf("%.1f", numbers.pop());
	}
}