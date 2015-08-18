import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
	
	static int solveMeSecond(int a, int b) {
		return a+b;
	}

	public static void main(String[] arg) {
		Scanner in = new Scanner(System.in);
		int t, sum, a, b;

		t = in.nextInt();
		for (int i = 0; i < t; i++) {
			a = in.nextInt();
			b = in.nextInt();
			sum = solveMeSecond(a, b);
			System.out.println(sum);
		}
	}
}
