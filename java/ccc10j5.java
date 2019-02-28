import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class NightHop {
//not night witch lol
	static final int[] MX = {1, 2, 2, 1, -1, -2, -2, -1};
	static final int[] MY = {2, 1, -1, -2, -2, -1, 1, 2};
	
	public static void main(String[] args) {
		 Scanner sc = new Scanner(System.in);
		 int sx = sc.nextInt() - 1, sy = sc.nextInt() - 1, ex = sc.nextInt() - 1, ey = sc.nextInt() - 1;
		 
		 sc.close();
		 
		 //System.out.println(fromXY(sx, sy));
		 
		 Queue<Integer> next = new LinkedList<Integer>();
		 int[] levels = new int[64];
		 Arrays.fill(levels, -1);
		 int start = fromXY(sx, sy);
		 levels[start] = 0;
		 next.add(start);
		 
		 int finalLevel = 0;
		 
		 while(!next.isEmpty()){
			 int curr = next.poll();
			 int level = levels[curr];
			 boolean tb = false;
			 
			 for(int i = 0; i < MX.length; i++){
				 int mx = MX[i], my = MY[i];
				 int[] x = toXY(curr);
				 int cx = x[0], cy = x[1];
				 int tnx = cx + mx, tny = cy + my;
				 
				 //System.out.printf("(%d, %d) + (%d, %d) = (%d, %d) =? (%d, %d) {(%s)} [%d]\n", cx, cy, mx, my, tnx, tny, ex, ey, "" + ((tnx == ex) && (tny == ey)), level + 1);
				 
				 if(tnx < 0 || tnx > 7 || tny < 0 || tny > 7)
					 continue;
				 
				 int nnew = fromXY(tnx, tny);
				 
				 if(levels[nnew] != -1)
					 continue;
				 
				 if((tnx == ex) && (tny == ey)){
					 finalLevel = level + 1;
					 tb = true;
					 break;
				 }
				 
				 levels[nnew] = level + 1;
				 next.add(nnew);
			 }
			 
			 if(tb)
				 break;
		 }
		 
		 System.out.println(finalLevel);
	}
	
	static int fromXY(int x, int y){
		return x * 8 + y;
	}
	
	static int[] toXY(int pos){
		return new int[]{pos / 8, pos % 8};
		
	}
}