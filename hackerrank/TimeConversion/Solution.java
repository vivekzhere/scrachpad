import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		String time, half;
		int hour;
		time = in.nextLine();
		
		hour = Integer.parseInt(time.substring(0,2));
		if ("PM".equals(time.substring(8)) && hour != 12) {
			hour += 12;
		} else if ("AM".equals(time.substring(8)) && hour == 12) {
			hour = 0;
		}
		String hourf = String.format("%02d", hour);
		System.out.println(hourf+time.substring(2,8));
	}
}
