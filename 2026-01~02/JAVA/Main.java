mport java.util.Scanner;
public class Main{
	public static void main(String[] args){
		Scanner scan01 = new Scanner(System.in);
		System.out.print("What is your grade: ");

		int grade = scan01.nextInt();
	
		System.out.print("Your Result Grade is ");
		if(grade > 90)
			System.out.println("A");
		else if(grade > 80)
			System.out.println("B");
		else if(grade > 70)
			System.out.println("C");
		else
			System.out.println("F");
	}
}
