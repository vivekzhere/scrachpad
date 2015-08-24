import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
	public static void factorial(int n) {
		BigInteger result = new BigInteger("1");

		for (int i = 2; i <= n; i++) {
			result = result.multiply(BigInteger.valueOf(i));
		}
		
		System.out.println(result);
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n;

		n = in.nextInt();
		factorial(n);
	}
}
