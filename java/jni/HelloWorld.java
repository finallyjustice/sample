class HelloWorld
{
	private native void print(String name, int id);
	
	public static void main(String[] args)
	{
		String name = "User";
		int id = 50;
		new HelloWorld().print(name, id);
	}

	static {
		System.loadLibrary("HelloWorld");
	}
}
