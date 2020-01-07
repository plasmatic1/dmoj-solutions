import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Arrays;

public class JSP1 {
	public static void main(String[] args) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, ClassNotFoundException, InstantiationException {
		Class cls = Class.forName("Secret");
//		System.out.println(Arrays.toString(cls.getMethods()));
		Method m = cls.getDeclaredMethod("flag");
		m.setAccessible(true);
		m.invoke(cls.newInstance());
	}
}