import java.util.Scanner;

public class javaswitch {
	public static void main(String[] args){
		
		int userinput1;
		int userinput2;
		int answer1;
	
		Scanner scan = new Scanner(System.in);

		System.out.println("enter your first number");
			userinput1 = scan.nextInt();
		System.out.println("enter your second number");
			userinput2 = scan.nextInt();
		System.out.println("enter your operator like +, -, *, or /");
			String tString = scan.next();
			char temp = tString.charAt(0);

		switch(temp){
			case '+':
				answer1 = userinput1 + userinput2;
				System.out.printf("your answer is %d", answer1);
				break;
			case '-':
				answer1 = userinput1 + userinput2;
				System.out.printf("your answer is %d", answer1);
				break;
			case '*':
				answer1 = userinput1 + userinput2;
				System.out.printf("your answer is %d", answer1);
				break;
			case '/':
				answer1 = userinput1 + userinput2;
				System.out.printf("your answer is %d", answer1);
				break;
			default:
				System.out.printf("i have detected an error and its you\n");
				System.out.printf("the numbers %s and %s are fine but \"%c\" is not a math operator.", userinput1, userinput2, temp);
				break;
		}
	}
}