import java.util.*;

public class Main {  
  static boolean check(long N, int P, int Y, long T) {
    long cur = 0;
    for (int i = 0; i < Y; i++) {
      cur += N;
      cur = (cur * (100 + P)) / 100;
      cur = Math.min(cur, T); // prevent overflow
    }

    return cur == T;
  }

  public static void main(String args[]) { 
    Scanner sc = new Scanner(System.in);

    int P = sc.nextInt(), Y = sc.nextInt();
    long T = sc.nextLong();

    long l = 1, r = T, ans = -1;
    while (l <= r) {
      long mid = (l + r) / 2;
      if (check(mid, P, Y, T)) {
        ans = mid;
        r = mid-1;
      }
      else
        l = mid+1;
    }

    System.out.println(ans);
  } 
}