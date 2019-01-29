import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.stream.Collectors;

public class UnicodeGen {
	static final String USAGE = "Argument pattern: <shortcut (using ctrl, alt, and shift) <script file name (w/o extension)> <string...>"
			+ "\nExample: ctrll lenny ( ͡° ͜ʖ ͡°)";
	
	public static void main(String[] args) throws FileNotFoundException {
		String type = conv(args[0]);
		
		if(args.length < 3){
			System.out.println(USAGE);
			return;
		}
		
		String lenny = Arrays.stream(Arrays.copyOfRange(args, 2, args.length)).collect(Collectors.joining(" "));
		String fileN = args[1];
		
		File file = new File(System.getenv("user.dir") + File.pathSeparator + fileN + ".ahk");
		PrintStream stream = new PrintStream(new FileOutputStream(file));
		System.setOut(stream);
		
		System.out.printf("%s%s::\n", type, args[1]);
		for(char c : lenny.toCharArray())
			System.out.printf("SEND {U+%s}\n", Integer.toHexString((int) c).toUpperCase());
		System.out.println("RETURN;\n");
	}

	private static String conv(String string) {
		return string.replaceAll("ctrl", "^").replaceAll("alt", "!")
				.replaceAll("shift", "+");
	}
}