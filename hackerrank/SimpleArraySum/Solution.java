import java.io.*;
import java.util.*;

public class Solution {

	static int sumArray(int[] A) {
		int sum = 0;
		for (int element : A) {
			sum += element;
		}
		return sum;
	}

	public static void main(String[] args) {
		int n, sum;
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		int[] A = new int[n];

		for (int i = 0; i < A.length ; i++) {
			A[i] = in.nextInt();
		}
		sum = sumArray(A);
		System.out.println(sum);
	}
}
