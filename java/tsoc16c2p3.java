import java.util.Scanner;
import java.math.BigInteger;

public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int A = sc.nextInt(), B = sc.nextInt(), C = sc.nextInt(), D = sc.nextInt();
        long tot = 0;
        for (int i = A; i <= B; i++) {
            if (BigInteger.valueOf(i).isProbablePrime(25)) {
                tot += sumUnder(i, D) - sumUnder(i, C - 1);
                tot = (tot + 2016420) % 2016420;
            }
        }
        System.out.println(tot);
    }
    
    static long sumUnder(long prime, long x) {
        long times = x / prime;
        long ret = times * (times + 1) / 2;
        ret %= 2016420;
        ret *= prime;
        return ret % 2016420;
    }
}