import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);	
		int n, element;
		long sum;

		n = in.nextInt();
		sum = 0l;
		for(int i = 0; i < n; i++) {
			element = in.nextInt();
			sum += element;
		}
		System.out.println(sum);

	}
}
