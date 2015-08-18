import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n, i, j, sum1, sum2, val;

		n = in.nextInt();
		sum1 = 0;
		sum2 = 0;

		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				val = in.nextInt();
				if (i == j) {
					sum1 += val;
				}
				if (i + j == (n - 1)) {
					sum2 += val;
				}
			}
		}

		System.out.println(Math.abs(sum1 - sum2));
	}
}
