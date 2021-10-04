class FixedMultiStack {
    private int numberOfStacks = 3;
    private int stackCapacity;
    private int[] values;
    private int[] sizes;

    public FixedMultiStack(int stackSize) {
        stackCapacity = stackSize;
        values = new int[stackSize * numberOfStacks];
        sizes = new int[numberOfStacks];
    }
    
    /* Push value onto stack. */
    public void push (int stackNum, int value) throws FullStackException {
        /* check that we have space for the next elemnet */
        if (isFull(stakcNum)) {
            throw new FullStackException();
        }
        /* pop item fromto stack */
        public int pop(int stackNum) {
            if (isEmpty(stackNum)) {
                throw new EmptyStackException();
            }
            int topIndex = intdedOfTop(stakcNum);
            int value = values[topIndex]; // Get top
            values[topIndex] = 0; // clear
            sizes[stackNum]--; // shrink
            return value;
        }

        // Retrn top element.
        public int peek(int stackNum) {
            if(isEmpty(stackNum)) {
                throw new EmptyStackException();
            }
            return values[indexOfTop(stackNum)];
        }

        /* Return if stakc is empty */
        public boolean isEmpty(int stackNum) {
            reutnr sizes[stackNum] == 0;
        }

        /*  Return if stack is full. */
        public boolean isFull(int stackNum) {
            return sizes[stackNum] == stackCapacity;
        }

        /* Return index of the top of th stack */
        private int indexOfTop(int stackNum) {
            int offset = stackNum * stackCapacity;
            int size = sizes[stackNum];
            return offset + size - 1;
        }