import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.StringTokenizer;

public class ac19p5 {
	static int N;
	static int[][] grid, dis;
	
	public static void main(String[] args) throws IOException {
//		Scanner sc = new Scanner(System.in);
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//	   N = readInt();
		N = Integer.parseInt(br.readLine());
	   grid = new int[N][N];
	   dis = new int[N][N];
	   
	   for (int i = 0; i < N; i++) {
		   StringTokenizer st = new StringTokenizer(br.readLine());
		   for (int j = 0; j < N; j++) {
			   dis[i][j] = Integer.MAX_VALUE;
//			   grid[i][j] = readInt();
//			   grid[i][j] = sc.nextInt();
			   grid[i][j] = Integer.parseInt(st.nextToken());
		   }
	   }
	   
	   int mx = 0;
	   for (int i = 0; i < N; i++) {
		   for (int j = 0; j < N; j++) {
			   mx = Math.max(mx, dfs(i, j));
//			   System.out.printf("i=%d j=%d dis=%d\n", i, j, dis[i][j]);
		   }
	   }
	   
	   System.out.println(mx - 1);
	   
//	   exit();
//	   sc.close();
	}

	private static int dfs(int i, int j) {
		if (dis[i][j] != Integer.MAX_VALUE) return dis[i][j];
		
		dis[i][j] = 0;
		if (i + 1 < N && grid[i + 1][j] > grid[i][j])
			dis[i][j] = Math.max(dis[i][j], dfs(i + 1, j));
		if (i - 1 >= 0 && grid[i - 1][j] > grid[i][j])
			dis[i][j] = Math.max(dis[i][j], dfs(i - 1, j));
		if (j + 1 < N && grid[i][j + 1] > grid[i][j])
			dis[i][j] = Math.max(dis[i][j], dfs(i, j + 1));
		if (j - 1 >= 0 && grid[i][j - 1] > grid[i][j])
			dis[i][j] = Math.max(dis[i][j], dfs(i, j - 1));
		
		return ++dis[i][j];
	}

	final private static int BUFFER_SIZE = 1 << 16;
	private static DataInputStream din = new DataInputStream(System.in);
	private static byte[] buffer = new byte[BUFFER_SIZE];
	private static int bufferPointer = 0, bytesRead = 0;
	static PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

	public static String readLine() throws IOException {
		byte[] buf = new byte[1000000]; // line length
		int cnt = 0, c;
		while ((c = Read()) != -1) {
			if (c == '\n')
				break;
			buf[cnt++] = (byte) c;
		}
		return new String(buf, 0, cnt);
	}

	public static String read() throws IOException {
		byte[] ret = new byte[1024];
		int idx = 0;
		byte c = Read();
		while (c <= ' ') {
			c = Read();
		}
		do {
			ret[idx++] = c;
			c = Read();
		} while (c != -1 && c != ' ' && c != '\n' && c != '\r');
		return new String(ret, 0, idx);
	}

	public static int readInt() throws IOException {
		int ret = 0;
		byte c = Read();
		while (c <= ' ')
			c = Read();
		boolean neg = (c == '-');
		if (neg)
			c = Read();
		do {
			ret = ret * 10 + c - '0';
		} while ((c = Read()) >= '0' && c <= '9');

		if (neg)
			return -ret;
		return ret;
	}

	public static long readLong() throws IOException {
		long ret = 0;
		byte c = Read();
		while (c <= ' ')
			c = Read();
		boolean neg = (c == '-');
		if (neg)
			c = Read();
		do {
			ret = ret * 10 + c - '0';
		} while ((c = Read()) >= '0' && c <= '9');
		if (neg)
			return -ret;
		return ret;
	}

	public static double readDouble() throws IOException {
		double ret = 0, div = 1;
		byte c = Read();
		while (c <= ' ')
			c = Read();
		boolean neg = (c == '-');
		if (neg)
			c = Read();

		do {
			ret = ret * 10 + c - '0';
		} while ((c = Read()) >= '0' && c <= '9');

		if (c == '.') {
			while ((c = Read()) >= '0' && c <= '9') {
				ret += (c - '0') / (div *= 10);
			}
		}

		if (neg)
			return -ret;
		return ret;
	}

	private static void fillBuffer() throws IOException {
		bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
		if (bytesRead == -1)
			buffer[0] = -1;
	}

	private static byte Read() throws IOException {
		if (bufferPointer == bytesRead)
			fillBuffer();
		return buffer[bufferPointer++];
	}

	public void close() throws IOException {
		if (din == null)
			return;
		din.close();
	}

	static void print(Object o) {
		pr.print(o);
	}

	static void println(Object o) {
		pr.println(o);
	}

	static void flush() {
		pr.flush();
	}

	static void println() {
		pr.println();
	}

	static void exit() throws IOException {
		din.close();
		pr.close();
		System.exit(0);
	}
}