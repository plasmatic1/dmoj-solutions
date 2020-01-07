import java.lang.reflect.Method;
import java.util.Timer;
import java.util.TimerTask;

public class JSBP3 {
	public static void main(String[] args) {
		new Thread(() -> {
			try {
				Class cls = Class.forName("Secret");
				Method m = cls.getDeclaredMethod("flag");
				m.invoke(null);
				System.exit(0);
			} catch (java.lang.Exception e) {
				e.printStackTrace();
				System.exit(-1);
			}
		}).start();
	}
}