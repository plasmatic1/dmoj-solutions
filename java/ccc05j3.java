import java.util.Scanner;
import java.util.Stack;

public class ccc05j3 {
	static final String EXIT = "SCHOOL";
	
	public static void main(String[] args) {
		Stack<Instruction> ds = new Stack<Instruction>();
		Scanner in = new Scanner(System.in);
		
		String dd = in.nextLine();
		ds.add(new Instruction(dd, "HOME"));
		
		while(true){
			String r = in.nextLine();
			if(r.equals(EXIT))
				break;
			
			String d = in.nextLine();
			
			ds.add(new Instruction(d, r));
		}
		
		while(!ds.isEmpty()){
			if(ds.size() == 1){
				out("Turn " + Dir.swap(ds.pop().d()).as() + " into your HOME.");
				break;
			}
			else{
				Instruction i = ds.pop();
				
				out("Turn " + Dir.swap(i.d()).as() + " onto " + i.r() + " street.");
			}
		}
		
		in.close();
	}
	
	static void out(Object o){
		System.out.println(o);
	}
}

class Instruction{
	private Dir d;
	private String r;
	
	public Instruction(String d, String r){
		this.d = Dir.getDir(d);
		this.r = r;
	}
	
	public Dir d(){
		return d;
	}
	
	public String r(){
		return r;
	}
}

enum Dir{
	R("RIGHT"),
	L("LEFT");
	
	private String s;
	
	Dir(String s){
		this.s = s;
	}

	public String as() {
		return s;
	}
	
	public static Dir getDir(String s){
		switch(s){
		case "R":
			return Dir.R;
		case "L":
			return Dir.L;
		default:
			return Dir.L;
		}
	}
	
	public static Dir swap(Dir d){
		switch(d){
		case L:
			return R;
		case R:
			return L;
		default:
			return L;
		}
	}
}