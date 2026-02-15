class stack{

	int s[] = new int[100];
	int top = -1;
	final int max = 100;
	void error(final String msg){
		System.out.printf("[Error]: %s", msg);
	}

	public void push(int value){
		if(top == max - 1){
			//error("Stack is Full");
			return;
		}

		s[++top] = value;
	}

	public int pop(){
		if(top == -1){
	//		error("stack is Empty");
			return -1;
		}

		return s[top--];
	}
}
