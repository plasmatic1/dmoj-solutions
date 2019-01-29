/*
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Debug {

	public static void main(String[] args) {
		A test = new A("quackingDuck");
		
		System.out.println(spit(test, 0, new StringBuilder(), true));
		System.out.println(spitClass(A.class));
	}
	
	public static String spitClass(Class<?> clazz){
		StringBuilder begins = new StringBuilder();
		
		begins.append("Class: " + clazz.getName() + " extends " + clazz.getSuperclass().getName() + " \n"
				+ "implements " + Arrays.stream(clazz.getInterfaces()).map(Class::getName).collect(Collectors.joining(", ")) + "\n"
				+ "Vars : \n");
		
		for(Field f : clazz.getFields()){
			begins.append("    " + Modifier.toString(f.getModifiers()) + " " + f.getType().getSimpleName() + " " + f.getName() + "\n");
		}
		
		begins.append("Methods : \n" + Arrays.stream(clazz.getMethods())
		.map(m -> "    " + m.getReturnType().getSimpleName() + " " + m.getName() + "(" + Arrays.stream(m.getParameterTypes())
				.map(Class::getSimpleName)
				.collect(Collectors.joining(", ")) + ")\n")
		.collect(Collectors.joining("")));
		
		return begins.toString();
	}
	
	public static String spit(Object obj, int indent, StringBuilder begins, boolean showMethods){
		Function<Object, Boolean> print = o -> o instanceof Integer || o instanceof Long || o instanceof Boolean || o instanceof Character
				|| o instanceof Short || o instanceof Double || o instanceof Byte || o instanceof Float || o instanceof String;
		
		Field[] fields = obj.getClass().getDeclaredFields();
		
		String indents = "";
		
		for(int i = 0; i < indent; i++)
			indents += "    ";
		
		for(Field f : fields){
			f.setAccessible(true);
			Object o = null;
			try {
				o = f.get(obj);
			} catch (Exception e){e.printStackTrace();}
			
			if(o == null)
				return begins.toString();
			
			if(o.getClass().isArray()){
				begins.append(indents + f.getName() + " : -> " + o.getClass().getSimpleName() + "\n");
				
				for(int i = 0; i < Array.getLength(o); i++){
					Object element = Array.get(o, i);
					
					if(element != null)
						if(!print.apply(element) || element.getClass().isArray()){
							begins.append(indents + "    " + i + " : -> " + element.getClass().getSimpleName() + "\n");
							
							if(!element.getClass().isArray())
								if(showMethods)
									begins.append(indents + "        Methods : " + Arrays.stream(element.getClass().getMethods())
									.map(m -> m.getReturnType().getSimpleName() + " " + m.getName() + "(" + Arrays.stream(m.getParameterTypes())
											.map(Class::getSimpleName)
											.collect(Collectors.joining(", ")) + ")")
									.collect(Collectors.joining(", ")) + "\n");
							
							spit(element, indent + 2, begins, showMethods); 
						}
					
					if(element != null)
						begins.append(indents + "    " + i + " : " + element + " -> " + element.getClass().getSimpleName() + "\n");
					else
						begins.append(indents + "    " + i + " : null\n");
				}
				begins.append(indents + "    length : " + Array.getLength(o) + "\n");
			}
			else if(print.apply(o))
				begins.append(indents + f.getName() + " : " + o.toString() + " -> " + o.getClass().getSimpleName() + "\n");
			else{
				begins.append(indents + f.getName() + " : -> " + o.getClass().getSimpleName() + "\n");
				
				if(showMethods)
					begins.append(indents + "    Methods : " + Arrays.stream(o.getClass().getMethods())
					.map(m -> m.getReturnType().getSimpleName() + " " + m.getName() + "(" + Arrays.stream(m.getParameterTypes())
							.map(Class::getSimpleName)
							.collect(Collectors.joining(", ")) + ")")
					.collect(Collectors.joining(", ")) + "\n");
				
				spit(o, indent + 1, begins, showMethods);
			}
		}
		
		return begins.toString();
	}
	
	public static String spit(Object obj){
		return spit(obj, 0, new StringBuilder(), true);
	}
}


class A{
	public String test = "est";
	public List<Integer> inttest = new ArrayList<Integer>();
	public int[] testt = {1, 2, 3, 4, 5, 999};
	public Object[] tt = {1, 2.6, 3L, "fuc", new P(1, 45)};
	
	public A(String test){
		this.test = test;
		inttest.add(4);
		inttest.add(69);
		inttest.add(-9999);
	}
}

class P{
	public int x;
	public int y;
	
	public P(int x, int y){
		this.x = x;
		this.y = y;
	}
	
	public void foo(){
		System.out.println("bar");
	}
}


 

*/