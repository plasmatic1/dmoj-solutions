import java.io.*;
import java.util.*;
   
public class Sorting{
   
    static class Pair implements Comparable<Pair>{
        int v, i;
        Pair(int v, int i){
            this.v = v;
            this.i = i;
        }
        @Override
        public int compareTo(Pair p) {
            return this.v-p.v;
        }
    }

    static Scanner sc = new Scanner(System.in);

    static long readInt() throws IOException{
        return sc.nextLong();
    }
   
    public static void main(String[] args) throws IOException {
        //StringTokenizer st = new StringTokenizer(br.readLine());
        int n = (int) readInt();
        long m = readInt();
        long K = readInt();
        int X = (int) readInt();
        Pair[] arr = new Pair[n];
        //st = new StringTokenizer(br.readLine());
        for (int i=0; i<n; i++) {
            arr[i] = new Pair((int) readInt(), i);
        }
        Arrays.sort(arr);
        long[] psa = new long[n];
        for (int i=0; i<n; i++) {
            psa[i] = arr[i].v;
            if (i>0) psa[i] += psa[i-1];
        }
        for (int i=0; i+X<=n; i++) {
            //System.out.println((i+X-2>=0?psa[i+X-2]:0)-(i==0?0:psa[i-1]));
            //System.out.println(psa[i+X-1]-(i==0?0:psa[i-1]));
            if ((i+X-2>=0?psa[i+X-2]:0)-(i==0?0:psa[i-1])+1<=K&&psa[i+X-1]-(i==0?0:psa[i-1])>=K) {
                boolean[] f = new boolean[n];
                int[] ans = new int[n];
                for (int j=0; j<X; j++) {
                    f[i+j] = true;
                    ans[arr[i+j].i] = j+1;
                }
                int cnt = X+1;
                for (int j=0; j<n; j++) {
                    if (!f[j]) {
                        ans[arr[j].i] = cnt;
                        cnt++;
                    }
                }
                for (int j=0; j<n; j++) {
                    System.out.print(ans[j]+" ");
                }
                return;
            }
        }
        System.out.println(-1);
        System.out.flush();
    }  
}