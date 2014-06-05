
public class Storage {
	// the size of Storage is 10
	private Product[] products = new Product[10];
	private int top = 0;
	
	// add new product to storage
	public synchronized void push(Product product) {
		while(top == products.length) {
			try {
				wait(); // the storage is full, wait
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		products[top++] = product;
		System.out.println(Thread.currentThread().getName()+" produces "+product);
		notifyAll();
	}
	
	// consumer extracts product from storage
	public synchronized Product pop() {
		while(top == 0) {
			try {
				wait(); // the storage is empty, wait
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		--top;
		Product p = new Product(products[top].getId(), products[top].getName());
		products[top] = null;
		System.out.println(Thread.currentThread().getName()+" consumers "+p);
		notifyAll();
		return p;
	}
}
