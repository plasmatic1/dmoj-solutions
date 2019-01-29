import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class FloorPlan {
	static List<Integer> rooms = new ArrayList<Integer>();
	static ArrayList<Integer>[] matrix;
	static int N;
	static int C;
	static int R;
	
	@SuppressWarnings("unchecked")
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		R = Integer.parseInt(br.readLine());
		C = Integer.parseInt(br.readLine());
		matrix = new ArrayList[R];
		
		for(int i = 0; i < R; i++){
			ArrayList<Integer> row = new ArrayList<Integer>();
			char[] rs = br.readLine().toCharArray();
			
			for(int j = 0; j < rs.length; j++){
				if(rs[j] == 'I')
					row.add(j);
			}
			matrix[i] = row;
		}
		
		for(int i = 0; i < R; i++){
			for(int j = 0; j < C; j++){
				if(!matrix[i].contains(j))
					rooms.add(getRoom(i, j));
			}
		}
		rooms.sort(Integer::compareTo);
		Collections.reverse(rooms);
		
		int roomsFilled = 0;
		
		for(int room : rooms){
			if(N >= room){
				roomsFilled++;
				N -= room;
			}
			else
				break;
		}
		
		if(roomsFilled == 1)
			System.out.printf("%d room, %d square metre(s) left over\n", roomsFilled, N);
		else
			System.out.printf("%d rooms, %d square metre(s) left over\n", roomsFilled, N);
	}
	
	public static int getRoom(int cr, int cc){
		//System.out.printf("(%d, %d) -> %s\n", cr, cc, matrix[cr].contains(cc) ? "I" : ".");
		if(matrix[cr].contains(cc))
			return 0;
		
		matrix[cr].add(cc);
		return 1 + (cr < R - 1 ? getRoom(cr + 1, cc) : 0) + 
				(cr > 0 ? getRoom(cr - 1, cc) : 0) + 
				(cc < C - 1 ? getRoom(cr, cc + 1) : 0) + 
				(cc > 0 ? getRoom(cr, cc - 1) : 0);
	}

}
