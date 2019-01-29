import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.HashMap;

public class Rocks {

	static final int MAX = 10001;
	static int n = 0, c;
	static int[] values = new int[MAX], tree = new int[MAX];
	static char bi;
	static String ba, bb;
	static HashMap<String, Integer> rockmap = new HashMap<>();

	static void add(int x, int z){
		for(; x < MAX; x += x & -x){
			tree[x] += z;
		}
	}

	static void setv(int x, int z){
		add(x, z - values[x]);
		values[x] = z;
	}

	static int sum(int x){
		int summ = 0;

		for(; x > 0; x -= x & -x){
			summ += tree[x];
		}

		return summ;
	}

	static final int A = (int)('a') - 1;
	static int get_val(String str){
		int sum = 0;

		for(int i = 0; i < str.length(); i++){
			sum += (int)(str.charAt(i)) - A;
		}

		return sum;
	}

	public static void main(String[] args) throws IOException{
		c = readInt();

		for (int i = 0; i < c; ++i) {
			bi = read().charAt(0);

			if(bi == 'A'){
				ba = read();

				if(rockmap.containsKey(ba)){
					println("Can't add " + ba);
					continue;
				}

				rockmap.put(ba, ++n);
				setv(n, get_val(ba));
			}
			else if(bi == 'S'){
				ba = read();
				bb = read();

				int l = rockmap.get(ba), r = rockmap.get(bb);

				rockmap.put(ba, r);
				rockmap.put(bb, l);

				setv(r, get_val(ba));
				setv(l, get_val(bb));
			}
			else if(bi == 'M'){
				ba = read();
				bb = read();

				int l = rockmap.get(ba), r = rockmap.get(bb);

				if(l > r){
					int tmp = l;
					l = r;
					r = tmp;
				}

				println(sum(r) - sum(l - 1));
			}
			else if(bi == 'R'){
				ba = read();
				bb = read();

				int l = rockmap.remove(ba);

				rockmap.put(bb, l);
				setv(l, get_val(bb));
			}
			else{ //bi == N
				println(n);
			}
		}
		
		exit();
	}
	
	final private static int BUFFER_SIZE = 1 << 16;private static DataInputStream din = new DataInputStream(System.in);private static byte[] buffer = new byte[BUFFER_SIZE];private static int bufferPointer = 0, bytesRead = 0;static PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));public static String readLine() throws IOException {byte[] buf = new byte[1000000];int cnt = 0, c;while ((c = Read()) != -1) {if (c == '\n')break;buf[cnt++] = (byte) c;}return new String(buf, 0, cnt);}public static String read() throws IOException {byte[] ret = new byte[1024];int idx = 0;byte c = Read();while (c <= ' ') c = Read();do {ret[idx++] = c;c = Read();} while (c != -1 && c != ' ' && c != '\n' && c != '\r');return new String(ret, 0, idx);}public static int readInt() throws IOException {int ret = 0;byte c = Read();while (c <= ' ')c = Read();boolean neg = (c == '-');if (neg)c = Read();do {ret = ret * 10 + c - '0';} while ((c = Read()) >= '0' && c <= '9');if (neg)return -ret;return ret;}public static long readLong() throws IOException {long ret = 0;byte c = Read();while (c <= ' ')c = Read();boolean neg = (c == '-');if (neg)c = Read();do {ret = ret * 10 + c - '0';} while ((c = Read()) >= '0' && c <= '9');if (neg)return -ret;return ret;}public static double readDouble() throws IOException {double ret = 0, div = 1;byte c = Read();while (c <= ' ')c = Read();boolean neg = (c == '-');if (neg)c = Read();do {ret = ret * 10 + c - '0';} while ((c = Read()) >= '0' && c <= '9');if (c == '.') {while ((c = Read()) >= '0' && c <= '9') {ret += (c - '0') / (div *= 10);}}if (neg)return -ret;return ret;}private static void fillBuffer() throws IOException {bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);if (bytesRead == -1)buffer[0] = -1;}private static byte Read() throws IOException {if (bufferPointer == bytesRead)fillBuffer();return buffer[bufferPointer++];}public void close() throws IOException {if (din == null)return;din.close();}static void print(Object o) {pr.print(o);}static void println(Object o) {pr.println(o);}static void flush() {pr.flush();}static void println() {pr.println();}static void exit() throws IOException {din.close();pr.close();System.exit(0);}
}
