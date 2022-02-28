import java.util.*;

public class Main {  
  static int N, K;
  static int[] pos;

  static boolean check(int H) {
    for (int i = 0; i < N; i++) {
      int useHydrant = 0, lastHydrantRight = -1000000000;
      for (int j = 0; j < N; j++) {
        int x = pos[(i + j) % N];
        if (x < pos[i]) x += 1000000;

        if (lastHydrantRight < x) {
          lastHydrantRight = x + 2 * H;
          useHydrant++;
        }
      }

      if (useHydrant <= K) return true;
    }

    return false;
  }

  public static void main(String args[]) { 
    Scanner sc = new Scanner(System.in);

    // System.out.println("What is N?: ");
    N = sc.nextInt();
    pos = new int[N];
    for (int i = 0; i < N; i++)
      pos[i] = sc.nextInt();
    K = sc.nextInt();
    
    Arrays.sort(pos);
    
    int l = 0, r = 1000000, ans = -1;

    while (l <= r) {
      int mid = (l + r) / 2;

      if (check(mid)) {
        r = mid-1;
        ans = mid;
      }
      else {
        l = mid+1;
      }
    }

    System.out.println(ans);
  } 
}