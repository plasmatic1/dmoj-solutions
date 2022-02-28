import java.util.*;
import java.io.*;

public class Main {  
  static long gcd(long a, long b) {
    if (b == 0) return a;
    return gcd(b, a%b);
  }

  static long lcm(long a, long b) {
    return (a*b)/gcd(a, b);
  }

  public static void main(String args[]) throws IOException { 
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    StringTokenizer st = new StringTokenizer(br.readLine());

    int N = Integer.parseInt(st.nextToken()),
        Q = Integer.parseInt(st.nextToken());

    st = new StringTokenizer(br.readLine());

    int maxLength = 0;
    long[] lcms = new long[N+1];
    lcms[0] = 1;
    boolean done = false;
    for (int i = 1; i <= N; i++) {
      long x = Integer.parseInt(st.nextToken());

      if (!done) {
        lcms[i] = lcm(lcms[i-1], x); // associativity of LCM
        //System.out.printf("i=%d lcms=%d\n", i, lcms[i]);
        if (lcms[i] <= 1000000000L) {
          maxLength = i;
        }
        else {
          done = true;
        }
      }
    }

    //System.out.printf("maxLen=%d\n", maxLength);

    while (Q > 0) {
      int t = Integer.parseInt(br.readLine());

      if (t == 0) {
        System.out.println(-1);
      }
      else {
        int l = 1, r = maxLength, ans = maxLength + 1;
        while (l <= r) {
          int mid = (l + r) / 2;
          if (t % lcms[mid] != 0) {
            ans = mid;
            r = mid-1;
          }
          else
            l = mid+1;
        }

        if (ans > N) ans = -1;
        System.out.println(ans);
      }

      Q--;
    }
  } 
}