//javac pattogoLabda.java
//java pattogoLabda

public class pattogoLabda {
    public static void main(String[] args){
	int x = 0, y = 0;
	int x1 = x-1, y1 = y-1;
	int height = 20, width = 50;
	char border = 9209;							//határ kódja UNICODE

	while(true){
	    long start = System.currentTimeMillis();
	    while(System.currentTimeMillis() - start < 250){			

	    }
	    System.out.print("\033[H\033[2J");

	    x += Math.pow(-1, x1/(width-3));
	    y += Math.pow(-1, y1/(height-3));
	    x1++;
	    y1++;

//felső határ
	    for(int i = 0; i < width; i++){
		System.out.print(border);
	    }
	    System.out.println();
//labda előtti határ, tér
	    for(int i = 0; i < y-1; i++){
		System.out.print(border);
		for(int j = 0; j < width-2; j++){
		    System.out.print(" ");
		}
		System.out.println(border);
	    }
//labda sora
	    System.out.print(border);
	    for(int i = 0; i < x-1; i++){
		System.out.print(" ");
	    }
	    System.out.print("o");
	    for(int i = x+1; i < width-1; i++){
		System.out.print(" ");
	    }
	    System.out.println(border);
//labda utáni határ, tér
	    for(int i = y+1; i < height-1; i++){
		System.out.print(border);
		for(int j = 0; j < width-2; j++){
		    System.out.print(" ");
		}
		System.out.println(border);
	    }
	    for(int i = 0; i < width; i++){
		System.out.print(border);
	    }
	    System.out.println();
	    System.out.println("X: " + x + " Y: " + y);
	}

    }
}
