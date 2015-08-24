import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int AD, AM, AY, ED, EM, EY;
		long fine;

		AD = in.nextInt();
		AM = in.nextInt();
		AY = in.nextInt();

		ED = in.nextInt();
		EM = in.nextInt();
		EY = in.nextInt();

		if (AY > EY) {
			fine = 10000 * (AY - EY);
		} else if ( AY == EY && AM > EM) {
			fine = 500 * (AM - EM);
		} else if ( AY == EY && AM == EM && AD > ED) {
			fine = 15 * (AD - ED);
		} else {
			fine = 0;
		}

		System.out.println(fine);
	}
}
