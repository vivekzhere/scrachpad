import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int [] nums = {49, 4, 4, 49, 4, 4, 49, 49, 4, 4, 4 ,4, 180, 180, 180};

		System.out.println (singleNumber(nums) );
	}
	
	public static int singleNumber(int[] nums) {
		int a = 0, b = 0, ta;
		for (int c : nums) {
			ta = (~a&b&c) | (a&~b) | (a&~c); 
			b = (b&~c) | (~b &c);
			a = ta;
			System.out.println (c);
			System.out.println (a);
			System.out.println (b);
			System.out.println ("");

		}
		return a | b;
	}
}
