
import static java.lang.System.out;

public class Java2c {
    public native int square(int n);

		static {
				// just executed once
				final String os = System.getProperty("os.name");
				out.println(String.format("os='%s'", os));
				final String path = System.getProperty("java.library.path");
				out.println(String.format("java.library.path='%s'", path));
				if (os.startsWith("Windows"))
        	System.loadLibrary("libsquare");
				else
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
