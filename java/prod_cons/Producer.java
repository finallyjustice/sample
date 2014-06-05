
public class Producer implements Runnable{
	private Storage storage;
	
	public Producer(Storage storage) {
		this.storage = storage;
	}
	
	public void run() {
		for(int i=0; i<100; i++) {
			Product product = new Product(Integer.toString(i), "P-"+i);
			storage.push(product);
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
