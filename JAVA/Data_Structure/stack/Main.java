import java.util.Scanner;

public class Main{
	public static void main(String[] args){
		stack s = new stack();
		Scanner scan = new Scanner(System.in);
		boolean w = true;
		int choice;
		do{
			System.out.print("choice: ");
			choice = scan.nextInt();
			if(choice == 0)
				w = false;
			s.push(choice);
		}while(w);

		int value = 0;

		while(value != -1)
		{
			value = s.pop();
			System.out.printf("value: %d\n", value);
		}
	}
}
