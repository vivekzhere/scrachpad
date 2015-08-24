import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n;

		n = in.nextInt();
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++) {
				if (i + j + 1 < n)
					System.out.printf(" ");
				else
					System.out.printf("#");
			}
			System.out.println();
		}
	}
}
