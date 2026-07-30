import java.util.Arrays;
import java.util.StringTokenizer;

public class test{
	public static int[] Add(int[] originalArr, int val){
		int[] newArray = Arrays.copyOf(originalArr, originalArr.length + 1);

		newArray[newArray.length - 1] = val;
		
		return newArray;
	}


	public static void main(String[] args)
	{
		String test1 = "15, -41, 12, 42, -12, 2, 4";
		String test2 = test1.replaceAll("[^0-9,-]", ",");
		StringTokenizer strtoken = new StringTokenizer(test2, ",");
		int[] originalArr = new int[strtoken.countTokens()];
		int index = 0;
		
		while(strtoken.hasMoreTokens()){
			originalArr[index] = Integer.parseInt(strtoken.nextToken());
			index++;
	}
		int[] newArray = Add(originalArr, 99);
		int maxNumber = Integer.MIN_VALUE;

		for(int number : newArray){
			if(number > maxNumber)
				maxNumber = number;
		}

		System.out.print(maxNumber);
	}
}
