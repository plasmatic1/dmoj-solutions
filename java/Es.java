

public class Es {
	static e point(int v) {
		return new e(v, -1);
	}

	private static class e implements Comparable<e> {
		int p;
		int d;

		public e(int p, int d) {
			this.p = p;
			this.d = d;
		}

		@Override
		public int compareTo(e arg0) {
			return Integer.compare(this.d, arg0.d);
		}

		@Override
		public boolean equals(Object other) {
			if (!(other instanceof e)) {
				return false;
			}
			return this.p == ((e) other).p;
		}

		@Override
		public String toString() {
			return "(P: " + this.p + " | D: " + this.d + ")";
		}
	}
}
