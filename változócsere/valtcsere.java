package valtcsere;


public class Valtcsere {


    public static void main(String[] args) {
        
        int a = 23;
	int b = 12;

	System.out.println("a: " + a + " b: " + b);

	a = b - a;
	b = b - a;
	a = a + b;

	System.out.println("a: " + a + " b: " + b);

	a = b - a;
	b = b - a;
	a = a + b;

	System.out.println("a: " + a + " b: " + b);	
    }
    
}
