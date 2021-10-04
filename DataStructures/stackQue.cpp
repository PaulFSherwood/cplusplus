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

