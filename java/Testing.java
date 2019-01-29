import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public 
  class 
  
                                Testing       { // To fuck ur shit up
  public static void main(String[] args) throws IOException{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    int n = Integer.parseInt(br.readLine());

    for(int i = 0; i < n; i++){
      String s = br.readLine();
      System.out.println(s);
    }

    br.close();
  }
}