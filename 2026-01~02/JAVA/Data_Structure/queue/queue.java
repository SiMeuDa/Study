class queue{
	private final int size = 10;
	private int front = 0, rear = 0;
	private boolean count = false;
	private int[] q = new int[size];

	void enqueue(int value){
		if(rear == size - 1)
		{
			rear = 0;
			count = true;
		}

		if((front == rear) && count)
			return;

		q[rear++] = value;
	}

	int dequeue(){
		if(front == size - 1){
			front = 0;
			count = false;
		}
	}
}
