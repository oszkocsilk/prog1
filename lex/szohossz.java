/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package szohossz;

/**
 *
 * @author tomiman
 */
public class SzoHossz {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here


        int h = 0, n = 0x01, szohossz = 1;

	do
        {
	   ++h;
           n=n<<1;
           if(n == 0)
               szohossz = 0;
        }while(szohossz != 0);

        System.out.println("A szo hossza:"+h);
}

}
