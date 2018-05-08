package wiki2matrix;

public class AlternativTabella {


	  public static void main(String[] args) {

	    double[][] L = {
	    		{0.0, 0.08333333333333333, 0.08333333333333333, 0.15384615384615385, 0.0, 0.07692307692307693, 0.11764705882352941, 0.07142857142857142, 0.06666666666666667, 0.07142857142857142, 0.06666666666666667, 0.25, },
	    		{0.125, 0.0, 0.0, 0.07692307692307693, 0.0, 0.15384615384615385, 0.058823529411764705, 0.14285714285714285, 0.13333333333333333, 0.07142857142857142, 0.0, 0.125, },
	    		{0.0625, 0.16666666666666666, 0.0, 0.07692307692307693, 0.125, 0.07692307692307693, 0.058823529411764705, 0.14285714285714285, 0.13333333333333333, 0.07142857142857142, 0.13333333333333333, 0.0, },
	    		{0.0, 0.16666666666666666, 0.08333333333333333, 0.0, 0.125, 0.07692307692307693, 0.11764705882352941, 0.0, 0.06666666666666667, 0.07142857142857142, 0.13333333333333333, 0.0, },
	    		{0.0625, 0.16666666666666666, 0.16666666666666666, 0.07692307692307693, 0.0, 0.07692307692307693, 0.11764705882352941, 0.14285714285714285, 0.13333333333333333, 0.14285714285714285, 0.13333333333333333, 0.125, },
	    		{0.0625, 0.0, 0.16666666666666666, 0.0, 0.125, 0.0, 0.058823529411764705, 0.0, 0.06666666666666667, 0.07142857142857142, 0.06666666666666667, 0.125, },
	    		{0.125, 0.08333333333333333, 0.08333333333333333, 0.07692307692307693, 0.0, 0.07692307692307693, 0.0, 0.14285714285714285, 0.06666666666666667, 0.07142857142857142, 0.13333333333333333, 0.0, },
	    		{0.125, 0.08333333333333333, 0.08333333333333333, 0.15384615384615385, 0.125, 0.15384615384615385, 0.058823529411764705, 0.0, 0.06666666666666667, 0.14285714285714285, 0.06666666666666667, 0.0, },
	    		{0.125, 0.0, 0.08333333333333333, 0.15384615384615385, 0.25, 0.07692307692307693, 0.11764705882352941, 0.0, 0.0, 0.14285714285714285, 0.06666666666666667, 0.0, },
	    		{0.125, 0.08333333333333333, 0.08333333333333333, 0.15384615384615385, 0.125, 0.07692307692307693, 0.058823529411764705, 0.14285714285714285, 0.0, 0.0, 0.13333333333333333, 0.25, },
	    		{0.0625, 0.08333333333333333, 0.0, 0.0, 0.0, 0.07692307692307693, 0.11764705882352941, 0.07142857142857142, 0.13333333333333333, 0.0, 0.0, 0.125, },
	    		{0.125, 0.08333333333333333, 0.16666666666666666, 0.07692307692307693, 0.125, 0.07692307692307693, 0.11764705882352941, 0.14285714285714285, 0.13333333333333333, 0.14285714285714285, 0.06666666666666667, 0.0, }
	    		};

	    // az eredeti tabella sorrendje, 2011.03.11
	    String[] csapatNevE = {
	      "Ferencváros",
	      "Videoton",
	      "Debreceni VSC",
	      "Újpest",
	      "Budapest Honvéd",
	      "Paksi FC",
	      "Haladás",
	      "Diósgyőri VTK",
	      "Puskás Akadémia",
	      "Balmazújváros",
	      "Mezőkövesd–Zsóry FC",
	      "Vasas FC"
	    };
	    // az eredeti tabella pontjai, 2011.03.11
	    int[] ep = {
	      55,
	      55,
	      37,
	      37,
	      36,
	      35,
	      30,
	      30,
	      30,
	      27,
	      27,
	      26
	    };

	    // az L mαtrix kιszνtιsekori sorrend (a blogra kettιbontottban ez a Wikis keresttαbla), 2011.03.11
	    String[] csapatNevL = {
	      "Balmazújváros",
	      "Budapest Honvéd",
	      "Debreceni VSC",
	      "Diósgyőri VTK",
	      "Ferencváros",
	      "Haladás",
	      "Mezőkövesd–Zsóry FC",
	      "Paksi FC",
	      "Puskás Akadémia",
	      "Újpest",
	      "Vasas FC",
	      "Videoton"
	    };

	    double[] hv = new double[L.length];
	    double[] h = new double[L.length];

	    for (int i = 0; i < hv.length; ++i) {
	      hv[i] = 1.0 / L.length;
	      h[i] = 0.0;
	    }

	    double reginorma = 0.0, regiosszeg = 0.0;

	    boolean amig = true;
	    while (amig) {

	      for (int i = 0; i < L.length; ++i) {
	        for (int j = 0; j < L[i].length; ++j) {
	          h[i] += L[i][j] * hv[j];
	        }
	      }

	      // kicsit elegánsabban volt a laboron:
	      // http://progpater.blog.hu/2011/02/13/bearazzuk_a_masodik_labort
	      double osszeg = 0.0;
	      for (int i = 0; i < h.length; ++i) {
	        osszeg += (hv[i] - h[i]) * (hv[i] - h[i]);
	      }

	      System.out.println("iterαciσ...");

	      double norma = Math.sqrt(osszeg);
	      System.out.println("norma = " + norma);

	      if (norma < .000000000001) {
	        amig = false;

	        System.out.println("+++");
	        double osszegEll = 0.0;
	        for (int i = 0; i < h.length; ++i) {

	          osszegEll += h[i];
	          System.out.println(h[i]);

	        }
	        System.out.println("φsszeg ell. = " + osszegEll);
	        System.out.println("+++");

	      }

	      //double d = 0.98;
	      double d = 0.87;
	      //double d = 0.7;

	      osszeg = 0.0;
	      for (int i = 0; i < h.length; ++i) {

	        //hv[i] = h[i];
	        hv[i] = d * h[i] + (1.0 - d) / L.length;

	        osszeg += hv[i];
	        h[i] = 0.0;
	      }

	      System.out.println("φsszeg = " + osszeg);

	      if (osszeg == regiosszeg && norma == reginorma) {
	        amig = false;

	        System.out.println("***");
	        for (int i = 0; i < h.length; ++i) {
	          System.out.println(hv[i]);
	        }

	        System.out.println("****");

	        rendezCsapatok(csapatNevL, hv, csapatNevE, ep);

	      }
	      reginorma = norma;
	      regiosszeg = osszeg;

	    } // while
	  }

	  public static void rendezCsapatok(String[] s, double h[], String[] e, int ep[]) {

	    System.out.println("\nCsapatok rendezve:\n");

	    int csapatNevekMeret = h.length;

	    Csapat csapatok[] = new Csapat[csapatNevekMeret];

	    for (int i = 0; i < csapatNevekMeret; i++) {
	      csapatok[i] = new Csapat(s[i], h[i]);
	    }

	    java.util.List<Csapat> rendezettCsapatok = java.util.Arrays.asList(csapatok);
	    java.util.Collections.sort(rendezettCsapatok);
	    java.util.Collections.reverse(rendezettCsapatok);
	    java.util.Iterator iterv = rendezettCsapatok.iterator();
	    int ii = 0;
	    while (iterv.hasNext()) {
	      Csapat csapat = (Csapat) iterv.next();

	      String ds = Double.toString(csapat.ertek);
	      int idx = ds.indexOf(".");
	      StringBuffer sb = new StringBuffer();
	      sb = sb.delete(0, sb.length());
	      sb.append(ds.substring(0, idx + 5));
	      String e4 = sb.toString();
	System.out.println("|-");
	      System.out.println("| " + e[ii]);
	      System.out.println("| " + ep[ii]);
	      System.out.println("| " + csapat.nev);
	      System.out.println("| " + e4);

	      ++ii;
	    }
	    System.out.println("|-");

	  }
	}

	class Csapat implements Comparable<Csapat> {

	  protected String nev;
	  protected double ertek;

	  public Csapat(String nev, double ertek) {
	    this.nev = nev;
	    this.ertek = ertek;
	  }

	  public int compareTo(Csapat csapat) {
	    if (this.ertek < csapat.ertek) {
	      return -1;
	    } else if (this.ertek > csapat.ertek) {
	      return 1;
	    } else {
	      return 0;
	    }
	  }

}

