
import static java.lang.System.out;

public class Java2c {
    public native int square(int n);

		static {
				// just executed once
        System.loadLibrary("square");
		}

    public static void main(String[] args) {
				final String arch = System.getProperty("os.arch");
        out.println("Ho, Azorg@" + arch);

        final Java2c j2c = new Java2c();
				final int val = j2c.square(3);
        out.println(String.format("square(%d)=%d", 3, val));
    }
}
