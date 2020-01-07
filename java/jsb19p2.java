import java.lang.reflect.Method;

public class JSP2 {
	public static void main(String[] args) {
		new java.util.Timer().schedule(new java.util.TimerTask() {

			public void run() {
				try {
					Class cls = Class.forName("Secret");
//		System.out.println(Arrays.toString(cls.getMethods()));
					Method m = cls.getDeclaredMethod("flag");
					m.setAccessible(true);
					m.invoke(cls.newInstance());
					System.exit(0);

				} catch (java.lang.Exception e) {
					System.exit(-65);
				}
			}

		}, 0L);
	}
}