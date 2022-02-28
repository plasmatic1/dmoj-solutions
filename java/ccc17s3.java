import java.util.*;

public class Main {  
  public static void main(String args[]) { 
    Scanner sc = new Scanner(System.in);

    // System.out.println("What is N?: ");
    int N = sc.nextInt();
    int[] fre = new int[2001];
    for (int i = 0; i < N; i++)
      fre[sc.nextInt()]++;

    int[] ans = new int[4001];
    for (int i = 0; i <= 2000; i++) {
      for (int j = i; j <= 2000; j++) {
        if (i != j) {
          ans[i + j] += Math.min(fre[i], fre[j]);
        }
        else {
          ans[i + j] += fre[i] / 2;
        }
      }
    }

    int maxLength = 0, ansCount = 0;
    for (int i = 2; i <= 4000; i++) {
      int cur = ans[i];

        // if (i <= 10)
        //   System.out.printf("i=%d cur=%d\n", i, cur);

      if (cur > maxLength) {
        maxLength = cur;
        ansCount = 1;
      }
      else if (cur == maxLength)
        ansCount++;
    }

    System.out.printf("%d %d\n", maxLength, ansCount);
  } 
}