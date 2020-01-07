import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Wowow {
	public static final int MAX = 1048577, MP2 = 1048576;
	static int n, fn = 0, bfriend, brank, rnk_ptr = 1;
	static int[] friends = new int[MAX], 
			rank_mp = new int[MAX], 
			tree = new int[MAX], 
			ranks = new int[MAX];
	static char instru;
	static instruct[] instructs = new instruct[MAX];

	static void add(int x, int z){
		for(; x <= MAX; x += x & -x){
			tree[x] += z;
		}
	}

	int sum(int x){
		int sum = 0;

		for(; x > 0; x -= x & -x){
			sum = sum + tree[x];
		}

		return sum;
	}

	static int index_of(int rank){
		return Arrays.binarySearch(rank_mp, 0, rnk_ptr, rank);
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		rank_mp[0] = Integer.MIN_VALUE;
		
		n = Integer.parseInt(br.readLine());

		for (int i = 0; i < n; ++i) {
			StringTokenizer token = new StringTokenizer(br.readLine());
			instru = token.nextToken().charAt(0);

			if(instru == 'Q'){
				brank = Integer.parseInt(token.nextToken());

				instructs[i] = new instruct(instru, -1, brank);
			}
			else{
				bfriend = Integer.parseInt(token.nextToken());
				brank = Integer.parseInt(token.nextToken());

				instructs[i] = new instruct(instru, bfriend, brank);
				rank_mp[rnk_ptr++] = brank;
			}
		}

		Arrays.sort(rank_mp, 0, rnk_ptr);

		for (int i = 0; i < n; ++i) {
			char ins = instructs[i].ins;
			int rnk = instructs[i].rnk, fri = instructs[i].fri;

			if(ins == 'N'){
				rnk = index_of(rnk);
				
				ranks[rnk] = fri;
				friends[fri] = rnk;

				add(rnk, 1);
				fn++;
			}
			else if(ins == 'M'){
				rnk = index_of(rnk);

				add(friends[fri], -1);

				friends[fri] = rnk;
				ranks[rnk] = fri;

				add(rnk, 1);
			}
			else{
				//instru == 'Q'

				rnk = fn - rnk;
				int skill = 0, total = 0;

				for (int j = MP2; j > 0; j >>= 1) {
					int alt = skill | j;
					if(total + tree[alt] <= rnk){
						skill = alt;
						total += tree[alt];
					}
				}

				System.out.println(ranks[skill + 1]);
			}
		}
	}
	
	static class instruct{
		char ins;
		int fri, rnk;
		
		public instruct(char ins, int fri, int rank){
			this.ins = ins;
			this.fri = fri;
			this.rnk = rank;
		}
	}
}