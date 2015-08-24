import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n, c1, c2, c3, num;
		
		n = in.nextInt();
		
		c1 = 0;
		c2 = 0;
		c3 = 0;

		for(int i = 0; i < n; i++) {
			num = in.nextInt();
			if (num > 0)
				c1++;
			else if (num < 0)
				c2++;
			else
				c3++;
		}
		System.out.printf("%.3f", (double) c1/n);
		System.out.println();
		System.out.printf("%.3f", (double) c2/n);
		System.out.println();
		System.out.printf("%.3f", (double) c3/n);
		System.out.println();
	}
}
